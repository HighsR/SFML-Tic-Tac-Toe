#pragma once  
#include<SFML/Graphics.hpp>  
#include"State.hpp"  
#include"Game.hpp"  
#include "AI.hpp"

namespace sOLO
{
	class GameState :public State
	{
	public:
		GameState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		void InitGridPieces();

		void CheckAndPlacePiece();

		void checkPlayerHasWon(int turn);
		
		void Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);

		GameDataRef _data;

		std::optional<sf::Sprite> _background;

		std::optional<sf::Sprite> _pauseButton;

		std::optional<sf::Sprite> _gridSprite;

		std::optional <sf::Sprite> _gridPieces[3][3];
		int gridArray[3][3];

		int turn;
		int gameState;

		AI* ai;

		sf::Clock _clock;
	};
}
