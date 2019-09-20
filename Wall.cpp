#include "stdafx.h"
#include "Wall.h"
#include "Board.h"
#include "Ball.h"

#define dUpWallY 1
#define dDownWallY 23

Wall::Wall(int x, int y)
:Board(x, y, y, false, false, false)
{
}

void Wall::collision(Ball &ball)
{
	if(ball.getypos()-Board::getYDownEnd()==1||ball.getypos()-Board::getYDownEnd()==(-1))
	{
		ball.setDirection(false,true);
	}
}

void Wall::setPosition(bool isUp)
{
	Board::Y_UpperEnd = (isUp)? dUpWallY:dDownWallY;
	Board::Y_LowerEnd = (isUp)? dUpWallY:dDownWallY;
}