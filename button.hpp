#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class button {
 public:
  int positionX = 50;
  int positionY = 50;
  sf::Font font;
  // void (*resultingaction)();
  int buttonwidth;
  int buttonheight;
  bool buttonPressed = false;

  button(std::string label, sf::RenderWindow& window, int positionX,
         int positionY) {
    font.loadFromFile("arial.ttf");
    sf::Text text(label, font);
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Regular);
    text.setFillColor(sf::Color::Black);
    text.setPosition(positionX, positionY);
    sf::FloatRect textRect = text.getLocalBounds();
    buttonwidth = textRect.width * 1.5;
    buttonheight = textRect.height * 1.5;
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    sf::RectangleShape buttonbox(sf::Vector2f(buttonwidth, buttonheight));
    buttonbox.setPosition(positionX - buttonwidth / 2.0f,
                          positionY - buttonheight / 2.0f);
    buttonbox.setFillColor(sf::Color(100, 100, 100));
    auto MousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f MousePositionF(static_cast<float>(MousePosition.x),
                                static_cast<float>(MousePosition.y));
    window.draw(buttonbox);
    window.draw(text);
    if (buttonbox.getGlobalBounds().contains(MousePositionF) and
        sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      buttonPressed = true;
    }
  }

 private:
};
