#include "Board.h"
#include <assert.h>
#include "Snake.h"
#include "Goal.h"

Board::Board( Graphics& gfx )
	:
	gfx( gfx )
{}

void Board::DrawCell( const Location & loc,Color c )
{
	assert( loc.x >= 0 );
	assert( loc.x < width );
	assert( loc.y >= 0 );
	assert( loc.y < height );

	const int off_x = x + borderWidth + borderPadding;
	const int off_y = y + borderWidth + borderPadding;

	gfx.DrawRectDim( loc.x * dimension + off_x + cellPadding,loc.y * dimension + off_y + cellPadding,dimension - cellPadding * 2,dimension - cellPadding * 2,c );
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard( const Location & loc ) const
{
	return loc.x >= 0 && loc.x < width &&
		loc.y >= 0 && loc.y < height;
}

void Board::DrawBorder()
{
	const int top = y;
	const int left = x;
	const int bottom = top + (borderWidth + borderPadding) * 2 + height * dimension;
	const int right = left + (borderWidth + borderPadding) * 2 + width * dimension;

	// top
	gfx.DrawRect( left,top,right,top + borderWidth,borderColor );
	// left
	gfx.DrawRect( left,top + borderWidth,left + borderWidth,bottom - borderWidth,borderColor );
	// right
	gfx.DrawRect( right - borderWidth,top + borderWidth,right,bottom - borderWidth,borderColor );
	// bottom
	gfx.DrawRect( left,bottom - borderWidth,right,bottom,borderColor );
}

int Board::GetContents(const Location & loc) const
{
	return hasContent[ loc.y * width + loc.x ];
}

void Board::SpawnContent(std::mt19937 rng, const Snake & snek,  int contentType)
{
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist( rng );
		newLoc.y = yDist( rng );
	} while (snek.IsInTile( newLoc ) || GetContents( newLoc ) != 0);

	if (contentType == 1)
	{
		hasContent[newLoc.y * width + newLoc.x] = 1;
	} 
	else if (contentType == 2)
	{
		hasContent[newLoc.y * width + newLoc.x] = 2;
	}
	else 
	{
		hasContent[newLoc.y * width + newLoc.x] = 3;
	}
	
}

void Board::DrawContent()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int contentType = GetContents({ j,i });
			if (contentType != 0)
			{
				if (contentType == 1)
				{
					DrawCell({ j, i }, obstacleColor);
				}
				else if (contentType == 2)
				{
					DrawCell({ j, i }, foodColor);
				}
				else
				{
					DrawCell({ j, i }, poisonColor);
				}
			}
		}
	}
}

void Board::ConsumeContent(const Location& loc)
{
	const int contentType = GetContents(loc);
	assert( contentType == 2 || contentType == 3 );
	
	hasContent[loc.y * width + loc.x] = 0;
}