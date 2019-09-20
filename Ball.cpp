#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Ball.h"
#include "vCanvas.h"
using namespace std;


/*private:
	int X;
	int Y;
	int Delay;
	bool isDown, isRight;
*/
Ball::Ball(int x, int y, bool isD, bool isR, int delay, int maxd)
:X(x), Y(y), isDown(isD), isRight(isR), Delay(delay), MaxDelay(maxd)
{
	srand( (unsigned int)time(NULL) );
	setPosition(true);
	randDirection();
}

void Ball::setPosition(bool isLeftLose)
{
	X = (isLeftLose)? dLeftDefaultBallX:dRightDefaultBallX, Y = dDefaultBallY-2+rand()%5;
}

void Ball::randDirection()
{
	
	isDown = (rand()%2 == 1)? true:false;
	isRight = (rand()%2 == 1)? true:false;
}
void Ball::move()
{
	X += (isRight)? 2:(-2);
	Y += (isDown)? 1:(-1);
}
int Ball::getxpos()const
{
	return X;
}
int Ball::getypos()const
{
	return Y;
}

void Ball::setDirection(bool ChangeIsR,bool ChangeIsD)
{
	Beep(784,1000/64);
	if(ChangeIsR)
	{
		isRight = !isRight;
	}
	if(ChangeIsD)
	{
		isDown = !isDown;
	}
}
bool Ball::getIsDown() const
{
	return isDown;
}
	
void Ball::setDelay(int d)
{
	Delay = d;
}
int Ball::getDelay() const
{
	return Delay;
}

void Ball::setMaxDelay(int d)
{
	MaxDelay = d;
}
int Ball::getMaxDelay() const
{
	return MaxDelay;
}
void Ball::setBall(bool isleftlose)
{
	setPosition(isleftlose);
	setMaxDelay(4);
}
void Ball::adjustYPosition(int newY)
{
	if(newY>1&&newY<23)
		Y = newY;
	if(newY == 1 || newY == 23)
		X = (rand()%2 == 1)? X+2 : X-2;
}