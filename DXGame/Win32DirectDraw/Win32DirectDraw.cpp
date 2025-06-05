// Win32DirectDraw.cpp : Defines the entry point for the application.
//
#include "ScriptTrans.h"
#include "stdafx.h"
#include <iostream>
#include "Win32DirectDraw.h"
#include <windows.h>
#include <DirectXMath.h>
#include <fstream>
using namespace std;



// this builds a 32 bit color value in A.8.8.8 format (8-bit alpha mode)
//#define _RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))
#define _RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))



// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);

INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);







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
	/*ofstream outfile;	
	outfile.open("allScripts.txt");*/
	game.Game_Init(hInstance, main_window_handle);
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{		
		
		


		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		/*Vector vec(0, 0.0f, 100.0f);
		double length = vec.Length();
		double theta = 3.14 / 2;*/
		game.SetMouseState(mousestate);
		game.Game_Main();
		
		// TODO: Add any drawing code here...
		/*SetTextColor(hdc, RGB(0,0,255));
		SetBkMode(hdc, OPAQUE);
		TextOut(hdc,10,10, L"test", GetTextSize(TextArray[0]));*/
	

		if (KEY_DOWN( VK_ESCAPE))
			break;
		
<<<<<<< HEAD
		//if (KEY_DOWN( VK_UP ))
		//	MoveCamera(1);
		//	//eye.z+=1;
		//else if (KEY_DOWN( VK_DOWN))
		//	MoveCamera(-1);
		//	//eye.z-=1;
		//	//SlideCamera(-1,0);	
		//

		//if (KEY_DOWN( VK_LEFT ))
		//{
		//	SlideCamera(-1,0);
		////	eye.x -= 1;
		////	at.x -= 1;
		//}
		//else if (KEY_DOWN( VK_RIGHT))
		//{
		//	SlideCamera(1,0);			
		//	//eye.x += 1;
		//	//at.x += 1;
		//}

		HRESULT hr = game.input->lpdimouse->GetDeviceState(sizeof(DIMOUSESTATE),(LPVOID)&mousestate);
=======

		#include "camera.scr"
		

		HRESULT hr = input->lpdimouse->GetDeviceState(sizeof(DIMOUSESTATE),(LPVOID)&mousestate);
>>>>>>> f2bb61289de15cc22f3cae01fb96254a5d78474d
		if (FAILED(hr))
		{
			/* error */
		}

		//D3DVECTOR v;
		//v = at - eye;
		
		//if (mousestate.lX > 0)
		//	game.yaw -= (3.14/180.0);
		//else if (mousestate.lX < 0)
		//	game.yaw += (3.14/180.0);

		/*if (mousestate.lY > 0)
			game.pitch -= (3.14/180.0);
		else if (mousestate.lY < 0)
			game.pitch += (3.14/180.0);*/

		/*while (game.yaw > (3.14*2))
			game.yaw-=(2*3.14);
		while (game.yaw < 0)
			game.yaw+=(2*3.14);

		while (game.pitch > (3.14*2))
			game.pitch-=(2*3.14);
		while (game.pitch < 0)
			game.pitch+=(2*3.14);*/

		
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
		//game.at.y = game.eye.y + radius * sin(game.pitch);
		//newHradius = radius *cos(game.pitch);
		//game.at.x = game.eye.x + newHradius * cos(game.yaw);
		//game.at.z = game.eye.z + newHradius * sin(game.yaw);

		//game.up.x = game.eye.x - game.at.x;
		//game.up.z = game.eye.z - game.at.z;
		//game.up.y = game.eye.y + radius * sin(game.pitch+ 3.14/2);
	}
	//outfile.close();
	game.Game_Shutdown();
	return (int) msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc = GetDC(hWnd);

	switch (message)
	{	
	case WM_COMMAND:
		wmId = LOWORD(wParam);
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

		SetTextColor(hdc, RGB(0, 0, 255));
		SetBkMode(hdc, OPAQUE);
		//TCHAR buf[80];

		wchar_t buf[100];
		//swprintf(buf, L"dot product: %f", dot);

		//TextOut(hdc, 10, 10, buf, wcslen(buf));

		/*swprintf(buf, L"Eye: %f %f %f", game.eye.x, game.eye.y, game.eye.z);
		TextOut(hdc, 10, 30, buf, wcslen(buf));

		swprintf(buf, L"yaw: %f ", game.yaw);
		TextOut(hdc, 10, 50, buf, wcslen(buf));

		swprintf(buf, L"obj_world 1: %f %f %f %f", XMVectorGetX(game.obj_vertices[0].r[0]), XMVectorGetY(game.obj_vertices[0].r[0]), XMVectorGetZ(game.obj_vertices[0].r[0]), XMVectorGetW(game.obj_vertices[0].r[0]));
		TextOut(hdc, 10, 80, buf, wcslen(buf));

<<<<<<< HEAD
		swprintf(buf, L"obj_world 2: %f %f %f %f", XMVectorGetX(game.obj_vertices[0].r[1]), XMVectorGetY(game.obj_vertices[0].r[1]), XMVectorGetZ(game.obj_vertices[0].r[1]), XMVectorGetW(game.obj_vertices[0].r[1]));
		TextOut(hdc, 10, 100, buf, wcslen(buf));
		
		swprintf(buf, L"obj_world 3: %f %f %f %f", XMVectorGetX(game.obj_vertices[0].r[2]), XMVectorGetY(game.obj_vertices[0].r[2]), XMVectorGetZ(game.obj_vertices[0].r[2]), XMVectorGetW(game.obj_vertices[0].r[2]));
		TextOut(hdc, 10, 120, buf, wcslen(buf));

		swprintf(buf, L"obj_world 4: %f %f %f %f", XMVectorGetX(game.obj_world[0].r[3]), XMVectorGetY(game.obj_world[0].r[3]), XMVectorGetZ(game.obj_world[0].r[3]), XMVectorGetW(game.obj_world[0].r[3]));
		TextOut(hdc, 10, 140, buf, wcslen(buf));

		swprintf(buf, L"yaw rotation 1: %f %f %f %f", XMVectorGetX(game.yawRot.r[0]), XMVectorGetY(game.yawRot.r[0]), XMVectorGetZ(game.yawRot.r[0]), XMVectorGetW(game.yawRot.r[0]));
		TextOut(hdc, 10, 80, buf, wcslen(buf));

		swprintf(buf, L"yaw rotation 2: %f %f %f %f", XMVectorGetX(game.yawRot.r[1]), XMVectorGetY(game.yawRot.r[1]), XMVectorGetZ(game.yawRot.r[1]), XMVectorGetW(game.yawRot.r[1]));
		TextOut(hdc, 10, 100, buf, wcslen(buf));

		swprintf(buf, L"yaw rotation 3: %f %f %f %f", XMVectorGetX(game.yawRot.r[2]), XMVectorGetY(game.yawRot.r[2]), XMVectorGetZ(game.yawRot.r[2]), XMVectorGetW(game.yawRot.r[2]));
		TextOut(hdc, 10, 120, buf, wcslen(buf));

		swprintf(buf, L"yaw rotation 4: %f %f %f %f", XMVectorGetX(game.yawRot.r[3]), XMVectorGetY(game.yawRot.r[3]), XMVectorGetZ(game.yawRot.r[3]), XMVectorGetW(game.yawRot.r[3]));
		TextOut(hdc, 10, 140, buf, wcslen(buf));

		swprintf(buf, L"proj 1: %f %f %f %f", XMVectorGetX(game.projCoordinates.r[0]), XMVectorGetY(game.projCoordinates.r[0]), XMVectorGetZ(game.projCoordinates.r[0]), XMVectorGetW(game.projCoordinates.r[0]));
		TextOut(hdc, 10, 180, buf, wcslen(buf));

		swprintf(buf, L"proj 2: %f %f %f %f", XMVectorGetX(game.projCoordinates.r[1]), XMVectorGetY(game.projCoordinates.r[1]), XMVectorGetZ(game.projCoordinates.r[1]), XMVectorGetW(game.projCoordinates.r[1]));
		TextOut(hdc, 10, 200, buf, wcslen(buf));

		swprintf(buf, L"proj 3: %f %f %f %f", XMVectorGetX(game.projCoordinates.r[2]), XMVectorGetY(game.projCoordinates.r[2]), XMVectorGetZ(game.projCoordinates.r[2]), XMVectorGetW(game.projCoordinates.r[2]));
		TextOut(hdc, 10, 220, buf, wcslen(buf));

		swprintf(buf, L"proj 4: %f %f %f %f", XMVectorGetX(game.projCoordinates.r[3]), XMVectorGetY(game.projCoordinates.r[3]), XMVectorGetZ(game.projCoordinates.r[3]), XMVectorGetW(game.projCoordinates.r[3]));
		TextOut(hdc, 10, 240, buf, wcslen(buf));

		swprintf(buf, L"Tcam_inv 1: %f %f %f %f", XMVectorGetX(game.Tcam_inv.r[0]), XMVectorGetY(game.Tcam_inv.r[0]), XMVectorGetZ(game.Tcam_inv.r[0]), XMVectorGetW(game.Tcam_inv.r[0]));
		TextOut(hdc, 10, 280, buf, wcslen(buf));

		swprintf(buf, L"Tcam_inv 2: %f %f %f %f", XMVectorGetX(game.Tcam_inv.r[1]), XMVectorGetY(game.Tcam_inv.r[1]), XMVectorGetZ(game.Tcam_inv.r[1]), XMVectorGetW(game.Tcam_inv.r[1]));
		TextOut(hdc, 10, 300, buf, wcslen(buf));

		swprintf(buf, L"Tcam_inv 3: %f %f %f %f", XMVectorGetX(game.Tcam_inv.r[2]), XMVectorGetY(game.Tcam_inv.r[2]), XMVectorGetZ(game.Tcam_inv.r[2]), XMVectorGetW(game.Tcam_inv.r[2]));
		TextOut(hdc, 10, 320, buf, wcslen(buf));

		swprintf(buf, L"Tcam_inv 4: %f %f %f %f", XMVectorGetX(game.Tcam_inv.r[3]), XMVectorGetY(game.Tcam_inv.r[3]), XMVectorGetZ(game.Tcam_inv.r[3]), XMVectorGetW(game.Tcam_inv.r[3]));
		TextOut(hdc, 10, 340, buf, wcslen(buf));*/
		/*if (game.obj.size() > 0)
=======
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
>>>>>>> f2bb61289de15cc22f3cae01fb96254a5d78474d
		{
			swprintf(buf, L"obj 1: %f %f %f %f", XMVectorGetX(game.obj[0].r[0]), XMVectorGetY(game.obj[0].r[0]), XMVectorGetZ(game.obj[0].r[0]), XMVectorGetW(game.obj[0].r[0]));
			TextOut(hdc, 10, 280, buf, wcslen(buf));

			swprintf(buf, L"obj 2: %f %f %f %f", XMVectorGetX(game.obj[0].r[1]), XMVectorGetY(game.obj[0].r[1]), XMVectorGetZ(game.obj[0].r[1]), XMVectorGetW(game.obj[0].r[1]));
			TextOut(hdc, 10, 300, buf, wcslen(buf));

			swprintf(buf, L"obj 3: %f %f %f %f", XMVectorGetX(game.obj[0].r[2]), XMVectorGetY(game.obj[0].r[2]), XMVectorGetZ(game.obj[0].r[2]), XMVectorGetW(game.obj[0].r[2]));
			TextOut(hdc, 10, 320, buf, wcslen(buf));

			swprintf(buf, L"obj 4: %f %f %f %f", XMVectorGetX(game.obj[0].r[3]), XMVectorGetY(game.obj[0].r[3]), XMVectorGetZ(game.obj[0].r[3]), XMVectorGetW(game.obj[0].r[3]));
			TextOut(hdc, 10, 340, buf, wcslen(buf));
		}
		swprintf(buf, L"Eye: %f", level.objectList[0].plist[0].vert[0]);
		TextOut(hdc,10,50, buf, wcslen(buf));*/

<<<<<<< HEAD
		//EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
=======
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
>>>>>>> f2bb61289de15cc22f3cae01fb96254a5d78474d
	}
	return 0;
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

	wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;// LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32DIRECTDRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);// (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCE(IDC_WIN32DIRECTDRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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



LPSTR TextArray [] = {
    "Test"
};



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







///////////////////////////////////////////////////////////

