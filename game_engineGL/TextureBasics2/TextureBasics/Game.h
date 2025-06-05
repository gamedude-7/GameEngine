#pragma once
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
//#include <io.h>
#include <fcntl.h>
#include <direct.h>
#include <wchar.h>
#include <ddraw.h>      // needed for defs in T3DLIB1.H 
#include <algorithm>
#include <utility>
#include <vector>
//#include "T3DLIB1.H"    // T3DLIB4 is based on some defs in this 
//#include "T3DLIB4.H"
//#include "T3DLIB5.H"
//#include "T3DLIB6.h"
//#include "stdafx.h"
#include "GAMEENGINELIB.H"
//#include "InputClass.h"

#include <windows.h>
#include <algorithm>
#include <utility>

#include "Vector.h"
//#include <DirectXMath.h>
//#include <DirectXPackedVector.h>
//#include <DirectXColors.h>
//#include <DirectXCollision.h>
#include "Level.h"
#include "ScriptTrans.h"
//#include "allScripts.txt" ;			
#include "Camera.h"
using namespace DirectX;
using namespace std;


#define BITMAP_ID            0x4D42 // universal id for a bitmap

// initializes a direct draw struct
#define DDRAW_INIT_STRUCT(ddstruct) { memset(&ddstruct,0,sizeof(ddstruct)); ddstruct.dwSize=sizeof(ddstruct); }

// this builds a 16 bit color value in 5.6.5 format (green dominate mode)
#define _RGB16BIT565(r,g,b) ((b & 31) + ((g & 63) << 5) + ((r & 31) << 11))

#define XMFLOAT4X4 XMMATRIX

typedef HRESULT(WINAPI* LPDIRECTDRAWCREATE)(GUID FAR* lpGUID, LPDIRECTDRAW FAR* lplpDD, IUnknown FAR* pUnkOuter);


typedef struct _DIMOUSESTATE {
	LONG    lX;
	LONG    lY;
	LONG    lZ;
	BYTE    rgbButtons[4];
} DIMOUSESTATE, * LPDIMOUSESTATE;

//extern BITMAP_FILE           bitmap;                // holds the bitmap	


class Game
{	
	//HINSTANCE hInstDDraw;
	//LPDIRECTDRAW7 pDDraw7;
	//DDSURFACEDESC2        ddsd;                  // a direct draw surface description struct
	//DDSCAPS2 ddscaps;
	HWND main_window_handle;
	double moveDist = 1;
	
	double radius = 100;
	double newHradius;
	float pitch;
	float yaw; 
public:
	//InputClass* input;

	D3DXMATRIX view,projCoordinates;
	Vector eye;
	Vector at;
	Vector up;
	Vector eyeToVertex;
	Camera *cam;
	vector<D3DXMATRIX> obj;
	vector<D3DXMATRIX> obj_vertices;
	LPDIRECTDRAWSURFACE7  lpddsprimary = NULL;   // dd primary surface
	LPDIRECTDRAWSURFACE7  lpddsback = NULL;   // dd back surface
	Level level;
	void Game_Shutdown();
	int Game_Main();
	int Game_Init(HINSTANCE hInst, HWND windowHandle);
	int DDraw_Fill_Surface(LPDIRECTDRAWSURFACE7 lpdds, USHORT color, RECT* client);
	int GetTextSize(LPSTR a0);
	void MoveCamera(float d);
	void RotateCamera(float yaw, float pitch);
	void SlideCamera(float h, float v);
	void SetMouseState(DIMOUSESTATE mousestate);
	D3DXMATRIX Tcam_inv,yawRot, pitchRot;
	DIMOUSESTATE mousestate;
};

