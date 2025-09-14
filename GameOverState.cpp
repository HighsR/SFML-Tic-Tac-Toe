#include<sstream>
#include "GameOverState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include "GameState.hpp"
#include<iostream>

namespace sOLO
{
    GameOverState::GameOverState(GameDataRef data, int gameState) : _data(data), _gameState(gameState)  
    {  

    }

	void GameOverState::Init()
	{
		this->_data->assets.LoadTexture("Retry Button", RETRY_BUTTON);
		this->_data->assets.LoadTexture("Home Button", HOME_BUTTON);


		_retryButton.emplace(_data->assets.GetTexture("Retry Button"));
		_homeButton.emplace(_data->assets.GetTexture("Home Button"));

		if (_retryButton) {
			const sf::FloatRect lb = _retryButton->getLocalBounds();

			_retryButton->setOrigin({ lb.size.x * 0.5f, lb.size.y * 0.5f });

			const auto ws = _data->window.getSize();
			_retryButton->setPosition({ static_cast<float>(ws.x) * 0.5f,static_cast<float>(ws.y) * 0.5f });
		}

		if (_homeButton) {
			const auto lb = _homeButton->getLocalBounds();
			_homeButton->setOrigin({ lb.size.x * 0.5f, lb.size.y * 0.f });

			const auto ws = _data->window.getSize();
			_homeButton->setPosition({ static_cast<float>(ws.x) * 0.5f, 10.f });
		}

	}

	void GameOverState::HandleInput()
	{
		while (auto event = this->_data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				this->_data->window.close();
				continue;
			}


			if (this->_data->input.IsSpriteClicked(*this->_retryButton, sf::Mouse::Button::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new GameState(_data)), true);
			}

			if (this->_data->input.IsSpriteClicked(*this->_homeButton, sf::Mouse::Button::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new MainMenuState(_data)));
			}

		}
	}

	void GameOverState::Update(float dt)
	{

	}
	
	void GameOverState::Draw(float dt)
	{
        if (this->_gameState == STATE_WON)
        {
			this->_data->window.clear(sf::Color::Green);
		}
		else if (this->_gameState == STATE_LOSE)
		{
			this->_data->window.clear(sf::Color::Red);
		}
		else {
			this->_data->window.clear(sf::Color::White);
		}

		this->_data->window.draw(*this->_retryButton);
		this->_data->window.draw(*this->_homeButton);


		this->_data->window.display();
	}
}

