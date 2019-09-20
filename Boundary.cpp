#include "stdafx.h"
#include "Boundary.h"
#include "vCanvas.h"
#include "Board.h"
#include "Ball.h"

#define dLeftBoundary 0
#define dRightBoundary (ConsoleBufferWidth-2)

/*
class Boundary : public Board
{
private:
	static int LPoint;
	static int RPoint;
	*/
int Boundary::LPoint = 0;
int Boundary::RPoint = 0;

	Boundary::Boundary(int x, int y, bool isl)
		:Board(x, y, y, false, false, isl)
	{
		resetPoint();
	}
	void Boundary::collision(Ball &ball)
	{
		if(ball.getxpos() == Board::getX())
		{
			if(Board::getIsLPlayer())
			{
				plusPoint(ball, true);
			}
			else
			{
				plusPoint(ball, false);
			}
		}			
	}
	void Boundary::resetPoint()
	{
		LPoint = 0, RPoint = 0;
	}
	void Boundary::plusPoint(Ball& ball, bool isLeftBoundaryHit)//reset ball here;
	{
		if(isLeftBoundaryHit)
		{
			RPoint++;
			ball.setBall(true);
		}
		else
		{
			LPoint++;
			ball.setBall(false);
		}
		ball.randDirection();		
	}
	int Boundary::getLpoint()
	{
		return LPoint;
	}
	int Boundary::getRpoint()
	{
		return RPoint;
	}

	void Boundary::setPosition(bool isLeft)
	{
		Board::X = (isLeft)?dLeftBoundary:dRightBoundary;
		Board::isLPlayer = isLeft;
	}