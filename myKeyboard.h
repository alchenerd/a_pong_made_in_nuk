//�X�۹C���{���]�p���� EX5-2 ��L�T�����B�z p.5-14 ~ p.5-26
//�o�O���F��C���i�檺�̨Τƪ���
//�w�p�NGetKeyboardState�令�t��GetKeyState��GetMyKeyState
//�ӻ{�䦳W(0x57),S(0x53),�W(VK_UP),�U(VK_DOWN),ENTER(VK_RETURN),ESCAPE(VK_ESCAPE)�@�p����
//�䤤W,S,�W,�U����Ĭ�B���s�o��
//�ץ�Keyboard.h�a�Ӫ����~

//�����Y�ɤ�CPP�ѦҡG	�C���{���]�p���� �f�ؼw�� ISBN 986-125-455-2
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
//��C���O�����
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