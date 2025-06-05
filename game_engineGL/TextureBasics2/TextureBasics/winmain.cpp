// DEMOII7_2.CPP
// READ THIS!
// To compile make sure to include DDRAW.LIB, DSOUND.LIB,
// DINPUT.LIB, DINPUT8.LIB, WINMM.LIB in the project link list, and of course 
// the C++ source modules T3DLIB1-5.CPP and the headers T3DLIB1-5.H
// be in the working directory of the compiler

// INCLUDES ///////////////////////////////////////////////

#define INITGUID       // make sure al the COM interfaces are available
                       // instead of this you can include the .LIB file
                       // DXGUID.LIB


#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN 

#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <mmsystem.h>
#include <iostream> // include important C/C++ stuff
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h> 
#include <math.h>
#include <io.h>
#include <fcntl.h>

//#include <ddraw.h>  // directX includes
/*#include <dsound.h>
#include <dmksctrl.h>
#include <dmusici.h>
#include <dmusicc.h>
#include <dmusicf.h>*/
//#include <dinput.h>
//#include "T3DLIB1.h" // game library includes
//#include "T3DLIB2.h"
//#include "T3DLIB3.h"
//#include "T3DLIB4.h"
//#include "T3DLIB5.h"
#include "Object.h"
#include "Camera.h"
#include "Game.h"
#include "CGfxOpenGL.h"
#include "timer.h"

#define WINDOW_WIDTH      400 // size of window
#define WINDOW_HEIGHT     400
#define MOUSE_SENSITIVITY	10
bool exiting = false;
long windowWidth = 1680;// 1024;
long windowHeight = 1050; //768;
long windowBits = 24;
bool fullscreen = false;
HDC hDC;
Game game;

CGfxOpenGL *g_glRender = NULL;
CHiResTimer *g_hiResTimer = NULL;

HWND main_window_handle           = NULL; // save the window handle
//HINSTANCE main_instance           = NULL; // save the instance
Object obj;     // used to hold our mesh                   
Camera    *cam;     // the single camera

// initialize camera position and direction
Vector  cam_pos = {0,0,0,1};
Vector cam_dir = {0,0,0,1};

// all your initialization code goes here...
VECTOR4D vscale={5.0,5.0,5.0,1},  // scale of object
         vpos = {0,0,0,1},        // position of object
         vrot = {0,0,0,1};        // initial orientation of object

FILE* fp_error;

