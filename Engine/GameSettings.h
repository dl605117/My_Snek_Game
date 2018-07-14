#pragma once
#include <string>

class GameSettings
{
public:
	GameSettings( const std::string& filename );
	int GetTileSize() const;
	int GetBoardWidth() const;
	int GetBoardHeight() const;
	int GetNPoison() const;
	int GetNGoal() const;
	float GetSpeedUpRate() const;
private:
	int tileSize;
	int boardWidth;
	int boardHeight;
	int nPoison;
	int nGoal;
	float speedUpRate;
};