#include "Snake.h"
#include <assert.h>

Snake::Snake( const Location& loc )
{
	segments.emplace_back( loc );
}

void Snake::MoveBy( const Location& delta_loc )
{
	for( int i = (int)segments.size() - 1; i > 0; --i )
	{
		segments[i].Follow( segments[i - 1] );
	}
	segments.front().MoveBy( delta_loc );
}

Location Snake::GetNextHeadLocation( const Location& delta_loc ) const
{
	Location l( segments.front().GetLocation() );
	l.Add( delta_loc );
	return l;
}

void Snake::GrowAndMoveBy( const Location& delta_loc )
{
	segments.emplace_back( bodyColor[ (int)segments.size() % nBodyColors ] );
	MoveBy( delta_loc );
}

void Snake::Draw( Board & brd ) const
{
	for( const Segment& s : segments )
	{
		s.Draw( brd );
	}
}

bool Snake::IsInTileExceptEnd( const Location& target ) const
{
	for( int i = 0; i < (int)segments.size() - 1; ++i )
	{
		if( segments[i].GetLocation() == target )
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsInTile( const Location& target ) const
{
	for( const Segment& s : segments )
	{
		if( s.GetLocation() == target )
		{
			return true;
		}
	}
	return false;
}

int Snake::GetLength() const
{
	return (int)segments.size();
}

Snake::Segment::Segment( const Location& loc )
{
	this->loc = loc;
	c = Snake::headColor;
}

Snake::Segment::Segment( Color snakeColor )
{
	c = snakeColor;
}

void Snake::Segment::Follow( const Segment& next )
{
	loc = next.loc;
}

void Snake::Segment::MoveBy( const Location& delta_loc )
{
	assert( abs( delta_loc.x ) + abs( delta_loc.y ) == 1 );
	loc.Add( delta_loc );
}

void Snake::Segment::Draw( Board& brd ) const
{
	brd.DrawCell( loc,c );
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
