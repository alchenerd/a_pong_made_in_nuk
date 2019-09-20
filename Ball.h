#ifndef _BALL_H_
#define _BALL_H_

#define dLeftDefaultBallX LConsoleMidPoint
#define dRightDefaultBallX LConsoleMidPoint
#define dDefaultBallY 12
#define dBallmoverate 0

class Ball
{
private:
	int X;
	int Y;
	int Delay;
	int MaxDelay;
	bool isDown, isRight;
public:
	Ball(int = 0, int = 0, bool = false, bool = false, int = dBallmoverate, int = dBallmoverate);
	void setPosition(bool);
	void setDirection(bool,bool);
	void randDirection();
	void move();
	int getxpos()const;
	int getypos()const;
	bool getIsDown() const;
	void setDelay(int);
	int getDelay() const;
	void setMaxDelay(int);
	int getMaxDelay() const;
	void setBall(bool);
	void adjustYPosition(int);
};

#endif