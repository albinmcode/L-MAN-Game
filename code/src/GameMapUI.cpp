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
,wordEnglish(40)
{
    // Load background
    if (!backgroundTexture.loadFromFile("assets/img/background.png")) {
        std::cerr << "Error al cargar la textura del fondo." << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    // Center background
    backgroundSprite.setPosition(Vector2f(35, 0));
}

void GameMap::run(RenderWindow& window) {
    std::int8_t key = 0;
    // Round word
    std::int32_t wordIndex = this->word.values[0];
    this->wordSpanish.changeWord(wordIndex + 100);
    this->wordEnglish.word = getWordByIndex(wordIndex);
    

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            this->handleEvent(window, event, key);
        }
        window.clear();
        // Sprites draw
        this->draw(window);
        this->wordSpanish.draw(window);
        this->wordEnglish.draw(window);
        this->word.draw(window);
        this->lman.draw(window);
        this->kanji.draw(window);
        this->question.draw(window);
        this->hearts.draw(window);
        this->points.draw(window);
        // player movement
        this->lman.action(window, key);
        this->kanji.actionEnemy(window); // Perform the movement of the enemies
        this->question.actionEnemy(window); //Perform the movement of the enemies
        // Process collect event
        this->collectEvent();
        window.display();
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
        this->word.removeLetter(row*22 + column);
        
        if (this->word.values[row * 22 + column] != 28) {
            std::string aux = wordEnglish.palabra;
            aux+= this->word.getLetter(this->word.values[row * 22 + column]);
            this->word.values[row * 22 + column] = 28;
            if (compareWords(aux.c_str(), wordEnglish.word, wordEnglish.length) == 1 && wordEnglish.length && wordEnglish.length<stringLength(wordEnglish.word)) {
                this->wordEnglish.palabra = aux;
                this->wordEnglish.loadWordFromString(wordEnglish.palabra);
                wordEnglish.length++;
            }
            else if (wordEnglish.length == stringLength(wordEnglish.word)) {
                std::cout << "Ganaste";
            }
            else {
                this->hearts.loseHeart();
            }
            std::cout << wordEnglish.length;
            
        }
       
        
    }
}

void GameMap::draw(RenderWindow& window) {
    // Draw background
    window.draw(backgroundSprite);
}
