#include<sstream>
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include "GameState.hpp"
#include<iostream>

namespace sOLO
{
	MainMenuState::MainMenuState(GameDataRef data) :_data(data)
	{

	}

	void MainMenuState::Init()
	{
		this->_data->assets.LoadTexture("Background",MAIN_MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Game Title",MAIN_MENU_TITLE_PATH);
		this->_data->assets.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
		this->_data->assets.LoadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);

		_background.emplace(_data->assets.GetTexture("Background"));
		_title.emplace(_data->assets.GetTexture("Game Title"));
		_playButton.emplace(_data->assets.GetTexture("Play Button"));
		_playButtonOuter.emplace(_data->assets.GetTexture("Play Button Outer"));

		if (_playButton) {
			const sf::FloatRect lb = _playButton->getLocalBounds();

			_playButton->setOrigin({ lb.size.x * 0.5f, lb.size.y * 0.5f });

			const auto ws = _data->window.getSize();
			_playButton->setPosition({ static_cast<float>(ws.x) * 0.5f,static_cast<float>(ws.y) * 0.5f });
		}

		if (_playButtonOuter) {
			const auto lb = _playButtonOuter->getLocalBounds();
			_playButtonOuter->setOrigin({ lb.size.x * 0.5f, lb.size.y * 0.5f });

			const auto ws = _data->window.getSize();
			_playButtonOuter->setPosition({ static_cast<float>(ws.x) * 0.5f,static_cast<float>(ws.y) * 0.5f });
		}

		if (_title) {
			const auto lb = _title->getLocalBounds();
			_title->setOrigin({ lb.size.x * 0.5f, 0.f });

			const auto ws = _data->window.getSize();
			_title->setPosition({ static_cast<float>(ws.x) * 0.5f, 0.f });
		}
	}

	void MainMenuState::HandleInput()
	{
		while (auto event = this->_data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				this->_data->window.close();
				continue;
			}


			if (this->_data->input.IsSpriteClicked(*this->_playButton,sf::Mouse::Button::Left,this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
		}
	}

	void MainMenuState::Update(float dt)
	{

	}

	void MainMenuState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(*this->_background);
		this->_data->window.draw(*this->_playButton);
		this->_data->window.draw(*this->_playButtonOuter);
		this->_data->window.draw(*this->_title);

		this->_data->window.display();
	}
}

