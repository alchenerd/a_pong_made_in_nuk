#ifndef _BOARD_H_
#define _BOARD_H_
#include "Ball.h"

#define dLeftBoardLine 10
#define dRightBoardLine (ConsoleBufferWidth-12)
#define dDefaultUend 10
#define dDefaultDend 14

class Board
{
protected:
	int X;
	int Y_UpperEnd;//small
	int Y_LowerEnd;//big
	bool isUp;
	bool isDown;
	bool isLPlayer;
	static int Countdown;
	static int Delay;
public:
	Board(int = 0, int = 0, int = 0, bool = false, bool = false, bool = true);
	int getX() const;
	int getYUpEnd() const;
	int getYDownEnd() const;
	bool getIsLPlayer() const;
	
	virtual void setPosition(bool);
	void move();
	virtual void collision(Ball &);

	void setIsUp(bool);
	void setIsDown(bool);

	static void setDelay(int);
	int getDelay() const;

	static void setCountDown(int);
	int getCountDown() const;
};

#endif