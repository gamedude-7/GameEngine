// Win32DirectDraw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <iostream>
#include "Win32DirectDraw.h"

using namespace std;

#define MAX_LOADSTRING 100
#define BITMAP_ID            0x4D42 // universal id for a bitmap

// this builds a 32 bit color value in A.8.8.8 format (8-bit alpha mode)
//#define _RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))
#define _RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))

// Global Variables:
							// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);





USHORT RGB16Bit565(int r, int g, int b)
{
// this function simply builds a 5.6.5 format 16 bit pixel
// assumes input is RGB 0-255 each channel
r>>=3; g>>=2; b>>=3;
return(_RGB16BIT565((r),(g),(b)));

} // end RGB16Bit565

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32DIRECTDRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32DIRECTDRAW));

	Game_Init();
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Game_Main();
		
		// TODO: Add any drawing code here...
		//SetTextColor(hdc, RGB(0,0,255));
		//SetBkMode(hdc, OPAQUE);
		//TextOut(hdc,10,10, L"test", GetTextSize(TextArray[0]));

		if (KEY_DOWN( VK_ESCAPE))
			break;
		
		if (KEY_DOWN( VK_UP ))
			MoveCamera(1);
			//eye.z+=1;
		else if (KEY_DOWN( VK_DOWN))
			MoveCamera(-1);
			//eye.z-=1;
			//SlideCamera(-1,0);	
		

		if (KEY_DOWN( VK_LEFT ))
		{
			SlideCamera(1,0);
		//	eye.x -= 1;
		//	at.x -= 1;
		}
		else if (KEY_DOWN( VK_RIGHT))
		{
			SlideCamera(-1,0);
			//eye.x += 1;
			//at.x += 1;
		}

		if (KEY_DOWN( VK_PAUSE))
			eyeToVertex.z = eyeToVertex.z;

		HRESULT hr = input->lpdimouse->GetDeviceState(sizeof(DIMOUSESTATE),(LPVOID)&mousestate);
		if (FAILED(hr))
		{
			/* error */
		}

		//D3DVECTOR v;
		//v = at - eye;
		Vector vec(0,0.0f,100.0f);
		
		if (mousestate.lX > 0)
			yaw -= (3.14/180.0);
		else if (mousestate.lX < 0)
			yaw += (3.14/180.0);

		if (mousestate.lY > 0)
			pitch -= (3.14/180.0);
		else if (mousestate.lY < 0)
			pitch += (3.14/180.0);

		while (yaw > (3.14*2))
			yaw-=(2*3.14);
		while (yaw < 0)
			yaw+=(2*3.14);

		while (pitch > (3.14*2))
			pitch-=(2*3.14);
		while (pitch < 0)
			pitch+=(2*3.14);

		double length = vec.Length();
		double theta = 3.14/2;
	/*	if (yaw < (3.14/2)) // 1st quadrant
		{
			theta = yaw;
			at.x = eye.x + (vec.Length() * cos(theta));
			at.z = eye.z + (vec.Length() * sin(theta));
		}
		else if (yaw > (3.14/2) && yaw < 3.14) // 2nd quadrant
		{
			theta = yaw - 3.14/2;
			at.x = eye.x -(vec.Length() * sin(theta));
			at.z = eye.z + (vec.Length() * cos(theta));									
		}		
		else if (yaw > 3.14 && yaw < (3.14+3.14/2)) // 3rd quadrant
		{
			theta = yaw - 3.14;
			at.x = eye.x - (vec.Length() * sin(theta));
			at.z = eye.z - (vec.Length() * cos(theta));	
		}
		else if (yaw < 3.14*2 && yaw > (3.14+3.14/2)) // 4th quadrant
		{
			theta = yaw -(3.14+3.14/2);
			at.x = eye.x + (vec.Length() * sin(theta));
			at.z = eye.z -(vec.Length() * cos(theta));	
		}

		if (pitch < (3.14/2)) // 1st quadrant
		{
			theta = pitch;
			at.y =  (vec.Length() * cos(theta));
			at.z = (vec.Length() * sin(theta));
		}
		else if (pitch > (3.14/2) && pitch < 3.14) // 2nd quadrant
		{
			theta = pitch - 3.14/2;
			at.y =  -(vec.Length() * sin(theta));
			at.z = (vec.Length() * cos(theta));									
		}		
		else if (pitch > 3.14 && pitch < (3.14+3.14/2)) // 3rd quadrant
		{
			theta = pitch - 3.14;
			at.y =  -(vec.Length() * sin(theta));
			at.z = -(vec.Length() * cos(theta));	
		}
		else if (pitch < 3.14*2 && pitch > (3.14+3.14/2)) // 4th quadrant
		{
			theta = pitch -(3.14+3.14/2);
			at.y = (vec.Length() * sin(theta));
			at.z = -(vec.Length() * cos(theta));	
		}*/
		//double costheta = cos(theta);
		//double sintheta = sin(theta);
		at.y = eye.y + radius * sin(pitch);
		newHradius = radius *cos(pitch);
		at.x = eye.x + newHradius * cos(yaw);
		at.z = eye.z + newHradius * sin(yaw);

		up.x = eye.x - at.x;
		up.z = eye.z - at.z;
		up.y = eye.y + radius * sin(pitch+ 3.14/2);
	}

	Game_Shutdown();
	return (int) msg.wParam;
}


