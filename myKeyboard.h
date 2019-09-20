//出自遊戲程式設計概論 EX5-2 鍵盤訊息的處理 p.5-14 ~ p.5-26
//這是為了乓遊戲進行的最佳化版本
//預計將GetKeyboardState改成含有GetKeyState的GetMyKeyState
//承認鍵有W(0x57),S(0x53),上(VK_UP),下(VK_DOWN),ENTER(VK_RETURN),ESCAPE(VK_ESCAPE)共計六鍵
//其中W,S,上,下不能衝突且為連發鍵
//修正Keyboard.h帶來的錯誤

//本標頭檔及CPP參考：	遊戲程式設計概論 呂建德著 ISBN 986-125-455-2
//						msdn.microsoft.com

#pragma once

#include <windows.h>

class clQueue
{
private:
	unsigned int mCount;
	unsigned int mBufSize;
	int *mBuffer;
	unsigned int PushIndex, PopIndex;
	CRITICAL_SECTION CriticalSection;
private:
	void Critical_Enter(void)
	{ EnterCriticalSection(&CriticalSection); }
	void Critical_Leave(void)
	{ LeaveCriticalSection(&CriticalSection); }

public:
	clQueue() : mCount(0), mBufSize(50), mBuffer(NULL), PushIndex(0), PopIndex(0)
	{
		InitializeCriticalSection( &CriticalSection );
		mBuffer = new int[ mBufSize ];
	}
	~clQueue()
	{
		if( mBuffer != NULL )
		{
			delete [] mBuffer;
			mBuffer = NULL;
		}
		DeleteCriticalSection( &CriticalSection );
	}
	bool Push ( int nNum )
	{
		Critical_Enter();

		if( mCount >= mBufSize )
		{
			Critical_Leave();
			return false;
		}
		mBuffer[ PushIndex ] = nNum;
		PushIndex++;
		if( PushIndex >= mBufSize )
		{
			PushIndex = 0;
		}
		mCount++;

		Critical_Leave();
		return true;
	}

	bool Pop ( int &nNum )
	{
		Critical_Enter();

		if( mCount == 0 )
		{
			Critical_Leave();
			return false;
		}

		nNum = mBuffer[ PopIndex ];
		PopIndex++;
		if( PopIndex >= mBufSize )
		{
			PopIndex = 0;
		}
		mCount--;

		Critical_Leave();
		return true;
	}

	void Clear ( void )
	{
		Critical_Enter();
		PushIndex = PopIndex;
		mCount = 0;
		Critical_Leave();
	}
};

/////////
//佇列類別不更動
/////////

/////////////////////////////////////////////////////////
//define key type:
//
//hotkey:VK_UP, 0x57, VK_DOWN, 0x53
//
//couplekey:dont cares
//
//generalkey:VK_RETURN, VK_ESCAPE
//
//note:only use in game, use method getch() in menu;
/////////////////////////////////////////////////////////

#define D_HotKeyNumber 4
#define D_CoupleKeyNumber 0

#define D_KeyReadRate 64 //times per second
#define D_KeyReadSpace (1000/D_KeyReadRate) //span per read(ms)
#define D_QuickKeyDelay 0//10*D_KeyReadSpace = 0.5s

//////////////////////////////////////////////////////////
//key read class
//

class clKeyBoard
{
private:
	DWORD dwThreadId; //DWORD = double word

protected:
	clQueue Keys;

private:
	void StartKeyThread ( void );

public:
	clKeyBoard()
	{
		StartKeyThread();
	}
	virtual ~clKeyBoard()
	{
	}

	bool ReadKey ( unsigned int &KeyCode )
	{
		int nKeyCode;
		if( Keys.Pop( nKeyCode ) )
		{
			KeyCode = nKeyCode;
			return true;
		}
		return false;
	}

	bool WriteKey ( unsigned int KeyCode )
	{
		if ( Keys.Push( KeyCode ) )
		{
			return true;
		}
		return false;
	}

	void ClearBuffer( void )
	{
		Keys.Clear();
	}
};