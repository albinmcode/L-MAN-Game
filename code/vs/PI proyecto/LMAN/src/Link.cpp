#include "Link.hpp"

sf::Link::Link(std::string titleStr, std::string urlStr, sf::Vector2f position)
: Text()
, url(urlStr)
{
    this->setString(titleStr);
    this->setPosition(position);
}

const bool sf::Link::isMouseOver(const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect buttonBounds = this->getGlobalBounds();
    return buttonBounds.contains(static_cast<sf::Vector2f>(mousePos));
}

void sf::Link::openURL() {
    // Windows shell
    std::wstring urlWSTR =  std::wstring(this->url.begin(), this->url.end());
    ShellExecute(0, 0, urlWSTR.c_str(), 0, 0, SW_SHOW);
}