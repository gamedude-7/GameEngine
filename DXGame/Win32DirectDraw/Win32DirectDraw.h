#pragma once
#define INITGUID
#include "resource.h"
#include "C3DModel.h"
#include "InputClass.h"
#include <math.h>

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <tchar.h>

#include <ddraw.h>

#include "Level.h"

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

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600
#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600
#define SCREEN_BPP		16
// initializes a direct draw struct
#define DDRAW_INIT_STRUCT(ddstruct) { memset(&ddstruct,0,sizeof(ddstruct)); ddstruct.dwSize=sizeof(ddstruct); }



// container structure for bitmaps .BMP file
typedef struct BITMAP_FILE_TAG
        {
        BITMAPFILEHEADER bitmapfileheader;  // this contains the bitmapfile header
        BITMAPINFOHEADER bitmapinfoheader;  // this is all the info including the palette
        unsigned int           *buffer;           // this is a pointer to the data

        } BITMAP_FILE, *BITMAP_FILE_PTR;


HINSTANCE hInst;	
 HINSTANCE hInstDDraw;
 LPDIRECTDRAW7 pDDraw7;
 DDSURFACEDESC2        ddsd;                  // a direct draw surface description struct
 DDSCAPS2 ddscaps;
 HWND main_window_handle;
 BITMAP_FILE           bitmap;                // holds the bitmap
 LPDIRECTDRAWSURFACE7  lpddsprimary = NULL;   // dd primary surface
LPDIRECTDRAWSURFACE7  lpddsback    = NULL;   // dd back surface
int DDraw_Fill_Surface(LPDIRECTDRAWSURFACE7 lpdds, USHORT color, RECT *client = NULL);
unsigned int ExtractGreen(unsigned int nSourceColor);
unsigned short ConvertRGB888toRGB565(unsigned int nSourceColor);
int Draw_Pixel16(int x, int y,int color,UCHAR *video_buffer, int lpitch);
int Draw_Line16(int xo, int yo, int x1,int y1, int color,UCHAR *vb_start,int lpitch);
int Draw_Clip_Line(int x0,int y0, int x1, int y1, int color, 
                    UCHAR *dest_buffer, int lpitch);
int Clip_Line(int &x1,int &y1,int &x2, int &y2);
// this builds a 16 bit color value in 5.6.5 format (green dominate mode)
#define _RGB16BIT565(r,g,b) ((b & 31) + ((g & 63) << 5) + ((r & 31) << 11))

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

Level level("world.lvl");
D3DXMATRIX m_MatWorld;
Object obj;
D3DXVECTOR3 eye(0.0f,0.0f,-100.0f);
D3DXVECTOR3 at(0.0f,0.0f,100.0f);
D3DXVECTOR3 up(0.0f,1.0f,0.0f);	
Vector eyeToVertex(0.0f,0.0f,0.0f);
InputClass *input;
DIMOUSESTATE mousestate;
double yaw = 3.14/2;
double pitch = 0;
double radius = 100;
double newHradius;
double dot = 0;
double moveDist = 1;
int Game_Init();
int Game_Main();
void Game_Shutdown();
typedef HRESULT ( WINAPI* LPDIRECTDRAWCREATE )( GUID FAR *lpGUID, LPDIRECTDRAW FAR *lplpDD, IUnknown FAR *pUnkOuter );
int Load_Bitmap_File(BITMAP_FILE_PTR bitmap, char *filename);
int Flip_Bitmap(unsigned int *image, int bytes_per_line, int height);

// these defined the general clipping rectangle
int min_clip_x = 0,                             // clipping rectangle 
    max_clip_x = (SCREEN_WIDTH-1),
    min_clip_y = 0,
    max_clip_y = (SCREEN_HEIGHT-1);

static void SlideCamera(float h, float v)
{
	double ang = yaw+3.14/2;
	eye.x += h*moveDist*cos(ang); //(h is either a 1 or 0 to indicate)
	eye.z += h*moveDist*sin(ang); //(movement in this plane or not)
}

static void MoveCamera(float d)
{
	eye.y += d*moveDist*sin(pitch);
	eye.x += d*moveDist*cos(pitch)*cos(yaw);
	eye.z += d*moveDist*cos(pitch)*sin(yaw);
}