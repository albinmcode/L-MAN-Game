#pragma once

#include <codecvt>
#include <cstdint>
#include <SFML/Graphics.hpp>

// converter to manage utf8 characters
static std::wstring_convert<std::codecvt_utf8<wchar_t>> wStrConverter;

class RoundWordUI {
public:
	// Default constructor
	RoundWordUI(int yCord);
	// Draw points
	void draw(sf::RenderWindow& window);
	// Load texture from a character indexed from the word
	void loadLetterTexture(std::int32_t index, sf::Texture& letterTexture,
		const std::wstring& wordStr);
	// Obtain wordString size
	size_t getlength() const;
	// Obtain wordString
	const std::string& getString();
	// Set a new word string
	virtual void changeWord(std::int32_t index);
	// Load actual word string characters texture
	void loadWordTexture();
	// Load Word textures from a new word or from the the actual wordString
	void loadWordFromString(const std::string& newWord = " ");

protected:
	std::string wordString;
	sf::Texture wordSTexture;
	sf::Sprite wordSprite;
	std::vector<sf::Texture> letters;
	int yCord;
};
