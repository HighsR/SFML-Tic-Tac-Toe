#pragma once  
#include<SFML/Graphics.hpp>  
#include"State.hpp"  
#include"Game.hpp"  

namespace sOLO
{
	class GameOverState :public State
	{
	public:
		//GameOverState(GameDataRef data);
		GameOverState(GameDataRef data, int _gameState);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		std::optional<sf::Sprite> _background;

		std::optional<sf::Sprite> _retryButton;

		std::optional<sf::Sprite>  _homeButton;

		int _gameState;

	};
}
