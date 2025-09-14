#include "InputManager.hpp"

namespace sOLO
{
    bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window)
    {
	   if (sf::Mouse::isButtonPressed(button))
	   {
		 const sf::Vector2i pixel = sf::Mouse::getPosition(window);
		 const sf::Vector2f world = window.mapPixelToCoords(pixel);
		 return object.getGlobalBounds().contains(world);
	   }

		return false;
    }

	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
	{
		return sf::Mouse::getPosition(window);
	}
}