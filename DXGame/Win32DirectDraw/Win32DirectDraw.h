#pragma once
#define INITGUID
#include "resource.h"

//#include "InputClass.h"
#include <math.h>
#include <windows.h>
#include <algorithm>
#include <utility>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <tchar.h>

#include <ddraw.h>

#include "Level.h"
#include "Vector.h"
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>

//#include "GameEngineLib.h"
#include "Game.h"
#include <math.h>
//-----------------------------------------------------------------------------
// Defines, and constants
//-----------------------------------------------------------------------------
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif


#define MAX_LOADSTRING 100

//#define D3DXVECTOR3 Vector;


//int DDraw_Fill_Surface(LPDIRECTDRAWSURFACE7 lpdds, USHORT color, RECT *client = NULL);




#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)



//Object obj;

//D3DXVECTOR3 eye(0.0f,0.0f,-100.0f);
//XMVECTORF32 eye = { 0.0f, 0.0f, -100.0f, 0.0f };
//XMVECTOR eye = XMVectorSet(0.0f, 0.0f, -100.0f, 0.0f);
/*Vector eye(0.0f, 0.0f, -100.0f);
Vector at(0.0f,0.0f,100.0f,0.0f);
Vector up(0.0f,1.0f,0.0f,0.0f);	
Vector eyeToVertex(0.0f,0.0f,0.0f);*/

DIMOUSESTATE mousestate;



<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> bfa5e409f5f7288bc0c852707a66a6c4eac9b4f7


Game game;
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
HINSTANCE hInst;
HWND main_window_handle;
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text	
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name


<<<<<<< HEAD
=======
=======
static void MoveCamera(float d)
{
	eye.y += d*moveDist*sin(pitch);
	eye.x += d*moveDist*cos(pitch)*cos(yaw);
	eye.z += d*moveDist*cos(pitch)*sin(yaw);
}
>>>>>>> f2bb61289de15cc22f3cae01fb96254a5d78474d
>>>>>>> bfa5e409f5f7288bc0c852707a66a6c4eac9b4f7

