//#include "stdafx.h"
#include "Game.h"
#include "Object.h"
#include <iostream>


using namespace std;

USHORT RGB16Bit565(int r, int g, int b)
{
	// this function simply builds a 5.6.5 format 16 bit pixel
	// assumes input is RGB 0-255 each channel
	r >>= 3; g >>= 2; b >>= 3;
	return(_RGB16BIT565((r), (g), (b)));

} // end RGB16Bit565

//-----------------------------------------------------------------------------
int Game::DDraw_Fill_Surface(LPDIRECTDRAWSURFACE7 lpdds, USHORT color, RECT* client)
{
	DDBLTFX ddbltfx; // this contains the DDBLTFX structure

	// clear out the structure and set the size field 
	DDRAW_INIT_STRUCT(ddbltfx);

	// set the dwfillcolor field to the desired color
	ddbltfx.dwFillColor = color;

	// ready to blt to surface
	lpdds->Blt(client,     // ptr to dest rectangle
		NULL,       // ptr to source surface, NA            
		NULL,       // ptr to source rectangle, NA
		DDBLT_COLORFILL | DDBLT_WAIT,   // fill and wait                   
		&ddbltfx);  // ptr to DDBLTFX structure

	// return success
	return(1);
} // end DDraw_Fill_Surface

int Game::Game_Init(HINSTANCE hInst, HWND windowHandle)
{
	level = Level("world.lvl");
	////if (XMVerifySupport())
	//	//XMMatrix matrix();
	//LPDIRECTDRAW pDDraw = NULL;
	//LPDIRECTDRAWENUMERATEEXA pDirectDrawEnumerateEx = NULL;
	//HRESULT hr;

	//LPDIRECTDRAWCREATE pDDCreate = NULL;
	//level = Level("world.lvl");
	////hInstDDraw = LoadLibrary(L"ddraw.dll");
	//main_window_handle = windowHandle;
	//if (hInstDDraw)
	//{

	//	pDDCreate = (LPDIRECTDRAWCREATE)GetProcAddress(hInstDDraw, "DirectDrawCreate");
	//	if (pDDCreate)
	//	{
	//		hr = DirectDrawCreate(NULL, &pDDraw, NULL);
	//		if (hr != DD_OK)
	//		{
	//			return 0;
	//		}
	//		//pDDCreate(NULL, &pDDraw, NULL);

	//		if (SUCCEEDED(pDDraw->QueryInterface(IID_IDirectDraw7, (VOID**)&pDDraw7)))
	//		{
	//			DDSCAPS2 ddscaps;
	//			ZeroMemory(&ddscaps, sizeof(DDSCAPS2));
	//			ddscaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM;
	//		}


	//		// set cooperation to full screen
	//		hr = pDDraw7->SetCooperativeLevel(main_window_handle,
	//			DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX |
	//			DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT);
	//		if (hr != S_OK)
	//			return(0);

	//		// set display mode 
	//		hr = pDDraw7->SetDisplayMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, 0, 0);
	//		if (hr != S_OK)
	//			return(0);

	//		//// clear ddsd and set size
	//		DDRAW_INIT_STRUCT(ddsd);
	//		ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	//		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
	//		ddsd.dwBackBufferCount = 1;

	//		// create the primary surface
	//		hr = pDDraw7->CreateSurface(&ddsd, &lpddsprimary, NULL);
	//		if (hr != S_OK)
	//			return(0);

	//		// Get the pointer to the back buffer
	//		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
	//		HRESULT ddrval = lpddsprimary->GetAttachedSurface(&ddscaps, &lpddsback);
	//		if (ddrval != DD_OK)
	//		{
	//			//lpddsprimary->Release();
	//			return(false);
	//		}

	//		// get the pixel format of the primary surface
	//		DDPIXELFORMAT ddpf; // used to get pixel format

	//		// initialize structure
	//		DDRAW_INIT_STRUCT(ddpf);

	//		// query the format from primary surface
	//		lpddsprimary->GetPixelFormat(&ddpf);

	//		input = new InputClass(hInst, main_window_handle);
	//		D3DXMATRIX m_MatWorld;
	//		for (vector< Object >::iterator objIterator = level.objectList.begin(); objIterator != level.objectList.end(); objIterator++)
	//		{
	//			C3DModel model(objIterator->world_pos, objIterator->dir, objIterator->scale);				
	//			level.models.push_back(model);
	//		}

	//		// load the 24-bit image
	//	/*	if (!Load_Bitmap_File(&bitmap,"C://Users//Jason//Pictures//ff.bmp"))
	//		   return(0);*/

	//		   // copy the bitmap image to the primary buffer line by line
	//		   // notice the 24 to 32 bit conversion pixel by pixel

	//		   // lock the primary surface
	//		   //lpddsprimary->Lock(NULL,&ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT,NULL);

	//		   //// get video pointer to primary surfce
	//		   //DWORD *primary_buffer = (DWORD *)ddsd.lpSurface;      
	//		   //int size = sizeof(primary_buffer);
	//		   //unsigned int pixel;

	//		   /*	int padding = 0;
	//				   int scanlinebytes = WINDOW_WIDTH * 3;
	//   while ( ( scanlinebytes + padding ) % 4 != 0 )
	//	   padding++;
	//   int psw = scanlinebytes + padding;*/
	//   // process each line and copy it into the primary buffer
	//   //for (int index_y = 0; index_y < WINDOW_HEIGHT; index_y++)
	//   //	{
	//   //	for (int index_x = 0; index_x < WINDOW_WIDTH; index_x++)
	//   //		{
	//   //		// get BGR values
	//   //		/*UCHAR blue  = (bitmap.buffer[index_y*WINDOW_WIDTH*3 + index_x*3 + 0]),
	//   //			  green = (bitmap.buffer[index_y*WINDOW_WIDTH*3 + index_x*3 + 1]),
	//   //			  red   = (bitmap.buffer[index_y*WINDOW_WIDTH*3 + index_x*3 + 2]);*/

	//   //		// this builds a 32 bit color value in A.8.8.8 format (8-bit alpha mode)
	//   //		pixel = bitmap.buffer[index_y*WINDOW_WIDTH + index_x + 0];//_RGB32BIT(0,red,green,blue);

	//   //	//primary_buffer[index_x + (index_y*psw)] = pixel;

	//   //		// write the pixel
	//   //		primary_buffer[index_x + (index_y*ddsd.lPitch >> 2)] = pixel;

	//   //		} // end for index_x

	//   //	} // end for index_y
	//	}
	//	/*  Flip_Bitmap(bitmap.buffer,
	//		   bitmap.bitmapinfoheader.biWidth*(bitmap.bitmapinfoheader.biBitCount/8),
	//		   bitmap.bitmapinfoheader.biHeight);*/

	//		   //lpddsprimary->Unlock(NULL);
	//		   //DDraw_Fill_Surface(lpddsback,0);
	//	eye = Vector(0.0f, 0.0f, -100.0f);
	//	at = Vector(0.0f, 0.0f, 100.0f, 0.0f);
	//	up = Vector(0.0f, 1.0f, 0.0f, 0.0f);
	//	eyeToVertex = Vector(0.0f, 0.0f, 0.0f);
	//	yaw = 0;// 3.14 / 2;
	//	pitch = 0;
	//}

	return (1);
}

