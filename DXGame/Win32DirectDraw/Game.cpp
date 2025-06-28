#include "stdafx.h"
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
	//if (XMVerifySupport())
		//XMMatrix matrix();
	LPDIRECTDRAW pDDraw = NULL;
	LPDIRECTDRAWENUMERATEEXA pDirectDrawEnumerateEx = NULL;
	HRESULT hr;

	LPDIRECTDRAWCREATE pDDCreate = NULL;
	level = Level("world.lvl");
	hInstDDraw = LoadLibrary(L"ddraw.dll");
	main_window_handle = windowHandle;

	eye = Vector(0.0f, 0.0f, -100.0f);
	at = Vector(0.0f, 0.0f, 100.0f, 0.0f);
	up = Vector(0.0f, 1.0f, 0.0f, 0.0f);
	eyeToVertex = Vector(0.0f, 0.0f, 0.0f);
	yaw = 0;// 3.14 / 2;
	pitch = 0;

	if (hInstDDraw)
	{

		pDDCreate = (LPDIRECTDRAWCREATE)GetProcAddress(hInstDDraw, "DirectDrawCreate");
		if (pDDCreate)
		{
			hr = DirectDrawCreate(NULL, &pDDraw, NULL);
			if (hr != DD_OK)
			{
				return 0;
			}
			//pDDCreate(NULL, &pDDraw, NULL);

			if (SUCCEEDED(pDDraw->QueryInterface(IID_IDirectDraw7, (VOID**)&pDDraw7)))
			{
				DDSCAPS2 ddscaps;
				ZeroMemory(&ddscaps, sizeof(DDSCAPS2));
				ddscaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM;
			}


			// set cooperation to full screen
			hr = pDDraw7->SetCooperativeLevel(main_window_handle,
				DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX |
				DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT);
			if (hr != S_OK)
				return(0);

			// set display mode 
			hr = pDDraw7->SetDisplayMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, 0, 0);
			if (hr != S_OK)
				return(0);

			//// clear ddsd and set size
			DDRAW_INIT_STRUCT(ddsd);
			ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
			ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
			ddsd.dwBackBufferCount = 1;

			// create the primary surface
			hr = pDDraw7->CreateSurface(&ddsd, &lpddsprimary, NULL);
			if (hr != S_OK)
				return(0);

			// Get the pointer to the back buffer
			ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
			HRESULT ddrval = lpddsprimary->GetAttachedSurface(&ddscaps, &lpddsback);
			if (ddrval != DD_OK)
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
			D3DXMATRIX m_MatWorld;
			for (vector< Object >::iterator objIterator = level.objectList.begin(); objIterator != level.objectList.end(); objIterator++)
			{
				C3DModel model(objIterator->world_pos, objIterator->dir, objIterator->scale);	
				if (objIterator->name == "camera")
				{
					eye = objIterator->world_pos;
					eye *= -1;
					RotateCamera(objIterator->dir.y, objIterator->dir.x);
					//at = objIterator->dir;
				}
				level.models.push_back(model);
			}

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

void Game::SetMouseState(DIMOUSESTATE mousestate)
{
	this->mousestate = mousestate;
}

void Game::SlideCamera(float h, float v)
{
	double ang = yaw;    // game.yaw = PI/2
	float x = h * moveDist * cos(ang);
	float y = 0;
	float z = h * moveDist * sin(ang);

	eye += Vector(x, y, z);

	//eye.x += h*moveDist*cos(ang); //(h is either a 1 or 0 to indicate)
	//eye.z += h*moveDist*sin(ang); //(movement in this plane or not)    
	//XMVectorSetY(eye.vect,eye.vect.z + (h * moveDist * sin(ang)));
}

void Game::MoveCamera(float d)
{
	float y;
	float x;
	float z;
	double ang = yaw + 3.14 / 2;
	x = d * moveDist * cos(ang);
	y = d * moveDist * sin(pitch);
	z = d * moveDist * sin(ang);
	/*float y = d * moveDist * sin(game.pitch);
	float x = d * moveDist * cos(game.pitch) * cos(game.yaw);
	float z = d * moveDist * cos(game.pitch) * sin(game.yaw);*/
	//game.eye.y += d*moveDist*sin(pitch);
	//game.eye.x += d*moveDist*cos(pitch)*cos(yaw);
	//game.eye.z += d*moveDist*cos(pitch)*sin(yaw);
	eye += Vector(x, y, z);
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
	#include "allScripts.txt" ;

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
	RECT client;
	/*client->top = 0;
	client->left = 0;
	client->right = WINDOW_WIDTH;
	client->bottom = WINDOW_HEIGHT;*/
	SetRect(&client, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	DDraw_Fill_Surface(lpddsback, RGB16Bit565(255, 255, 255), &client);
	//// lock the primary surface
	DDRAW_INIT_STRUCT(ddsd);
	if (FAILED(lpddsback->Lock(NULL, &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL))) {
	//	return 0;
	}

	//// get video pointer to primary surfce
	UCHAR* back_buffer = (UCHAR*)ddsd.lpSurface;

	//D3DXMATRIX out;
	
	

	//Level level("world.lvl");
	/*view = XMMatrixSet(eye.x, eye.y, eye.z, 0,
		at.x, at.y, at.z, 0,
		up.x, up.y, up.z, 0,
		0, 0, 0, 1);*/
	view = XMMatrixSet(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,		
		-eye.x, -eye.y, -eye.z, 1 );
		//XMMatrixLookAtLH(eye.vect, at.vect, up.vect); //D3DXMatrixLookAtLH(&out, &eye, &at, &up);
	D3DXMATRIX m_MatWorld;
	//for (int i=0; i < level.objectList.size(); i++)
	int m = 0;
	vector<Point> pts;
	vector<Point> vertices;
	D3DXMATRIX Mtemp1, Mtemp2;
	//Mtemp1 = XMMatrixMultiply(pitchRot, XMMatrixRotationZ(yaw);
	yawRot = XMMatrixMultiply(view,XMMatrixRotationY(yaw));
	pitchRot = XMMatrixRotationX(pitch);
	Tcam_inv = XMMatrixMultiply(yawRot, pitchRot);
	for (vector< Object >::iterator objIterator = level.objectList.begin(); objIterator != level.objectList.end(); objIterator++, m++)
	{		
		obj.clear();
		obj_vertices.clear();
		//C3DModel model(&m_MatWorld, objIterator->world_pos, objIterator->dir);
		C3DModel model = level.models.at(m);
		m_MatWorld = model.MakeWorldMatrix();
		D3DXMATRIX projectionMatrix = model.ProjectionMatrix(100.00f, 10000.0f, 0.785f, 0.785f);
		D3DXMATRIX cameraCoordinates, screenCoordinates;

		
		//level.models.push_back(model);
		cameraCoordinates = m_MatWorld;// XMMatrixMultiply(m_MatWorld, Tcam_inv);

		//float camz = XMVectorGetZ(cameraCoordinates.r[2]);
		//cout << "camera: " << camz;
		//D3DXMatrixMultiply(&cameraCoordinates,&m_MatWorld,view);
		//D3DXMatrixMultiply(&projCoordinates,&cameraCoordinates, &projectionMatrix);
		projCoordinates = cameraCoordinates;// XMMatrixMultiply(cameraCoordinates, projectionMatrix);

		for (int i = 0; i < objIterator->num_vertices; i++)
		{

			D3DXMATRIX matrixWorld;

			float x = objIterator->vlist_local[i].getX(); 
			float y = objIterator->vlist_local[i].getY(); 
			float z = objIterator->vlist_local[i].getZ();
			float sx = 1;// objIterator->scale.x;
			float sy = 1;// objIterator->scale.y;
			float sz = 1;// objIterator->scale.z;
			//matrixWorld.r[0] = XMVectorSet(x, y, z, 0);
			//matrixWorld.r[0][0] = x;
			//matrixWorld.r[0][1] = y;
			//matrixWorld.r[0][2] = z;
			matrixWorld = XMMatrixSet(x*sx, y*sy, z*sz, 1,
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0);
			/*matrixWorld.m[0][3] = 1;
			for (int j = 1; j < 4; j++)
			{
				matrixWorld.m[j][0] = 0;
				matrixWorld.m[j][1] = 0;
				matrixWorld.m[j][2] = 0;
				matrixWorld.m[j][3] = 0;
			}*/

			obj_vertices.push_back(matrixWorld);
			float curr_radius = x * x + y * y + z * z;
			if (curr_radius > objIterator->max_radius)
			{
				objIterator->setMaxRadius(curr_radius);
			}
		}

		for (int i = 0; i < obj_vertices.size(); i++)
		{

			D3DXMATRIX matrixObj, tempObj, objWorld;
			//D3DXMatrixMultiply(&matrixObj,&obj_world[i],&projCoordinates);
			tempObj = XMMatrixMultiply(obj_vertices[i],projCoordinates);
			
			float x = objIterator->world_pos.x + XMVectorGetX(tempObj.r[0]);
			float y = objIterator->world_pos.y + XMVectorGetY(tempObj.r[0]);
			float z = objIterator->world_pos.z + XMVectorGetZ(tempObj.r[0]);
			objWorld = XMMatrixSet(x, y, z, 1,
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0);
			
			//D3DXMATRIX translationMatrix = XMMatrixTranslationFromVector(eye.vect);
			
		//	matrixObj = XMMatrixMultiply(objWorld, translationMatrix  );
			matrixObj = XMMatrixMultiply(objWorld,Tcam_inv );
			
			
			obj.push_back(matrixObj);
		}

		float x = objIterator->world_pos.getX() * XMVectorGetX(cameraCoordinates.r[0]);
		float y = objIterator->world_pos.getY() * XMVectorGetY(cameraCoordinates.r[1]);
		float z = objIterator->world_pos.getZ();
		/*if (z > eye.z + 10000 || z < eye.z + 10)
			continue;*/
		z = objIterator->world_pos.getZ() * XMVectorGetZ(cameraCoordinates.r[2]) + objIterator->world_pos.getZ() * XMVectorGetW(cameraCoordinates.r[2]);
		/*if (fabs(x) > z || fabs(y) > z)
			continue;*/

		pts.clear();
		vertices.clear();
			
		//for (int i = 0; i < obj.size(); i++)
		for (int j = 0; j < obj.size(); j++)
		{
			Point obj_per, pt, vertex;
			obj_per.x = XMVectorGetX(obj[j].r[0]) / XMVectorGetZ(obj[j].r[0]);
			obj_per.y = XMVectorGetY(obj[j].r[0]) / XMVectorGetZ(obj[j].r[0]);

			vertex.x = XMVectorGetX(obj[j].r[0]);
			vertex.y = XMVectorGetY(obj[j].r[1]);
			vertex.z = XMVectorGetZ(obj[j].r[2]);
			vertices.push_back(vertex);

			pt.x = SCREEN_WIDTH / 2 + obj_per.x * (SCREEN_WIDTH / 2);
			pt.y = SCREEN_HEIGHT - (SCREEN_HEIGHT / 2 + obj_per.y * (SCREEN_HEIGHT / 2));
			if (pt.x > 0 && pt.x < SCREEN_WIDTH && pt.y > 0 && pt.y < SCREEN_HEIGHT && vertex.z > 0)
			{
				if (back_buffer != NULL)
					Draw_Pixel16(pt.x, pt.y, RGB16Bit565(255, 255, 255), back_buffer, ddsd.lPitch);
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
			for (int j = 0; j < 3; j++)
			{
				//need to take cross product of 2 edges of the triangle
				v[j] = Vector(vertices[objIterator->plist[poly].vert[j]].getX(), vertices[objIterator->plist[poly].vert[j]].getY(), vertices[objIterator->plist[poly].vert[j]].getZ());
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
			Vector lookat(at.x, at.y, at.z);
			Vector view = lookat - v[0];
			double dot = 0;
			dot = norm.dot(view);

			if (back_buffer != NULL)// && dot < 0)
			{	
				//if (objIterator->color != nullptr)
					Draw_Triangle_2D16(pts[objIterator->plist[poly].vert[0]].getX(), pts[objIterator->plist[poly].vert[0]].getY(),
						pts[objIterator->plist[poly].vert[1]].getX(), pts[objIterator->plist[poly].vert[1]].getY(),
						pts[objIterator->plist[poly].vert[2]].getX(), pts[objIterator->plist[poly].vert[2]].getY(),
						RGB16Bit565(objIterator->R, objIterator->G, objIterator->B), back_buffer, ddsd.lPitch);
				Draw_Clip_Line(pts[objIterator->plist[poly].vert[0]].getX(), pts[objIterator->plist[poly].vert[0]].getY(), pts[objIterator->plist[poly].vert[1]].getX(), pts[objIterator->plist[poly].vert[1]].getY(), RGB16Bit565(0, 0, 0), back_buffer, ddsd.lPitch);				
				Draw_Clip_Line(pts[objIterator->plist[poly].vert[1]].getX(), pts[objIterator->plist[poly].vert[1]].getY(), pts[objIterator->plist[poly].vert[2]].getX(), pts[objIterator->plist[poly].vert[2]].getY(), RGB16Bit565(0, 0, 0), back_buffer, ddsd.lPitch);
				Draw_Clip_Line(pts[objIterator->plist[poly].vert[2]].getX(), pts[objIterator->plist[poly].vert[2]].getY(), pts[objIterator->plist[poly].vert[0]].getX(), pts[objIterator->plist[poly].vert[0]].getY(), RGB16Bit565(0, 0, 0), back_buffer, ddsd.lPitch);
				
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

	RECT screen_rect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
	lpddsback->Unlock(&screen_rect);
	//lpddsprimary->SetSurfaceDesc(&ddsd,*back_buffer);

	lpddsprimary->Flip(NULL, DDFLIP_WAIT);



	return 0;
}

void Game::Game_Shutdown()
{
	lpddsback->Release();
	lpddsprimary->Release();
	pDDraw7->Release();
	FreeLibrary(hInstDDraw);
}

// Function I made to get the size of the text
int Game::GetTextSize(LPSTR a0)
{
	for (int iLoopCounter = 0; ; iLoopCounter++)
	{
		if (a0[iLoopCounter] == '\0')
			return iLoopCounter;
	}
}



