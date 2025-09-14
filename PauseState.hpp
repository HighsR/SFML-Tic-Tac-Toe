#pragma once  
#include<SFML/Graphics.hpp>  
#include"State.hpp"  
#include"Game.hpp"  

namespace sOLO
{
	class PauseState :public State
	{
	public:
		PauseState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		std::optional<sf::Sprite> _background;

		std::optional<sf::Sprite> _resumeButton;

		std::optional<sf::Sprite> _homeButton;


	};
}