int DDraw_Fill_Surface(LPDIRECTDRAWSURFACE7 lpdds, USHORT color, RECT *client)
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

int Game_Main()
{
	// load the 24-bit image
	/*if (!Load_Bitmap_File(&bitmap,"C://Users//Jason//Pictures//ff.bmp"))
		return(0);*/

	
	
	
	//lpddsprimary->GetAttachedSurface(&ddscaps, &lpddsback);

	//DDSURFACEDESC2 ddsd;
	//IDirectDrawSurface7 *pdds;

	////
	//// create a DirectDrawSurface for this bitmap
	////
	//ZeroMemory(&ddsd, sizeof(ddsd));
	//ddsd.dwSize = sizeof(ddsd);
	//ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
	//ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	//ddsd.dwWidth = WINDOW_WIDTH;
	//ddsd.dwHeight = WINDOW_HEIGHT;

	//if (pDDraw7->CreateSurface(&ddsd, &lpddsback, NULL) != DD_OK)
	//{
	//	return 0;
	//} 
	//
	//
	// clear the drawing surface
	DDraw_Fill_Surface(lpddsback, RGB16Bit565(255,255,255));
	//// lock the primary surface
	DDRAW_INIT_STRUCT(ddsd);
	lpddsback->Lock(NULL,&ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT,NULL);

	//// get video pointer to primary surfce
	UCHAR *back_buffer = (UCHAR *)ddsd.lpSurface;    

	D3DXMATRIX out;

	D3DXMATRIX *view = D3DXMatrixLookAtLH(&out, &eye, &at, &up);

	//for (int i=0; i < level.objectList.size(); i++)
	for (vector< Object >::iterator objIterator = level.objectList.begin(); objIterator !=  level.objectList.end(); objIterator++)
	{

		C3DModel model(&m_MatWorld, objIterator->world_pos, objIterator->dir);
		D3DXMATRIX projectionMatrix = model.ProjectionMatrix( 100.00f, 10000.0f, 0.785f, 0.785f);	
		D3DXMATRIX cameraCoordinates, screenCoordinates, projCoordinates; 
		level.models.push_back(model);
		D3DXMatrixMultiply(&cameraCoordinates,&m_MatWorld,view);
		D3DXMatrixMultiply(&projCoordinates,&cameraCoordinates, &projectionMatrix);

		vector<D3DXMATRIX> obj_world;
			
		vector<D3DXMATRIX> obj;
	
		for (int i = 0; i < objIterator->num_vertices; i++)
		{
				
			D3DXMATRIX matrixWorld;
			float x = matrixWorld.m[0][0] = objIterator->vlist_local[i].getX();// + obj_rotate[i].m[0][0];
			float y = matrixWorld.m[0][1] = objIterator->vlist_local[i].getY();// + obj_rotate[i].m[0][1];
			float z = matrixWorld.m[0][2] = objIterator->vlist_local[i].getZ();// + obj_rotate[i].m[0][2];
			matrixWorld.m[0][3] = 1;
			for (int j = 1; j < 4; j++)
			{
				matrixWorld.m[j][0] = 0;
				matrixWorld.m[j][1] = 0;
				matrixWorld.m[j][2] = 0;
				matrixWorld.m[j][3] = 0;
			}

			obj_world.push_back(matrixWorld);
			float curr_radius =  x*x + y*y + z*z;
			if (curr_radius > objIterator->max_radius)
			{
				objIterator->setMaxRadius( curr_radius);
			}
		}

		for (int i = 0; i < obj_world.size(); i++)
		{
				
			D3DXMATRIX matrixObj;
			D3DXMatrixMultiply(&matrixObj,&obj_world[i],&projCoordinates);
			obj.push_back(matrixObj);				
		}

		float x =  cameraCoordinates.m[3][0];
		float y = cameraCoordinates.m[3][1];
		//float z = objIterator->world_pos.getZ() ;
		float z =cameraCoordinates.m[3][2];// + objIterator->world_pos.getZ() * cameraCoordinates.m[3][2];
		if ( z > (eye.z + 10000) || z < (eye.z + 100) )
			continue;
		

		if (fabs(x) > z || fabs(y) > z )
					continue;

		vector<Point> pts;
		vector<Point> vertices;
		for (int i = 0; i < obj.size(); i++)
		{
			Point obj_per, pt, vertex;
				
			obj_per.x = obj[i]._11/obj[i]._13;
			obj_per.y = obj[i]._12/obj[i]._13;

			vertex.x = obj[i]._11;
			vertex.y = obj[i]._12;
			vertex.z = obj[i]._13;
			vertices.push_back(vertex);
				
			pt.x = SCREEN_WIDTH/2 + obj_per.x * (SCREEN_WIDTH/2);
			pt.y = SCREEN_HEIGHT - (SCREEN_HEIGHT/2 + obj_per.y * (SCREEN_HEIGHT/2));
			if (pt.x > 0 && pt.x < SCREEN_WIDTH && pt.y > 0 && pt.y < SCREEN_HEIGHT && pt.z < 0)
			{
				if (back_buffer != NULL)
					Draw_Pixel16(pt.x,pt.y, RGB16Bit565(255,255,255), back_buffer, ddsd.lPitch);
			}
			pts.push_back(pt);
		}

		/*while (angle > (3.14*2))
			angle-=(2*3.14);
		while (angle < 0)
			angle+=(2*3.14);
		Vector right(cos(angle-(3.14/2)), 0.0, sin(angle-(3.14/2)) );*/
			
		bool skip = false;
		for (int poly = 0; poly < objIterator->num_polys; poly++)
        {       
			Vector v[3];
			for (int i=0; i<3; i++)
			{
				//need to take cross product of 2 edges of the triangle
				v[i] = Vector(vertices[objIterator->plist[poly].vert[i]].getX(),vertices[objIterator->plist[poly].vert[i]].getY(),vertices[objIterator->plist[poly].vert[i]].getZ());
			/*	Vector normal = vertices[objIterator->plist[poly].vert[i]]
				Vector vec(vertices[objIterator->plist[poly].vert[i]].getX() - eye.x, vertices[objIterator->plist[poly].vert[i]].getY() - eye.y,  vertices[objIterator->plist[poly].vert[i]].getZ() - eye.z  );
				Vector lookat(at.x,at.y,at.z);
				eyeToVertex = vec;
				vec.Normalize();
				dot = vec.dot(lookat);
				
				if (dot < 0 )
					skip = true;*/

			//	if ( vec.z < 0)
				//	skip = true;
			}
			Vector v01 = v[0] - v[1];
			Vector v02 = v[2] - v[1];
			Vector norm = v01.cross(v02);
			Vector lookat(at.x,at.y,at.z);
			Vector view = lookat - v[0];
			dot = norm.dot(view);
			
			

			/*if (dot < 0 )
			{
			//	skip = false;
				continue;
			}*/

			if (back_buffer!=NULL && dot > 0 ) {
				Draw_Clip_Line( pts[objIterator->plist[poly].vert[0]].getX(), pts[objIterator->plist[poly].vert[0]].getY(), pts[objIterator->plist[poly].vert[1]].getX(), pts[objIterator->plist[poly].vert[1]].getY(), RGB16Bit565(255,0,0), back_buffer, ddsd.lPitch);				
				Draw_Clip_Line( pts[objIterator->plist[poly].vert[1]].getX(), pts[objIterator->plist[poly].vert[1]].getY(), pts[objIterator->plist[poly].vert[2]].getX(), pts[objIterator->plist[poly].vert[2]].getY(), RGB16Bit565(0,255,0), back_buffer, ddsd.lPitch);
				Draw_Clip_Line( pts[objIterator->plist[poly].vert[2]].getX(), pts[objIterator->plist[poly].vert[2]].getY(), pts[objIterator->plist[poly].vert[0]].getX(), pts[objIterator->plist[poly].vert[0]].getY(), RGB16Bit565(0,0,255), back_buffer, ddsd.lPitch);
				//skip = false;
			}
        }
	}

			
	/*int size = sizeof(back_buffer);*/
	//vector< Object >::const_iterator objIterator;
	//vector<Object> obj_per;
	////for (int i=0; i < level.objectList.size(); i++)
	//for (objIterator = level.objectList.begin(); objIterator !=  level.objectList.end(); objIterator++)	
	//{
	//	//for (int j=0; j < level.objectList[i].num_polys; j++)
	/*	for (int i=0; i < objIterator->num_vertices; i++)
		{	*/		
	//	//	for (int k=0; k < objIterator->plist.size(); k++)
	//		/*for (int k=0; k < level.objectList[i].plist.size(); k++)
	//		{*/

				//Draw_Pixel16(level.matrices[i].m[0][0],level.matrices[i].m[1][1], RGB16Bit565(255,0,0), back_buffer, ddsd.lPitch);
	//		//}
		//}
	//	
	////	Draw_Line16(0,0,100,100,RGB16Bit565(0,0,0), back_buffer, ddsd.lPitch);
	//}
	 
	unsigned int pixel;
	
		
	//// process each line and copy it into the primary buffer
	//for (int index_y = 0; index_y < WINDOW_HEIGHT; index_y++)
	//{
	//	for (int index_x = 0; index_x < WINDOW_WIDTH; index_x++)
	//	{
	//	// get BGR values
	//	/*UCHAR blue  = (bitmap.buffer[index_y*WINDOW_WIDTH*3 + index_x*3 + 0]),
	//			green = (bitmap.buffer[index_y*WINDOW_WIDTH*3 + index_x*3 + 1]),
	//			red   = (bitmap.buffer[index_y*WINDOW_WIDTH*3 + index_x*3 + 2]);*/

	//	// this builds a 32 bit color value in A.8.8.8 format (8-bit alpha mode)
	//	pixel = bitmap.buffer[index_y*WINDOW_WIDTH + index_x ];//_RGB32BIT(0,red,green,blue);

	////primary_buffer[index_x + (index_y*psw)] = pixel;


	//	// write the pixel
	//	if (back_buffer!=NULL)
	//		back_buffer[index_x + (index_y*(ddsd.lPitch >> 1))] = ConvertRGB888toRGB565(pixel);

	//	} // end for index_x

	//} // end for index_y

	RECT screen_rect = {0,0,WINDOW_WIDTH,WINDOW_HEIGHT};
    lpddsback->Unlock(&screen_rect);
    //lpddsprimary->SetSurfaceDesc(&ddsd,*back_buffer);

	lpddsprimary->Flip(NULL, DDFLIP_WAIT);

	

	return 0;
}