void SetupPixelFormat(HDC hDC)
{
	int pixelFormat;

	PIXELFORMATDESCRIPTOR pfd =
	{	
		sizeof(PIXELFORMATDESCRIPTOR),	// size
			1,							// version
			PFD_SUPPORT_OPENGL |		// OpenGL window
			PFD_DRAW_TO_WINDOW |		// render to window
			PFD_DOUBLEBUFFER,			// support double-buffering
			PFD_TYPE_RGBA,				// color type
			32,							// prefered color depth
			0, 0, 0, 0, 0, 0,			// color bits (ignored)
			0,							// no alpha buffer
			0,							// alpha bits (ignored)
			0,							// no accumulation buffer
			0, 0, 0, 0,					// accum bits (ignored)
			16,							// depth buffer
			0,							// no stencil buffer
			0,							// no auxiliary buffers
			PFD_MAIN_PLANE,				// main layer
			0,							// reserved
			0, 0, 0,					// no layer, visible, damage masks
	};

	pixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, pixelFormat, &pfd);
}

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hDC;
	static HGLRC hRC;
	int height, width;
	float angX, angY;
	static int prevX=0,prevY=0,xPos=0,yPos=0;
	int moveDist = 1;
	// dispatch messages
	switch (uMsg)
	{	
	case WM_CREATE:			// window creation
		hDC = GetDC(hWnd);
		SetupPixelFormat(hDC);
		//SetupPalette();
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);
		break;

	case WM_DESTROY:			// window destroy
	case WM_QUIT:
	case WM_CLOSE:					// windows is closing

		// deselect rendering context and delete it
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);

		// send WM_QUIT to message queue
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		height = HIWORD(lParam);		// retrieve width and height
		width = LOWORD(lParam);

		g_glRender->SetupProjection(width, height);
		break;

	case WM_ACTIVATEAPP:		// activate app
		break;

	case WM_PAINT:				// paint
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:		// left mouse button
		break;

	case WM_RBUTTONDOWN:		// right mouse button
		break;

	case WM_MOUSEMOVE:			// mouse movement
		xPos=GET_X_LPARAM(lParam)-prevX; 
		prevX = GET_X_LPARAM(lParam);				
		cam->dir.y = cam->dir.y+xPos;		
		while (cam->dir.y<0)
			cam->dir.y+=360;
		while (cam->dir.y>360)
			cam->dir.y-=360;
		Write_Error(fp_error,"cam.dir.y: %f\n",cam->dir.y);
		yPos = GET_Y_LPARAM(lParam)-prevY; 	
		prevY =GET_Y_LPARAM(lParam);
		while (cam->dir.x<0)
			cam->dir.x+=360;
		while (cam->dir.y>360)
			cam->dir.x-=360;
		cam->dir.x = cam->dir.x-yPos;
		game.mousestate.lX = xPos;
		game.mousestate.lY = yPos;
		break;

	case WM_LBUTTONUP:			// left button release
		break;

	case WM_RBUTTONUP:			// right button release
		break;

	case WM_KEYUP:
		break;

	case WM_KEYDOWN:
		int fwKeys;
		LPARAM keyData;
		fwKeys = (int)wParam;    // virtual-key code 
		keyData = lParam;          // key data 

		while (cam->dir.y<0)
			cam->dir.y+=360;
		while (cam->dir.y>360)
			cam->dir.y-=360;
		while (cam->dir.x<0)
			cam->dir.x+=360;
		while (cam->dir.x>360)
			cam->dir.x-=360;
		angY = cam->dir.y*3.14f/180.0f;
		angX = cam->dir.x*3.14f/180.0f;
		
		switch(fwKeys)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;			
		case VK_UP:				
			cam->pos.y += moveDist*sin(angX);
			cam->pos.x += moveDist*cos(angX)*cos(angY); 			
			cam->pos.z += moveDist*cos(angX)*sin(angY); 			
			break;
		case VK_DOWN:
			cam->pos.y += -moveDist*sin(angX);
			cam->pos.x += -moveDist*cos(angX)*cos(angY); 			
			cam->pos.z += -moveDist*cos(angX)*sin(angY); 			
			break;			
		case VK_LEFT:
			angY=angY-3.14f/2.0f;
			cam->pos.x += moveDist*cos(angY);
			cam->pos.z += moveDist*sin(angY); 						
			break;
		case VK_RIGHT:
			angY=angY+3.14f/2.0f;
			cam->pos.x += moveDist*cos(angY);
			cam->pos.z += moveDist*sin(angY); 						
			break;		
		default:
			break;
		}
		g_glRender->setCam(cam);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX windowClass;		// window class
	HWND	   hwnd;			// window handle
	MSG		   msg;				// message
	DWORD	   dwExStyle;		// Window Extended Style
	DWORD	   dwStyle;			// Window Style
	RECT	   windowRect;

	g_glRender = new CGfxOpenGL;
	g_hiResTimer = new CHiResTimer;

	windowRect.left=(long)0;						// Set Left Value To 0
	windowRect.right=(long)windowWidth;	// Set Right Value To Requested Width
	windowRect.top=(long)0;							// Set Top Value To 0
	windowRect.bottom=(long)windowHeight;	// Set Bottom Value To Requested Height

	// fill out the window class structure
	windowClass.cbSize			= sizeof(WNDCLASSEX);
	windowClass.style			= CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc		= MainWindowProc;
	windowClass.cbClsExtra		= 0;
	windowClass.cbWndExtra		= 0;
	windowClass.hInstance		= hInstance;
	windowClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);	// default icon
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);		// default arrow
	windowClass.hbrBackground	= NULL;								// don't need background
	windowClass.lpszMenuName	= NULL;								// no menu
	windowClass.lpszClassName	= "GLClass";
	windowClass.hIconSm			= LoadIcon(NULL, IDI_WINLOGO);		// windows logo small icon

	// register the windows class
	if (!RegisterClassEx(&windowClass))
		return 0;

	if (fullscreen)								// fullscreen?
	{
		DEVMODE dmScreenSettings;					// device mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);	
		dmScreenSettings.dmPelsWidth = windowWidth;			// screen width
		dmScreenSettings.dmPelsHeight = windowHeight;			// screen height
		dmScreenSettings.dmBitsPerPel = windowBits;				// bits per pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		int result = ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		if (result != DISP_CHANGE_SUCCESSFUL)
		{
			// setting display mode failed, switch to windowed
			MessageBox(NULL, "Display mode failed", NULL, MB_OK);
			fullscreen = FALSE;	
			switch (result)
			{
				case DISP_CHANGE_BADDUALVIEW:
					cout << "The settings change was unsuccessful because the system is DualView capable.";
					break;
				case DISP_CHANGE_BADFLAGS:
					cout << "An invalid set of flags was passed in.";
					break;
				case DISP_CHANGE_BADMODE:
					cout << "The graphics mode is not supported.";
					break;
				case DISP_CHANGE_BADPARAM:
					cout << "An invalid parameter was passed in. This can include an invalid flag or combination of flags.";
					break;
				case DISP_CHANGE_FAILED:
					cout << "The display driver failed the specified graphics mode.";
					break;
				case DISP_CHANGE_NOTUPDATED:
					cout << "Unable to write settings to the registry.";
					break;
				case DISP_CHANGE_RESTART:
					cout << "The computer must be restarted for the graphics mode to work.";
					break;
			}
		}
	}

	if (fullscreen)								// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;					// Window Extended Style
		dwStyle=WS_POPUP;						// Windows Style
		ShowCursor(FALSE);						// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;					// Windows Style
	}

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// class registered, so now create our window
	hwnd = CreateWindowEx(NULL,									// extended style
		"GLClass",							// class name
		"BOGLGP - Chapter 7 - Texture Basics",	// app name
		dwStyle | WS_CLIPCHILDREN |
		WS_CLIPSIBLINGS,
		0, 0,								// x,y coordinate
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top, // width, height
		NULL,								// handle to parent
		NULL,								// handle to menu
		hInstance,							// application instance
		NULL);								// no extra params

	hDC = GetDC(hwnd);

	// check if window creation failed (hwnd would equal NULL)
	if (!hwnd)
		return 0;

	ShowWindow(hwnd, SW_SHOW);			// display the window
	UpdateWindow(hwnd);					// update the window

	cam = new Camera(cam_pos, // initial camera position
		cam_dir,  // initial camera angles
		NULL,      // no target
		50.0,      // near and far clipping planes
		500.0,
		90.0,      // field of view in degrees
		WINDOW_WIDTH,   // size of final screen viewport
		WINDOW_HEIGHT);
	// initialize the camera with 90 FOV, normalized coordinates
	//Init_CAM4DV1(&cam,      // the camera object
 //            CAM_MODEL_EULER, // the euler model
 //            &cam_pos,  // initial camera position
 //            &cam_dir,  // initial camera angles
 //            NULL,      // no target
 //            50.0,      // near and far clipping planes
 //            500.0,
 //            90.0,      // field of view in degrees
 //            WINDOW_WIDTH,   // size of final screen viewport
 //            WINDOW_HEIGHT);
	fp_error = NULL;
	if (!g_glRender->Init(cam,fp_error))
	{
		MessageBox(NULL, "CGfxOpenGL::Init() error!", "CGfxOpenGL class failed to initialize!", MB_OK);
		return -1;
	}

	g_hiResTimer->Init();
	                       // general error file
	Open_Error_File("errors.log",fp_error);

	game.cam = cam;
	while (!exiting)
	{
		
		game.Game_Main();
		
		g_glRender->Prepare(g_hiResTimer->GetElapsedSeconds(1));
		g_glRender->Render();
		SwapBuffers(hDC);

		while (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage (&msg, NULL, 0, 0))
			{
				exiting = true;
				break;
			}

			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}
	}
	Close_Error_File(fp_error);
	delete g_hiResTimer;
	delete g_glRender;

	if (fullscreen)
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);						// Show Mouse Pointer
	}

	return (int)msg.wParam;
}