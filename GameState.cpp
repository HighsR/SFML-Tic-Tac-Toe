#include "GameState.hpp"
#include<sstream>
#include "DEFINITIONS.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"

#include<iostream>

namespace sOLO
{
	GameState::GameState(GameDataRef data) :_data(data)
	{

	}

	void GameState::Init()
	{
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;

		this->ai = new AI(turn, this->_data);

		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		this->_data->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Piece", O_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("X Winning Piece",X_WINNING_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Winning Piece", O_WINNING_PIECE_FILEPATH);

		_background.emplace(_data->assets.GetTexture("Background"));
		_pauseButton.emplace(_data->assets.GetTexture("Pause Button"));
		_gridSprite.emplace(_data->assets.GetTexture("Grid Sprite"));

		if (_pauseButton) {
			const sf::FloatRect lb = _pauseButton->getLocalBounds();
			_pauseButton->setOrigin({ lb.size.x * 0.5f, lb.size.y * 0.5f });

			const auto ws = _data->window.getSize();
			_pauseButton->setPosition({ static_cast<float>(ws.x) * 0.5f,static_cast<float>(ws.y) - lb.size.y * 0.5f - 10.f });
		}
		if (_gridSprite) {
			const sf::FloatRect lb = _gridSprite->getLocalBounds();

			_gridSprite->setOrigin({ lb.size.x * 0.5f, lb.size.y * 0.5f });

			const auto ws = _data->window.getSize();
			_gridSprite->setPosition({ static_cast<float>(ws.x) * 0.5f,static_cast<float>(ws.y) * 0.5f });
		}
		

