#pragma once  
#include<SFML/Graphics.hpp>  
#include"State.hpp"  
#include"Game.hpp"  

namespace sOLO
{
	class MainMenuState :public State
	{
	public:
		MainMenuState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		std::optional<sf::Sprite> _background;

		std::optional<sf::Sprite> _playButton;

		std::optional<sf::Sprite> _playButtonOuter;

		std::optional<sf::Sprite> _title;

	};
}