void Game::SetMouseState(DIMOUSESTATE mousestate)
{
	this->mousestate = mousestate;
}

void Game::SlideCamera(float h, float v)
{
	eye = cam->pos;
	yaw = yaw - 3.14f / 2.0f;
	double ang = yaw;    // game.yaw = PI/2
	float x = h * moveDist * cos(ang);
	float y = 0;
	float z = h * moveDist * sin(ang);

	eye += Vector(x, y, z);
	cam->pos = eye;
	//eye.x += h*moveDist*cos(ang); //(h is either a 1 or 0 to indicate)
	//eye.z += h*moveDist*sin(ang); //(movement in this plane or not)    
	//XMVectorSetY(eye.vect,eye.vect.z + (h * moveDist * sin(ang)));
}

void Game::MoveCamera(float d)
{
	
	/*float y;
	float x;
	float z;*/
	//double ang = yaw + 3.14 / 2;
	/*x = d * moveDist * cos(ang);
	y = d * moveDist * sin(pitch);
	z = d * moveDist * sin(ang);*/
	eye = cam->pos;
	float y = d * moveDist * sin(pitch);
	float x = d * moveDist * cos(pitch) * cos(yaw);
	float z = d * moveDist * cos(pitch) * sin(yaw);
	//game.eye.y += d*moveDist*sin(pitch);
	//game.eye.x += d*moveDist*cos(pitch)*cos(yaw);
	//game.eye.z += d*moveDist*cos(pitch)*sin(yaw);
	eye += Vector(x, y, z);	
	cam->pos = eye;
}

void Game::RotateCamera(float yaw, float pitch)
{
	at.y = eye.y + radius * sin(pitch);
	newHradius = radius * cos(pitch);
	at.x = eye.x + newHradius * cos(yaw);
	at.z = eye.z + newHradius * sin(yaw);

	up.x = eye.x - at.x;
	up.z = eye.z - at.z;
	up.y = eye.y + radius * sin(pitch + 3.14 / 2);

}

int Game::Game_Main()
{
	//Vector vec(0, 0.0f, 100.0f);
	//double length = vec.Length();
	//double theta = 3.14 / 2;
	

	//eye = cam->pos;
	
	while (cam->dir.y < 0)
		cam->dir.y += 360;
	while (cam->dir.y > 360)
		cam->dir.y -= 360;
	while (cam->dir.x < 0)
		cam->dir.x += 360;
	while (cam->dir.x > 360)
		cam->dir.x -= 360;
	yaw = cam->dir.y * 3.14f / 180.0f;
	pitch = cam->dir.x * 3.14f / 180.0f;

	#include "allScripts.txt" ;			

	//IF(KEY_DOWN(VK_W))	
	//	MoveCamera(1);	
	//IF(KEY_DOWN(VK_S))
	//	MoveCamera(-1);	

	//IF(KEY_DOWN(VK_A))
	//	SlideCamera(1, 0);
	//ELSEIF(KEY_DOWN(VK_D))
	//	SlideCamera(-1, 0);

	//IF(KEY_DOWN(VK_UP))
	//	MoveCamera(1);
	//ELSEIF(KEY_DOWN(VK_DOWN))
	//	MoveCamera(-1);

	//if (KEY_DOWN(VK_LEFT))
	//	SlideCamera(-1, 0);
	//else if (KEY_DOWN(VK_RIGHT))
	//	SlideCamera(1, 0);


	//IF(mousestate.lX > 0)
	//	yaw -= (3.14 / 180.0);
	//ELSEIF(mousestate.lX < 0)
	//	yaw += (3.14 / 180.0);

	//IF(mousestate.lY > 0)
	//	pitch -= (3.14 / 180.0);
	//ELSEIF(mousestate.lY < 0)
	//	pitch += (3.14 / 180.0);

	//RotateCamera(yaw, pitch);

	return 0;
}

void Game::Game_Shutdown()
{

}

// get the size of the text
int Game::GetTextSize(LPSTR a0)
{
	for (int iLoopCounter = 0; ; iLoopCounter++)
	{
		if (a0[iLoopCounter] == '\0')
			return iLoopCounter;
	}
}