		InitGridPieces();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				gridArray[x][y] = EMPTY_PIECE;
			}
		}
	}

	void GameState::HandleInput()
	{
		while (auto event = this->_data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				this->_data->window.close();
			}


			if (this->_data->input.IsSpriteClicked(*this->_pauseButton, sf::Mouse::Button::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
			}

			else if (this->_data->input.IsSpriteClicked(*this->_gridSprite, sf::Mouse::Button::Left, this->_data->window))
			{
				if (gameState ==STATE_PLAYING)
				{
					this->CheckAndPlacePiece();
				}
			}
			
			
		}
	}

	void GameState::Update(float dt)
	{
		if (gameState == STATE_DRAW || gameState == STATE_LOSE || gameState == STATE_WON)
		{
			if (this->_clock.getElapsedTime().asSeconds() > TIME_BEFORE_SHOWING_GAME_OVER)
			{
				this->_data->machine.AddState(StateRef(new GameOverState(_data,gameState)), true);
			}
		}
	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(*this->_background);
		this->_data->window.draw(*this->_pauseButton);
		this->_data->window.draw(*this->_gridSprite);

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				this->_data->window.draw(*this->_gridPieces[x][y]);
			}
		}

		this->_data->window.display();
	}

	void GameState::InitGridPieces()
	{
		if (!_gridSprite) return;

		const sf::IntRect tr = _gridSprite->getTextureRect();
		const sf::Vector2f sc = _gridSprite->getScale();

		const float gridW = static_cast<float>(tr.size.x) * sc.x;
		const float gridH = static_cast<float>(tr.size.y) * sc.y;

		const sf::Vector2f topLeft = _gridSprite->getPosition() - sf::Vector2f{ gridW * 0.5f, gridH * 0.5f };

		const float cellW = gridW / 3.f;
		const float cellH = gridH / 3.f;

		const auto& xTex = _data->assets.GetTexture("X Piece");
		const auto texSz = xTex.getSize();

		const float s = std::min(cellW / static_cast<float>(texSz.x),cellH / static_cast<float>(texSz.y)) * 0.75f;

		for (int x = 0; x < 3; ++x)
			for (int y = 0; y < 3; ++y)
			{
				if (!_gridPieces[x][y]) _gridPieces[x][y].emplace(xTex);

				auto& spr = *_gridPieces[x][y];
				spr.setTexture(xTex);

				const auto lb = spr.getLocalBounds();
				spr.setOrigin(sf::Vector2f{ lb.position.x + lb.size.x * 0.5f,lb.position.y + lb.size.y * 0.5f });

				spr.setScale(sf::Vector2f{ s, s });

				spr.setPosition(sf::Vector2f{topLeft.x + (x + 0.5f) * cellW,topLeft.y + (y + 0.5f) * cellH});

				spr.setColor(sf::Color(255, 255, 255, 0));
			}
	}	
	void GameState::CheckAndPlacePiece()
	{
		if (!_gridSprite) return;

		const sf::Vector2f mouse = _data->window.mapPixelToCoords(
			_data->input.GetMousePosition(_data->window));

		const sf::FloatRect g = _gridSprite->getGlobalBounds();
		if (!g.contains(mouse)) return; 

		const float cellW = g.size.x / 3.f;
		const float cellH = g.size.y / 3.f;

		int col = static_cast<int>((mouse.x - g.position.x) / cellW);
		int row = static_cast<int>((mouse.y - g.position.y) / cellH);
		col = std::clamp(col, 0, 2);
		row = std::clamp(row, 0, 2);

		if (gridArray[col][row] != EMPTY_PIECE) return;

		if (!_gridPieces[col][row])
			_gridPieces[col][row].emplace(_data->assets.GetTexture("X Piece"));

		auto& spr = *_gridPieces[col][row];

		gridArray[col][row] = turn;
		if (turn == PLAYER_PIECE) {
			spr.setTexture(_data->assets.GetTexture("X Piece"));

			this->checkPlayerHasWon(turn);

		}
		spr.setColor(sf::Color(255, 255, 255, 255));
	}
	
	void GameState::checkPlayerHasWon(int player)
	{
		Check3PiecesForMatch(0, 0, 1, 0, 2, 0, player);
		Check3PiecesForMatch(0, 1, 1, 1, 2, 1, player);
		Check3PiecesForMatch(0, 2, 1, 2, 2, 2, player);
		Check3PiecesForMatch(0, 0, 0, 1, 0, 2, player);
		Check3PiecesForMatch(1, 0, 1, 1, 1, 2, player);
		Check3PiecesForMatch(2, 0, 2, 1, 2, 2, player);
		Check3PiecesForMatch(0, 0, 1, 1, 2, 2, player);
		Check3PiecesForMatch(0, 2, 1, 1, 2, 0, player);

		if (STATE_WON != gameState)
		{
			gameState = STATE_AI_PLAYING;

			ai->PlacePiece(&gridArray, _gridPieces, &gameState);

			Check3PiecesForMatch(0, 0, 1, 0, 2, 0, AI_PIECE);
			Check3PiecesForMatch(0, 1, 1, 1, 2, 1, AI_PIECE);
			Check3PiecesForMatch(0, 2, 1, 2, 2, 2, AI_PIECE);
			Check3PiecesForMatch(0, 0, 0, 1, 0, 2, AI_PIECE);
			Check3PiecesForMatch(1, 0, 1, 1, 1, 2, AI_PIECE);
			Check3PiecesForMatch(2, 0, 2, 1, 2, 2, AI_PIECE);
			Check3PiecesForMatch(0, 0, 1, 1, 2, 2, AI_PIECE);
			Check3PiecesForMatch(0, 2, 1, 1, 2, 0, AI_PIECE);

		}
		int emptyNum = 9;
		
		for(int x=0;x<3;x++)
		{
			for (int y=0; y < 3; y++)
			{
				if (EMPTY_PIECE != gridArray[x][y])
				{
					emptyNum--;
				}
			}
		}
		if (emptyNum==0&&(STATE_WON!=gameState)&&(STATE_LOSE!=gameState))
		{
			gameState=STATE_DRAW;
		}

		if (STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState)
		{
			this->_clock.restart();

		}
		
		std::cout << gameState << std::endl;
	}

	void GameState::Check3PiecesForMatch(int x1,int y1,int x2,int y2,int x3,int y3,int pieceToCheck)
	{
		if (pieceToCheck == gridArray[x1][y1]&& pieceToCheck == gridArray[x2][y2]&& pieceToCheck == gridArray[x3][y3])
		{
			std::string winningPieceStr;
			if (O_PIECE == pieceToCheck)
			{
				winningPieceStr = "O Winning Piece";
			}
			else
			{
				winningPieceStr = "X Winning Piece";
			}

			_gridPieces[x1][y1]->setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x2][y2]->setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x3][y3]->setTexture(this->_data->assets.GetTexture(winningPieceStr));

			if (PLAYER_PIECE == pieceToCheck)
			{
				gameState = STATE_WON;
			}
			else
			{
				gameState = STATE_LOSE;
			}
		}
	}
}
