#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <optional>

namespace sOLO
{
	class SplashState: public State
	{
	public:
		SplashState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		
	private:
		GameDataRef _data;

		sf::Clock _clock;

		std::optional<sf::Sprite> _background;
		
	};
}