unsigned int ExtractGreen(unsigned int nSourceColor)
{
	unsigned int RGBGreen;

	RGBGreen = nSourceColor & 0x0000FF00;
	return RGBGreen;
}

unsigned short ConvertRGB888toRGB565(unsigned int nSourceColor)
{
	unsigned short RGB565;
	// bring r,g, and b to the last 16 bits
	unsigned short r = ((nSourceColor >> 16) & 0x000000FF) ; 
	unsigned short g = ((nSourceColor >> 8) & 0x000000FF);
	unsigned short b = (nSourceColor & 0x000000FF) ;

	// if you have three 8 bit numbers, and you want 5 6 5
	//(8 - 3) - 5 bits
	//(8 - 2) - 6 bits
	//(8 - 3) - 5 bit
	//  unsigned short  B =  (b  >> 3)        & 0x001F;
 //   unsigned short  G = ((g >> 2) <<  5) & 0x07E0; // not <
 //   unsigned short  R = ((r   >> 3) << 11) & 0xF800; // not <

	//RGB565 = (R | G | B);
	// shift them to fit in 565 format 
	RGB565 = ((r << 8) & 0xF800) | ((g << 3) & 0x07E0) | ((b>>3) & 0x001F);
	return RGB565;
}
//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;// LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32DIRECTDRAW));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);// (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;// MAKEINTRESOURCE(IDC_WIN32DIRECTDRAW);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   //HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   main_window_handle = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

 /*  if (!main_window_handle)
   {
      return FALSE;
   }*/

  // ShowWindow(main_window_handle, nCmdShow);
   //UpdateWindow(main_window_handle);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//

