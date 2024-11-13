#include "GameMapUI.hpp"
#include <iostream>

GameMap::GameMap()
: mapSize(13*24)
, map()
, lman(Vector2f(64, 128))
, kanji(Vector2f(384+3, 288), "assets/img/kanji.png", 11 ,6)
, question(Vector2f(384+2, 320), "assets/img/pregunta.png", 11 , 7 )
, hearts(Vector2f(672+2, 64))
, points(Vector2f(672 + 2, 32))
, word(Vector2f(74, 136), word.index())
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
    std::int8_t key = 0;
    bool endRound = false;
    
    while (window.isOpen()) {
        // Round word
        std::int32_t wordIndex = this->word.values[this->word.getRandomIndex()];
        this->wordSpanish.changeWord(wordIndex + 100);
        this->wordEnglish.word = getWordByIndex(wordIndex);

        key = 0;
        endRound = false;
        this->roundWon = false;

        while (endRound == false) {
            Event event;
            while (window.pollEvent(event)) {
                this->handleEvent(window, event, key);
            }

            // player movement
            this->lman.action(window, key);
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

            if (canLoseLife &&((calculateDistance(this->lman.getPosition(), this->kanji.getPosition()) <= collisionDistance) ||
                (calculateDistance(this->lman.getPosition(), this->question.getPosition()) <= collisionDistance))) {
                    this->hearts.loseHeart();
                    canLoseLife = false;
                    clock.restart();
            }
            if (!canLoseLife && clock.getElapsedTime().asSeconds() >= delayBetweenLives) {
                canLoseLife = true;  // Permitir perder vida de nuevo
            }    
            if (this->checkEndCondition() == true) break;
        }
        // new game wait
        sf::sleep(sf::seconds(2));
        
        // Restart objects for a new round //
        if (this->roundWon == false) {
            this->points.restart();
            std::cout << "Perdiste\n";
        }
        this->wordEnglish.restartBuffers();
        resetElementsMap();
        this->word.restartLetters(); // Letters on the map
        this->hearts.restartHearts(3); // Lost hearts value
    }
}

void GameMap::handleEvent(RenderWindow& window, Event& event, std::int8_t& key) {
    if (event.type == Event::Closed) {
        window.close();
    }
    if (event.type == Event::KeyPressed) {
        // Convert from SFML key.code to ASCII
        if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
            key = static_cast<std::int8_t>(event.key.code - sf::Keyboard::A + 'A');
        }
        else if (event.key.code == sf::Keyboard::Space) {
            key = 32;
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
            std::string aux = wordEnglish.palabra;
            aux += static_cast<char>(getElement(row * 22 + column));
            saveElement(0, row * 22 + column);
            this->word.values[row * 22 + column] = 28;
            if (compareWords(aux.c_str(), wordEnglish.word, wordEnglish.length) == 1 && wordEnglish.length && wordEnglish.length <= stringLength(wordEnglish.word)) {
                this->wordEnglish.palabra = aux;
                this->wordEnglish.loadWordFromString(wordEnglish.palabra);
                wordEnglish.length++;
                this->points.winPoint();
            }
            else {
                this->hearts.loseHeart();
            }
            //std::cout << wordEnglish.length << ' ' << wordEnglish.word << '<-' << wordEnglish.palabra << '\n';
        }
    }
}

void GameMap::entityColisionEvent() {
    return;
}

const bool GameMap::checkEndCondition() {
    if (compareWords(this->wordEnglish.palabra.c_str(), wordEnglish.word, wordEnglish.length) == 1) {
        this->roundWon = true;
        std::cout << "Ganaste\n";
        return true;
    }
    if (this->hearts.playerDead()) {
        this->roundWon = false;
        return true;
    }
    return false;
}

const bool GameMap::getWinFlag() {
    return this->roundWon;
}

void GameMap::draw(RenderWindow& window) {
    // Draw background
    window.draw(backgroundSprite);
}

float GameMap::calculateDistance(sf::Vector2i pos1, sf::Vector2i pos2) {
    sf::Vector2f posLman = static_cast<sf::Vector2f>(pos1);
    sf::Vector2f enemy = static_cast<sf::Vector2f>(pos2);
    
    return std::sqrt(std::pow(posLman.x - enemy.x, 2) + std::pow(posLman.y - enemy.y, 2));
}
