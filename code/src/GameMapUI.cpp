#include "GameMapUI.hpp"
#include <iostream>

GameMap::GameMap()
: mapSize(13*24)
, map()
, lman(Vector2f(64, 128))
, kanji(Vector2f(384+3, 288), "assets/img/kanji.png", 11 ,6, this->lman)
, question(Vector2f(384+2, 320), "assets/img/pregunta.png", 11 , 7, this->lman)
, hearts(Vector2f(672+2, 64))
, points(Vector2f(672 + 2, 32))
, word(Vector2f(74, 136))
, wordSpanish(0)
, wordEnglish(40)
, roundWon(0)
{
    // Load background
    if (!backgroundTexture.loadFromFile("assets/img/background.png")) {
        std::cerr << "Error al cargar la textura del fondo." << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    // Center background
    backgroundSprite.setPosition(Vector2f(35, 0));


    if (!backgroundMusic.openFromFile("assets/music/background.ogg")) {
        std::cerr << "Error al cargar la música de fondo." << std::endl;
    }
    else {
        backgroundMusic.setLoop(true); // Reproducir en bucle
        backgroundMusic.play();
    }
}

void GameMap::run(RenderWindow& window) {
    bool endRound = false;
    
    while (window.isOpen()) {
        // Round word
        std::int32_t wordIndex = this->word.getRandomIndex(0, 99);
        this->wordSpanish.changeWord(wordIndex + 100);
        this->wordEnglish.changeWord(wordIndex);

        this->key = 0;
        endRound = false;
        this->roundWon = false;

        while (endRound == false) {
            Event event;
            while (window.pollEvent(event)) {
                this->handleEvent(window, event);
            }

            // player movement
            this->lman.action(window, this->key);
            this->kanji.actionEnemy(window); // Perform the movement of the enemies
            this->question.actionEnemy(window); //Perform the movement of the enemies
            // Process collect event
            this->collectEvent();
            // Entity colision event
            this->entityColisionEvent();
            

            // Sprites draw
            window.clear();
            this->draw(window);
            this->hearts.draw(window);
            this->wordSpanish.draw(window);
            this->wordEnglish.draw(window);
            this->word.draw(window);
            this->lman.draw(window);
            this->kanji.draw(window);
            this->question.draw(window);
            this->points.draw(window);
            window.display();

            if (this->checkEndCondition() == true) break;
        }

        // new game wait
        sf::sleep(sf::seconds(2));
        
        // Restart objects for a new round //
        if (this->roundWon == false) {
            this->points.restart();
            std::cout << "Perdiste\n";
        }
        else {
            this->hearts.winHeart();
        }
        this->wordEnglish.restartBuffers();
        resetElementsMap();
        this->word.restartLetters();
        this->lman.restartPosition(0, 0);
        this->key = 0;
        this->kanji.restartPosition(10, 5);
        this->question.restartPosition(10, 6);
    }
}

void GameMap::handleEvent(RenderWindow& window, Event& event) {
    if (event.type == Event::Closed) {
        window.close();
    }
    if (event.type == Event::KeyPressed) {
        // Convert from SFML key.code to ASCII
        if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
            this->key = static_cast<std::int8_t>(event.key.code - sf::Keyboard::A + 'A');
        }
        else if (event.key.code == sf::Keyboard::Space) {
            this->key = 32;
        }
    }
}

void GameMap::collectEvent() {
    // space pressed
    if (this->lman.collectChr() == true) {
        // row and column to index the letters matrix and remove one
        std::int32_t row = this->lman.getScale().y - 1;
        std::int32_t column = this->lman.getScale().x - 1;
        // position = (row * total columns) + column
        this->word.removeLetter(row * 22 + column);

        // not empty cell
        if (getElement(row * 22 + column) >= 'a') {
            // Obtain letter
            this->wordEnglish.collectChr(static_cast<char>(getElement(row * 22 + column)));
            // clear cell
            saveElement(0, row * 22 + column);
            // Check for match
            if (compareWords(wordEnglish.getString(), wordEnglish.getObjective(), wordEnglish.getlength()) == 1) {
                this->wordEnglish.refreshWord();
            }
            else {
                this->wordEnglish.popCollected();
                this->hearts.loseHeart();
            }
        }
    }
}

void GameMap::entityColisionEvent() {
    // Check for delay time and colision conditions
    if (canLoseLife && ((calculateDistance(this->lman.getPosition(), this->kanji.getPosition()) <= collisionDistance) ||
        (calculateDistance(this->lman.getPosition(), this->question.getPosition()) <= collisionDistance))) {
        this->hearts.loseHeart();
        sf::sleep(sf::milliseconds(300));
        // restart entities position and movement
        if (!this->hearts.playerDead()) {
            this->lman.restartPosition(0, 0);
            this->key = 0;
            this->kanji.restartPosition(10, 5);
            this->question.restartPosition(10, 6);
        }
        
        canLoseLife = false;
        clock.restart();
    }
    if (!canLoseLife && clock.getElapsedTime().asSeconds() >= delayBetweenLives) {
        canLoseLife = true;  // Permitir perder vida de nuevo
    }
}

const bool GameMap::checkEndCondition() {
    // Check if the english word and the colected word are the same
    if (compareWords(this->wordEnglish.palabra.c_str(), wordEnglish.word, wordEnglish.length) == 1) {
        this->points.winPoint();
        this->roundWon = true;
        std::cout << "Ganaste\n";
        return true;
    }
    // Check die event
    if (this->hearts.playerDead()) {
        this->roundWon = false;
        this->hearts.restartHearts(3);
        return true;
    }
    return false;
}

void GameMap::draw(RenderWindow& window) {
    // Draw background
    window.draw(backgroundSprite);
}

const float GameMap::calculateDistance(sf::Vector2i pos1, sf::Vector2i pos2) {
    sf::Vector2f posLman = static_cast<sf::Vector2f>(pos1);
    sf::Vector2f enemy = static_cast<sf::Vector2f>(pos2);
    
    return std::sqrt(std::pow(posLman.x - enemy.x, 2) + std::pow(posLman.y - enemy.y, 2));
}