// Function I made to get the size of the text
int GetTextSize (LPSTR a0)
{
    for (int iLoopCounter = 0; ;iLoopCounter++)
    {
        if (a0 [iLoopCounter] == '\0')
            return iLoopCounter;
    }
}

LPSTR TextArray [] = {
    "Test"
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc = GetDC(hWnd);

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		/*hdc = BeginPaint(hWnd, &ps);*/
		// TODO: Add any drawing code here...

		SetTextColor(hdc, RGB(0,0,255));
		SetBkMode(hdc, OPAQUE);
		//TCHAR buf[80];
		
		wchar_t buf[100];
		swprintf(buf, L"dot product: %f", dot);

		TextOut(hdc,10,10, buf, wcslen(buf));

		swprintf(buf, L"Eye: %f %f %f", eye.x, eye.y, eye.z);
		TextOut(hdc,10,30, buf, wcslen(buf));
	
		swprintf(buf, L"at: %f %f %f", at.x, at.y, at.z);
		TextOut(hdc,10,50, buf, wcslen(buf));


		/*swprintf(buf, L"Eye: %f", level.objectList[0].plist[0].vert[0]);
		TextOut(hdc,10,50, buf, wcslen(buf));*/
		
		//EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


//-----------------------------------------------------------------------------
//BOOL WINAPI DDEnumCallbackEx( GUID FAR* lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext, HMONITOR hm )
// {
//    UNREFERENCED_PARAMETER( lpDriverDescription );
//
//    DDRAW_MATCH* pDDMatch = ( DDRAW_MATCH* ) lpContext;
//    if( pDDMatch->hMonitor == hm )
//    {
//        pDDMatch->bFound = true;
//        strcpy_s( pDDMatch->strDriverName, 512, lpDriverName );
//        memcpy( &pDDMatch->guid, lpGUID, sizeof( GUID ) );
//    }
//    return TRUE;
//}

//-----------------------------------------------------------------------------
int Game_Init()
{
    LPDIRECTDRAW pDDraw = NULL;
    LPDIRECTDRAWENUMERATEEXA pDirectDrawEnumerateEx = NULL;
    HRESULT hr;

    LPDIRECTDRAWCREATE pDDCreate = NULL;

    hInstDDraw = LoadLibrary( L"ddraw.dll" );
    if( hInstDDraw )
    {
        pDDCreate = ( LPDIRECTDRAWCREATE )GetProcAddress( hInstDDraw, "DirectDrawCreate" );
        if( pDDCreate )
        {
            pDDCreate( NULL, &pDDraw, NULL );

            if( SUCCEEDED( pDDraw->QueryInterface( IID_IDirectDraw7, ( VOID** )&pDDraw7 ) ) )
            {
                DDSCAPS2 ddscaps;
                ZeroMemory( &ddscaps, sizeof( DDSCAPS2 ) );
                ddscaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM;
            }

			
			// set cooperation to full screen
			hr = pDDraw7->SetCooperativeLevel(main_window_handle, 
												  DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX | 
												  DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT);
			if (hr!=S_OK)
			   return(0);

			// set display mode 
			hr = pDDraw7->SetDisplayMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,0,0);
			if (hr != S_OK)
			   return(0);

			//// clear ddsd and set size
			DDRAW_INIT_STRUCT(ddsd); 
			ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
			ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
			ddsd.dwBackBufferCount = 1;

			// create the primary surface
			hr = pDDraw7->CreateSurface(&ddsd, &lpddsprimary, NULL);
			if (hr!=S_OK)
			   return(0);

			// Get the pointer to the back buffer
			ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
			HRESULT ddrval = lpddsprimary->GetAttachedSurface(&ddscaps, &lpddsback);
			if( ddrval != DD_OK )
			{
				//lpddsprimary->Release();
				return(false);
			}

			// get the pixel format of the primary surface
			DDPIXELFORMAT ddpf; // used to get pixel format

			// initialize structure
			DDRAW_INIT_STRUCT(ddpf);

			// query the format from primary surface
			lpddsprimary->GetPixelFormat(&ddpf);
			
			input = new InputClass(hInst, main_window_handle);
		
			

			// load the 24-bit image
		/*	if (!Load_Bitmap_File(&bitmap,"C://Users//Jason//Pictures//ff.bmp"))
			   return(0);*/

			// copy the bitmap image to the primary buffer line by line
			// notice the 24 to 32 bit conversion pixel by pixel

			// lock the primary surface
			//lpddsprimary->Lock(NULL,&ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT,NULL);

			//// get video pointer to primary surfce
			//DWORD *primary_buffer = (DWORD *)ddsd.lpSurface;      
			//int size = sizeof(primary_buffer);
			//unsigned int pixel;
	
			/*	int padding = 0;
					int scanlinebytes = WINDOW_WIDTH * 3;
	while ( ( scanlinebytes + padding ) % 4 != 0 )
		padding++;
	int psw = scanlinebytes + padding;*/
			// process each line and copy it into the primary buffer
			//for (int index_y = 0; index_y < WINDOW_HEIGHT; index_y++)
			//	{
			//	for (int index_x = 0; index_x < WINDOW_WIDTH; index_x++)
			//		{
			//		// get BGR values
			//		/*UCHAR blue  = (bitmap.buffer[index_y*WINDOW_WIDTH*3 + index_x*3 + 0]),
			//			  green = (bitmap.buffer[index_y*WINDOW_WIDTH*3 + index_x*3 + 1]),
			//			  red   = (bitmap.buffer[index_y*WINDOW_WIDTH*3 + index_x*3 + 2]);*/

			//		// this builds a 32 bit color value in A.8.8.8 format (8-bit alpha mode)
			//		pixel = bitmap.buffer[index_y*WINDOW_WIDTH + index_x + 0];//_RGB32BIT(0,red,green,blue);

			//	//primary_buffer[index_x + (index_y*psw)] = pixel;

			//		// write the pixel
			//		primary_buffer[index_x + (index_y*ddsd.lPitch >> 2)] = pixel;

			//		} // end for index_x

			//	} // end for index_y
        }
     /*  Flip_Bitmap(bitmap.buffer, 
            bitmap.bitmapinfoheader.biWidth*(bitmap.bitmapinfoheader.biBitCount/8), 
            bitmap.bitmapinfoheader.biHeight);*/
   
	//lpddsprimary->Unlock(NULL);
	//DDraw_Fill_Surface(lpddsback,0);
}
	       
	return (1);
}

