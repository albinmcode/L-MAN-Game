#pragma once

#include <SFML/Graphics.hpp>

// SFML library extension
namespace sf {
	class Link : public sf::Text {
	public:
		//Constructors
		inline Link() : Text() {} // Default
		Link(std::string titleStr, std::string urlStr, sf::Vector2f position);
		// mouse control
		const bool isMouseOver(const sf::RenderWindow& window);
		// go to link
		void openURL();

	private:
		std::string url;
	};
}
