#include "GameMapUI.hpp"
#include <iostream>

#include "Dictionary.hpp"

GameMap::GameMap()
: lman(Vector2f(64, 128))
, kanji(Vector2f(384+3, 288), "assets/img/kanji.png", "assets/img/kanji_vulnerable.png", 11 ,6, this->lman)
, question(Vector2f(384+2, 320), "assets/img/pregunta.png","assets/img/pregunta_vulnerable.png", 11 , 7, this->lman)
, hearts(Vector2f(672+2, 64))
, points(Vector2f(672 + 2, 32))
, letters(Vector2f(74, 136))
, wordSpanish(0)
, wordEnglish(40)
, sound()
{
    // Load background
    if (!backgroundTexture.loadFromFile("assets/img/background.png")) {
        throw std::runtime_error("No fue posible cargar la textura del fondo.");
    }
    backgroundSprite.setTexture(backgroundTexture);
    // Center background
    backgroundSprite.setPosition(Vector2f(35, 0));


    if (!backgroundMusic.openFromFile("assets/music/background.ogg")) {
        std::cerr << "No fue posible cargar la música de fondo." << std::endl;
    } else {
        backgroundMusic.setLoop(true); // Reproducir en bucle
        backgroundMusic.setVolume(20.0);
        backgroundMusic.play();
    }

    // load dictionary file
    if (!Dictionary::getInstance().loadFromCSV(
            "./assets/diccionarios/tildes/200commonwords.txt")) {
        throw std::runtime_error("Error al cargar diccionario.");
    }
}
void GameMap::vulnerability() {
    if (kanji.isVulnerable()||question.isVulnerable()) {
        if (vulnerabilityClock.getElapsedTime().asSeconds() >= 25) { // 10 segundos de vulnerabilidad
            kanji.setAttackEnemy();
            question.setAttackEnemy();
            lman.setNormal();
        }
    }
}
void GameMap::run(RenderWindow& window) {
    bool endRound = false;
    
    while (window.isOpen()) {
        // Round word
        std::int32_t wordIndex = this->letters.getRandomIndex(0,
            Dictionary::getInstance().size() - 1);
        this->wordSpanish.changeWord(wordIndex);
        this->wordEnglish.changeWord(wordIndex);

        this->key = 0;
        endRound = false;

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
            //vulnerable
            this->vulnerability();
            // Entity colision event   
            this->entityColisionEvent();
            

            // Sprites draw
            window.clear();
            this->draw(window);
            window.display();

            if (this->checkEndCondition() == true) break;
        }

        // new game wait
        sf::sleep(sf::seconds(2));
        
        // Restart objects for a new round //
        this->wordEnglish = EnglishWordUI(40);
        this->letters.restartLetters();
        this->lman.restartPosition(0, 0);
        this->key = 0;
        this->lman.restartMovement();
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
    if ((this->lman.collectChr() == true) && !getColision()) {
        // position = (row * total columns) + column
        size_t row = this->lman.getScale().y - 1;
        size_t column = this->lman.getScale().x - 1;
        // not empty cell
        if (this->letters.getElement(row, column) >= 'a') {
            // Obtain letter
            this->wordEnglish.collectChr(this->letters.getElement(row, column));
            // Clear position
            this->letters.removeLetter(row, column);
            // Check for match
            if (this->wordEnglish.validCollected(this->wordEnglish.getlength())){
                this->wordEnglish.refreshWord();
            }
            else {
                this->wordEnglish.popCollected();
                this->hearts.loseHeart();
            }
            sound.play("coin.wav");
        }
        if (this->letters.getElement(row, column) == 3) {
            // Clear position
            this->letters.removeLetter(row, column);
            // Set enemies vulnerable
            kanji.setVulnerableEnemy();
            question.setVulnerableEnemy();
            vulnerabilityClock.restart();
            lman.setBoost();
        }
    }
    else if (getColision()) {
        if (getEntityColision(this->kanji) && kanji.isVulnerable()) {
            kanji.setAttackEnemy();
            kanji.restartPosition(10, 5);
            wordEnglish.winChr();
        }
        else if(getEntityColision(this->question) && question.isVulnerable()){
            question.setAttackEnemy();
            question.restartPosition(10,6);
            wordEnglish.winChr();
        }
        
    }
}
bool GameMap::getEntityColision(EnemyUI enemy) {
    return calculateDistance(this->lman.getPosition(), enemy.getPosition()) <= collisionDistance;
}

bool GameMap::getColision() {
    return (getEntityColision(this->kanji)) || (getEntityColision(this->question));
}

void GameMap::dead() {
    this->hearts.loseHeart();
    sf::sleep(sf::milliseconds(300));
    // restart entities position and movement
    if (!this->hearts.playerDead()) {
        this->lman.restartPosition(0, 0);
        this->key = 0;
        this->kanji.restartPosition(10, 5);
        this->question.restartPosition(10, 6);
    }
    this->lman.restartMovement();
    canLoseLife = false;
    clock.restart();
    sound.play("hit.wav");
}

void GameMap::entityColisionEvent() {
    // Check for delay time and colision conditions
    
    if (canLoseLife && (getColision())&&!(kanji.isVulnerable()&&question.isVulnerable())){
        if (!kanji.isVulnerable()) {
            dead();
        }else if(!question.isVulnerable()){
            dead();
        }
        
    }
    if (!canLoseLife && clock.getElapsedTime().asSeconds() >= delayBetweenLives) {
        canLoseLife = true;  // Permitir perder vida de nuevo
    }
}

bool GameMap::checkEndCondition() {
    // Check if the english word and the colected word are the same
    if (this->wordEnglish.completedWord()) {
        // std::cout << "Ganaste\n";
        this->points.winPoint();
        this->hearts.winHeart();
        sound.play("win.wav");
        return true;
    }
    // Check die event
    if (this->hearts.playerDead()) {
        // std::cout << "Perdiste\n";
        sound.play("dead.wav");
        kanji.setAttackEnemy();
        question.setAttackEnemy();
        this->points.restart();
        this->hearts.restartHearts(3);
        return true;
    }
    return false;
}

void GameMap::draw(RenderWindow& window) {
    // Draw background
    window.draw(backgroundSprite);
    this->hearts.draw(window);
    this->wordSpanish.draw(window);
    this->wordEnglish.draw(window);
    this->letters.draw(window);
    this->lman.draw(window);
    this->kanji.draw(window);
    this->question.draw(window);
    this->points.draw(window);
}

float GameMap::calculateDistance(sf::Vector2i pos1, sf::Vector2i pos2) const {
    sf::Vector2f posLman = static_cast<sf::Vector2f>(pos1);
    sf::Vector2f enemy = static_cast<sf::Vector2f>(pos2);
    
    return std::sqrt(std::pow(posLman.x - enemy.x, 2) + std::pow(posLman.y - enemy.y, 2));
}
