#include "GameSettings.h"
#include <fstream>

GameSettings::GameSettings( const std::string& filename )
{
	std::fstream in( filename );

	std::string line;
	while ( std::getline( in, line ) )
	{
		if ( line == "[Tile Size]" )
		{
			in >> tileSize;
		}
		else if ( line == "[Board Size]" )
		{
			in >> boardWidth >> boardHeight;
		}
		else if ( line == "[SpeedUp Rate]" )
		{
			in >> speedUpRate;
		}
		else if ( line == "[Poison Amount]" )
		{
			in >> nPoison;
		}
		else if ( line == "[Goal Amount]" )
		{
			in >> nGoal;
		}
	}
}

int GameSettings::GetTileSize() const
{
	return tileSize;
}

int GameSettings::GetBoardWidth() const
{
	return boardWidth;
}

int GameSettings::GetBoardHeight() const
{
	return boardHeight;
}

int GameSettings::GetNPoison() const
{
	return nPoison;
}

int GameSettings::GetNGoal() const
{
	return nGoal;
}

float GameSettings::GetSpeedUpRate() const
{
	return speedUpRate;
}
