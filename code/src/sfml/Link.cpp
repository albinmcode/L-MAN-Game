#include "Link.hpp"

sf::Link::Link(std::string titleStr, std::string urlStr, sf::Vector2f position)
: Text()
, url(urlStr)
{
    this->setString(titleStr);
    this->setPosition(position);
}

bool sf::Link::isMouseOver(const sf::RenderWindow& window) const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect buttonBounds = this->getGlobalBounds();
    return buttonBounds.contains(static_cast<sf::Vector2f>(mousePos));
}

void sf::Link::openURL() const {
  // Linux system call
  ::system(("xdg-open " + this->url).c_str());
}