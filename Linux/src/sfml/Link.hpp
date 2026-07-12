#pragma once

#include <SFML/Graphics.hpp>

// SFML library extension
namespace sf {
class Link : public sf::Text {
 public:
	//Constructors
	Link() = default;
	Link(std::string titleStr, std::string urlStr, sf::Vector2f position);
	// mouse control
	bool isMouseOver(const sf::RenderWindow& window) const;
	// go to link
	void openURL() const;

 private:
	std::string url;
};
}
