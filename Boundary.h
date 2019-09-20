#ifndef _BOUNDARY_H_
#define _BOUNDARY_H_

#include "Board.h"
#include "Ball.h"

class Boundary : public Board
{
private:
	static int LPoint ;
	static int RPoint ;
public:
	Boundary(int = 0, int = 0, bool = true);
	virtual void collision(Ball &);
	void resetPoint();
	void plusPoint(Ball&, bool);//reset ball here;
	static int getLpoint();
	static int getRpoint();
	virtual void setPosition(bool);
};

#endif