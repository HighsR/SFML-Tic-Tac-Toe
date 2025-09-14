#include "PauseState.hpp"
#include<sstream>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include<iostream>

namespace sOLO
{
	PauseState::PauseState(GameDataRef data) :_data(data)
	{

	}

	void PauseState::Init()
	{
		this->_data->assets.LoadTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Resume Button", RESUME_BUTTON);
		this->_data->assets.LoadTexture("Home Button", HOME_BUTTON);

		_background.emplace(_data->assets.GetTexture("Background"));
		_resumeButton.emplace(_data->assets.GetTexture("Resume Button"));
		_homeButton.emplace(_data->assets.GetTexture("Home Button"));

		if (_resumeButton) {
			const sf::FloatRect lb = _resumeButton->getLocalBounds();
			_resumeButton->setOrigin({ lb.size.x * 0.5f, lb.size.y * 0.5f });

			const auto ws = _data->window.getSize();
			_resumeButton->setPosition({
				static_cast<float>(ws.x) * 0.5f,
				static_cast<float>(ws.y) - lb.size.y * 0.5f - 10.f // 10.f is bottom margin
				});
		}

		if (_homeButton) {
			const auto lb = _homeButton->getLocalBounds();
			_homeButton->setOrigin({ lb.size.x * 0.5f, lb.size.y * 0.f });

			const auto ws = _data->window.getSize();
			_homeButton->setPosition({ static_cast<float>(ws.x) * 0.5f, 10.f });
		}

	}

	void PauseState::HandleInput()
	{
		while (auto event = this->_data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				this->_data->window.close();
				continue;
			}

			    if (this->_data->input.IsSpriteClicked(*this->_resumeButton, sf::Mouse::Button::Left, this->_data->window))
				{
					this->_data->machine.RemoveState();
				}

				if (this->_data->input.IsSpriteClicked(*this->_homeButton, sf::Mouse::Button::Left, this->_data->window))
				{
					this->_data->machine.AddState(StateRef(new MainMenuState(_data)));
				}

			
		}
	}

	void PauseState::Update(float dt)
	{

	}

	void PauseState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(*this->_background);
		this->_data->window.draw(*this->_resumeButton);
		this->_data->window.draw(*this->_homeButton);

		this->_data->window.display();
	}
}

