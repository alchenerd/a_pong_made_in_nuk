#ifndef _WALL_H_
#define _WALL_H_

#include "Board.h"
#include "Ball.h"

class Wall : public Board
{
public:
	Wall(int = 0, int = 0);
	virtual void collision(Ball &);
	virtual void setPosition(bool);
};

#endif