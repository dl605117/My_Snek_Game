#pragma once

#include "Board.h"
#include <vector>

class Snake
{
private:
	class Segment
	{
	public:
		Segment( const Location& loc );
		Segment( Color snakeColor );
		void Follow( const Segment& next );
		void MoveBy( const Location& delta_loc );
		void Draw( Board& brd ) const;
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake( const Location& loc );
	void MoveBy( const Location& delta_loc );
	Location GetNextHeadLocation( const Location& delta_loc ) const;
	void GrowAndMoveBy( const Location& delta_loc );
	void Draw( Board& brd ) const;
	bool IsInTileExceptEnd( const Location& target ) const;
	bool IsInTile( const Location& target ) const;
	int GetLength() const;
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr int nBodyColors = 4;
	static constexpr Color bodyColor[ nBodyColors ] = {
		{ 10, 100, 32 },
		{ 10, 130, 48 },
		{ 18, 160, 48 },
		{ 10, 130, 48 }
	};
	std::vector<Segment> segments;
};