#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "myKeyboard.h"

int HotKeys [ D_HotKeyNumber ] = 
{ VK_UP, 0x57, VK_DOWN, 0x53 };

BOOL GetMyKeyState(PBYTE lpKeyState)
{
	const int all = 6;
	int allKeys [ all ] = 
	{ VK_UP, 0x57, VK_DOWN, 0x53, VK_ESCAPE, VK_RETURN };
	int loop;
	for( loop = 0 ; loop < all ; loop++ )
	{
		lpKeyState[loop] = (GetKeyState(allKeys[loop])>>8);
	}
	return TRUE;
}

//key read function

DWORD WINAPI ThreadFunc( LPVOID lpParam )
{
	const int Count = 6;
	int loop;
	BYTE KeyTable[Count];
	BYTE BackupTable[Count];
	clKeyBoard *lpKB = (clKeyBoard *)lpParam;
	bool HotKey, HotKeyPress;
	int HKdelay;
	short Res;

	if( lpKB == NULL ){ return 1; }

	memset ( KeyTable, 0, Count );
	memset ( BackupTable, 0, Count );
	HotKeyPress = false;
	HKdelay = 0;
	HotKey = false;

	while(true)
	{
		Res = GetKeyState( VK_F1 );

		if ( GetMyKeyState( PBYTE ( &KeyTable ) ) )
		{
			if((KeyTable[5]>>7) == 0 && (KeyTable[5]>>7) != (BackupTable[5]>>7) )
			{
				if( HotKey )
					{
						lpKB->ClearBuffer();
						HotKey = false;
					}
					lpKB->WriteKey(VK_RETURN);
			}
			if((KeyTable[4]>>7) == 0 && (KeyTable[4]>>7) != (BackupTable[4]>>7) )
			{
				if( HotKey )
					{
						lpKB->ClearBuffer();
						HotKey = false;
					}
					lpKB->WriteKey(VK_ESCAPE);
			}
			
			for( loop = 0 ; loop<D_HotKeyNumber ; loop++ )
			{
				if((KeyTable[loop]>>7) != 0 && (KeyTable[loop]>>7) != (BackupTable[loop]>>7) && !HotKey )
				{
					HotKey = true;
				}

				if((KeyTable[loop]>>7) == 0 && (KeyTable[loop]>>7) != (BackupTable[loop]>>7) && HotKey)
				{
					lpKB->WriteKey( HotKeys[loop] );
					HotKeyPress = false;					
				}
				else if ( (KeyTable[loop]>>7) != 0 && !HotKeyPress && (KeyTable[loop]>>7) == (BackupTable[loop]>>7) && HotKey )
				{
					HotKeyPress = true;
					HKdelay = D_QuickKeyDelay;
				}
			}
			
			if( HotKeyPress )
			{
				if( HKdelay > 0 )
				{
					--HKdelay;
				}
				if( HKdelay == 0 )
				{
					for( loop = 0 ; loop < D_HotKeyNumber ; loop++ )
					{
						if( (KeyTable[loop]>>7) != 0 && HotKey)
						{
							lpKB->WriteKey(HotKeys[loop]);
						}
					}
				}
			}

			memcpy ( BackupTable, KeyTable, Count );
		}

		Sleep( D_KeyReadSpace );
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////

void clKeyBoard::StartKeyThread( void )
{
	HANDLE hThread;

	hThread = CreateThread( NULL, 0, ThreadFunc, this, 0, &dwThreadId );
	if(hThread = NULL)
	{
		std::cout << "CreateThread failed." << std::endl;
	}
	else
	{
		CloseHandle( hThread );
	}
}