void Game_Shutdown()
{
	lpddsback->Release();
	lpddsprimary->Release();
	pDDraw7->Release();
	FreeLibrary( hInstDDraw );
}

int Load_Bitmap_File(BITMAP_FILE_PTR bitmap, char *filename)
{
// this function opens a bitmap file and loads the data into bitmap

HANDLE file_handle,  // the file handle
    index;        // looping index

DWORD bytesread;

unsigned int *temp_buffer = NULL; // used to convert 32 bit images to 16 bit
OFSTRUCT file_data;          // the file data information

// open the file if it exists
wchar_t* wFileName = new wchar_t[4096];
MultiByteToWideChar(CP_ACP, 0, filename, -1, wFileName, 4096);
file_handle = CreateFile(wFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
if (file_handle == NULL)
{
//	reportLas
	return(0);
}
	//OpenFile(filename,&file_data,OF_READ))==-1)
  

// now load the bitmap file header
//_lread(file_handle, &bitmap->bitmapfileheader,sizeof(BITMAPFILEHEADER));
if ( ReadFile( file_handle, &bitmap->bitmapfileheader, sizeof(BITMAPFILEHEADER),&bytesread, NULL) == false)
{
	CloseHandle(file_handle);
	return(0);
}

// test if this is a bitmap file
if (bitmap->bitmapfileheader.bfType!= 'MB') //BITMAP_ID)
   {
   // close the file
   CloseHandle(file_handle);

   // return error
   return(0);
   } // end if

// now we know this is a bitmap, so read in all the sections

// first the bitmap infoheader

// now load the bitmap file header
ReadFile(file_handle, &bitmap->bitmapinfoheader,sizeof(BITMAPINFOHEADER),&bytesread,NULL);

// finally the image data itself
SetFilePointer(file_handle,bitmap->bitmapfileheader.bfOffBits,NULL,FILE_BEGIN);

// now read in the image, if the image is 8 or 16 bit then simply read it
// but if its 24 bit then read it into a temporary area and then convert
// it to a 16 bit image

if ( bitmap->bitmapinfoheader.biBitCount==32)
   {
   // delete the last image if there was one
   if (bitmap->buffer)
       free(bitmap->buffer);

   // allocate the memory for the image
   if (!(bitmap->buffer = (unsigned int *)malloc(bitmap->bitmapinfoheader.biSizeImage)))
      {
      // close the file
      CloseHandle(file_handle);

      // return error
      return(0);
      } // end if

   // now read it in
   ReadFile(file_handle,bitmap->buffer,bitmap->bitmapinfoheader.biSizeImage, &bytesread, NULL);

   } // end if
else
   {
   // serious problem
   return(0);

   } // end else

#if 0
// write the file info out 
printf("\nfilename:%s \nsize=%d \nwidth=%d \nheight=%d \nbitsperpixel=%d \ncolors=%d \nimpcolors=%d",
        filename,
        bitmap->bitmapinfoheader.biSizeImage,
        bitmap->bitmapinfoheader.biWidth,
        bitmap->bitmapinfoheader.biHeight,
		bitmap->bitmapinfoheader.biBitCount,
        bitmap->bitmapinfoheader.biClrUsed,
        bitmap->bitmapinfoheader.biClrImportant);
#endif

// close the file
CloseHandle(file_handle);

// flip the bitmap
//Flip_Bitmap(bitmap->buffer, 
//            bitmap->bitmapinfoheader.biWidth*(bitmap->bitmapinfoheader.biBitCount/8), 
//            bitmap->bitmapinfoheader.biHeight);

// return success
return(1);

} // end Load_Bitmap_File

int Flip_Bitmap(unsigned int *image, int bytes_per_line, int height)
{
// this function is used to flip bottom-up .BMP images

unsigned int *buffer; // used to perform the image processing
int index;     // looping index

// allocate the temporary buffer
if (!(buffer = (unsigned int *)malloc(bytes_per_line*height)))
   return(0);

// copy image to work area
memcpy(buffer,image,bytes_per_line*height);

// flip vertically
for (index=0; index < height; index++)
    memcpy(&image[((height-1) - index)*800],
           &buffer[index*800], bytes_per_line);

// release the memory
free(buffer);

// return success
return(1);

} // end Flip_Bitmap

int Draw_Pixel16(int x, int y,int color,
                        UCHAR *video_buffer, int lpitch)
{
// this function plots a single pixel at x,y with color

((USHORT *)video_buffer)[x + y*(lpitch >> 1)] = color;

// return success
return(1);

} // end Draw_Pixel16

int Draw_Line16(int x0, int y0, // starting position 
                int x1, int y1, // ending position
                int color,     // color index
                UCHAR *vb_start, int lpitch) // video buffer and memory pitch
{
// this function draws a line from xo,yo to x1,y1 using differential error
// terms (based on Bresenahams work)

int dx,             // difference in x's
    dy,             // difference in y's
    dx2,            // dx,dy * 2
    dy2, 
    x_inc,          // amount in pixel space to move during drawing
    y_inc,          // amount in pixel space to move during drawing
    error,          // the discriminant i.e. error i.e. decision variable
    index;          // used for looping

int lpitch_2 = lpitch >> 1; // USHORT strided lpitch

// pre-compute first pixel address in video buffer based on 16bit data
USHORT *vb_start2 = (USHORT *)vb_start + x0 + y0*lpitch_2;

// compute horizontal and vertical deltas
dx = x1-x0;
dy = y1-y0;

// test which direction the line is going in i.e. slope angle
if (dx>=0)
   {
   x_inc = 1;

   } // end if line is moving right
else
   {
   x_inc = -1;
   dx    = -dx;  // need absolute value

   } // end else moving left

// test y component of slope

if (dy>=0)
   {
   y_inc = lpitch_2;
   } // end if line is moving down
else
   {
   y_inc = -lpitch_2;
   dy    = -dy;  // need absolute value

   } // end else moving up

// compute (dx,dy) * 2
dx2 = dx << 1;
dy2 = dy << 1;

// now based on which delta is greater we can draw the line
if (dx > dy)
   {
   // initialize error term
   error = dy2 - dx; 

   // draw the line
   for (index=0; index <= dx; index++)
       {
       // set the pixel
       *vb_start2 = (USHORT)color;

       // test if error has overflowed
       if (error >= 0) 
          {
          error-=dx2;

          // move to next line
          vb_start2+=y_inc;

	   } // end if error overflowed

       // adjust the error term
       error+=dy2;

       // move to the next pixel
       vb_start2+=x_inc;

       } // end for

   } // end if |slope| <= 1
else
   {
   // initialize error term
   error = dx2 - dy; 

   // draw the line
   for (index=0; index <= dy; index++)
       {
       // set the pixel
       *vb_start2 = (USHORT)color;

       // test if error overflowed
       if (error >= 0)
          {
          error-=dy2;

          // move to next line
          vb_start2+=x_inc;

          } // end if error overflowed

       // adjust the error term
       error+=dx2;

       // move to the next pixel
       vb_start2+=y_inc;

       } // end for

   } // end else |slope| > 1

// return success
return(1);

} // end Draw_Line16

int Draw_Clip_Line(int x0,int y0, int x1, int y1, int color, 
                    UCHAR *dest_buffer, int lpitch)
{
// this function draws a wireframe triangle

int cxs, cys,
	cxe, cye;

// clip and draw each line
cxs = x0;
cys = y0;
cxe = x1;
cye = y1;

// clip the line
if (Clip_Line(cxs,cys,cxe,cye))
	Draw_Line16(cxs, cys, cxe,cye,color,dest_buffer,lpitch);

// return success
return(1);

} // end Draw_Clip_Line

///////////////////////////////////////////////////////////

int Clip_Line(int &x1,int &y1,int &x2, int &y2)
{
// this function clips the sent line using the globally defined clipping
// region

// internal clipping codes
#define CLIP_CODE_C  0x0000
#define CLIP_CODE_N  0x0008
#define CLIP_CODE_S  0x0004
#define CLIP_CODE_E  0x0002
#define CLIP_CODE_W  0x0001

#define CLIP_CODE_NE 0x000a
#define CLIP_CODE_SE 0x0006
#define CLIP_CODE_NW 0x0009 
#define CLIP_CODE_SW 0x0005

int xc1=x1, 
    yc1=y1, 
	xc2=x2, 
	yc2=y2;

int p1_code=0, 
    p2_code=0;

// determine codes for p1 and p2
if (y1 < min_clip_y)
	p1_code|=CLIP_CODE_N;
else
if (y1 > max_clip_y)
	p1_code|=CLIP_CODE_S;

if (x1 < min_clip_x)
	p1_code|=CLIP_CODE_W;
else
if (x1 > max_clip_x)
	p1_code|=CLIP_CODE_E;

if (y2 < min_clip_y)
	p2_code|=CLIP_CODE_N;
else
if (y2 > max_clip_y)
	p2_code|=CLIP_CODE_S;

if (x2 < min_clip_x)
	p2_code|=CLIP_CODE_W;
else
if (x2 > max_clip_x)
	p2_code|=CLIP_CODE_E;

// try and trivially reject
if ((p1_code & p2_code)) 
	return(0);

// test for totally visible, if so leave points untouched
if (p1_code==0 && p2_code==0)
	return(1);

// determine end clip point for p1
switch(p1_code)
	  {
	  case CLIP_CODE_C: break;

	  case CLIP_CODE_N:
		   {
		   yc1 = min_clip_y;
		   xc1 = x1 + 0.5+(min_clip_y-y1)*(x2-x1)/(y2-y1);
		   } break;
	  case CLIP_CODE_S:
		   {
		   yc1 = max_clip_y;
		   xc1 = x1 + 0.5+(max_clip_y-y1)*(x2-x1)/(y2-y1);
		   } break;

	  case CLIP_CODE_W:
		   {
		   xc1 = min_clip_x;
		   yc1 = y1 + 0.5+(min_clip_x-x1)*(y2-y1)/(x2-x1);
		   } break;
		
	  case CLIP_CODE_E:
		   {
		   xc1 = max_clip_x;
		   yc1 = y1 + 0.5+(max_clip_x-x1)*(y2-y1)/(x2-x1);
		   } break;

	// these cases are more complex, must compute 2 intersections
	  case CLIP_CODE_NE:
		   {
		   // north hline intersection
		   yc1 = min_clip_y;
		   xc1 = x1 + 0.5+(min_clip_y-y1)*(x2-x1)/(y2-y1);

		   // test if intersection is valid, of so then done, else compute next
			if (xc1 < min_clip_x || xc1 > max_clip_x)
				{
				// east vline intersection
				xc1 = max_clip_x;
				yc1 = y1 + 0.5+(max_clip_x-x1)*(y2-y1)/(x2-x1);
				} // end if

		   } break;
	  
	  case CLIP_CODE_SE:
      	   {
		   // south hline intersection
		   yc1 = max_clip_y;
		   xc1 = x1 + 0.5+(max_clip_y-y1)*(x2-x1)/(y2-y1);	

		   // test if intersection is valid, of so then done, else compute next
		   if (xc1 < min_clip_x || xc1 > max_clip_x)
		      {
			  // east vline intersection
			  xc1 = max_clip_x;
			  yc1 = y1 + 0.5+(max_clip_x-x1)*(y2-y1)/(x2-x1);
			  } // end if

		   } break;
	    
	  case CLIP_CODE_NW: 
      	   {
		   // north hline intersection
		   yc1 = min_clip_y;
		   xc1 = x1 + 0.5+(min_clip_y-y1)*(x2-x1)/(y2-y1);
		   
		   // test if intersection is valid, of so then done, else compute next
		   if (xc1 < min_clip_x || xc1 > max_clip_x)
		      {
			  xc1 = min_clip_x;
		      yc1 = y1 + 0.5+(min_clip_x-x1)*(y2-y1)/(x2-x1);	
			  } // end if

		   } break;
	  	  
	  case CLIP_CODE_SW:
		   {
		   // south hline intersection
		   yc1 = max_clip_y;
		   xc1 = x1 + 0.5+(max_clip_y-y1)*(x2-x1)/(y2-y1);	
		   
		   // test if intersection is valid, of so then done, else compute next
		   if (xc1 < min_clip_x || xc1 > max_clip_x)
		      {
			  xc1 = min_clip_x;
		      yc1 = y1 + 0.5+(min_clip_x-x1)*(y2-y1)/(x2-x1);	
			  } // end if

		   } break;

	  default:break;

	  } // end switch

// determine clip point for p2
switch(p2_code)
	  {
	  case CLIP_CODE_C: break;

	  case CLIP_CODE_N:
		   {
		   yc2 = min_clip_y;
		   xc2 = x2 + (min_clip_y-y2)*(x1-x2)/(y1-y2);
		   } break;

	  case CLIP_CODE_S:
		   {
		   yc2 = max_clip_y;
		   xc2 = x2 + (max_clip_y-y2)*(x1-x2)/(y1-y2);
		   } break;

	  case CLIP_CODE_W:
		   {
		   xc2 = min_clip_x;
		   yc2 = y2 + (min_clip_x-x2)*(y1-y2)/(x1-x2);
		   } break;
		
	  case CLIP_CODE_E:
		   {
		   xc2 = max_clip_x;
		   yc2 = y2 + (max_clip_x-x2)*(y1-y2)/(x1-x2);
		   } break;

		// these cases are more complex, must compute 2 intersections
	  case CLIP_CODE_NE:
		   {
		   // north hline intersection
		   yc2 = min_clip_y;
		   xc2 = x2 + 0.5+(min_clip_y-y2)*(x1-x2)/(y1-y2);

		   // test if intersection is valid, of so then done, else compute next
			if (xc2 < min_clip_x || xc2 > max_clip_x)
				{
				// east vline intersection
				xc2 = max_clip_x;
				yc2 = y2 + 0.5+(max_clip_x-x2)*(y1-y2)/(x1-x2);
				} // end if

		   } break;
	  
	  case CLIP_CODE_SE:
      	   {
		   // south hline intersection
		   yc2 = max_clip_y;
		   xc2 = x2 + 0.5+(max_clip_y-y2)*(x1-x2)/(y1-y2);	

		   // test if intersection is valid, of so then done, else compute next
		   if (xc2 < min_clip_x || xc2 > max_clip_x)
		      {
			  // east vline intersection
			  xc2 = max_clip_x;
			  yc2 = y2 + 0.5+(max_clip_x-x2)*(y1-y2)/(x1-x2);
			  } // end if

		   } break;
	    
	  case CLIP_CODE_NW: 
      	   {
		   // north hline intersection
		   yc2 = min_clip_y;
		   xc2 = x2 + 0.5+(min_clip_y-y2)*(x1-x2)/(y1-y2);
		   
		   // test if intersection is valid, of so then done, else compute next
		   if (xc2 < min_clip_x || xc2 > max_clip_x)
		      {
			  xc2 = min_clip_x;
		      yc2 = y2 + 0.5+(min_clip_x-x2)*(y1-y2)/(x1-x2);	
			  } // end if

		   } break;
	  	  
	  case CLIP_CODE_SW:
		   {
		   // south hline intersection
		   yc2 = max_clip_y;
		   xc2 = x2 + 0.5+(max_clip_y-y2)*(x1-x2)/(y1-y2);	
		   
		   // test if intersection is valid, of so then done, else compute next
		   if (xc2 < min_clip_x || xc2 > max_clip_x)
		      {
			  xc2 = min_clip_x;
		      yc2 = y2 + 0.5+(min_clip_x-x2)*(y1-y2)/(x1-x2);	
			  } // end if

		   } break;
	
	  default:break;

	  } // end switch

// do bounds check
if ((xc1 < min_clip_x) || (xc1 > max_clip_x) ||
	(yc1 < min_clip_y) || (yc1 > max_clip_y) ||
	(xc2 < min_clip_x) || (xc2 > max_clip_x) ||
	(yc2 < min_clip_y) || (yc2 > max_clip_y) )
	{
	return(0);
	} // end if

// store vars back
x1 = xc1;
y1 = yc1;
x2 = xc2;
y2 = yc2;

return(1);

} // end Clip_Line