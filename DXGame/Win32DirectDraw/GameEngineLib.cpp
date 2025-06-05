// T3DLIB5.CPP

#define STANDALONE 0

// INCLUDES ///////////////////////////////////////////////////

#define DEBUG_ON

#define WIN32_LEAN_AND_MEAN  

#if (STANDALONE==1)
#define INITGUID       // you need this or DXGUID.LIB
#endif
#include <iostream> // include important C/C++ stuff
#include <fstream>
#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <mmsystem.h>
#include <objbase.h>

#include <conio.h>
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
//#include "T3DLIB1.H"    // T3DLIB4 is based on some defs in this 
//#include "T3DLIB4.H"
//#include "T3DLIB5.H"
//#include "T3DLIB6.h"
#include "stdafx.h"
#include "GAMEENGINELIB.H"

using namespace std;


// these defined the general clipping rectangle
int min_clip_x = 0,                             // clipping rectangle 
max_clip_x = (SCREEN_WIDTH - 1),
min_clip_y = 0,
max_clip_y = (SCREEN_HEIGHT - 1);

int LoadLevel_LVL(VECTOR4D_PTR scale,OBJECTLIST4DV1_PTR obj_list,RGBAV1_PTR ambient_color)
{
	
	//FILE *stream;		// file pointer

	char buffer[256];  // working buffer
	char tmp_string[8];
	int poly_surface_desc = 0; // PLG/PLX surface descriptor
	OBJECT4DV1_PTR obj; 	
	int numOfObjects;
	char *filename,*line;	
	char *szObjType;
	float width,height,length;
	int r,g,b,a;

	line = (char*)malloc(100);
	szObjType = (char*)malloc(100);
	obj = (OBJECT4DV1_PTR)malloc(sizeof(OBJECT4DV1));
	memset(obj, 0, sizeof(OBJECT4DV1));
	// Step 2: open the file for reading
	
	//fstream("compiled.lvl", ios::in | ios::out | ios::trunc);
	//ifstream fs;
	//("compiled.lvl", ios::in | ios::out | ios::trunc);
	//if (!(stream = fopen("compiled.lvl", "r")))
 //   {
 //   Write_Error("Couldn't open file %s.", filename);
 //   return(0);
 //   } // end if

	
	//// read the RGB color
	//fgets(line,100,stream);
	//sscanf(line,"%d %d %d %d",&r,&g,&b,&a);
	//ambient_color->rgba = _RGBA32BIT(r,g,b,a);

	//fgets(line,100,stream);
	//sscanf(line,"%d",&numOfObjects);
	//obj_list->num_objs = numOfObjects;
	//for (int i = 0; i < numOfObjects; i++)
	//{
	//	fgets(line,100,stream);
	//	sscanf(line,"%s",szObjType);
	//	if (strncmp(szObjType,"cube",4)==0)
	//	{
	//		obj = (OBJECT4DV1*)malloc( sizeof(OBJECT4DV1));				
	//		fgets(line,100,stream);
	//		sscanf(line,"%f %f %f",&obj->world_pos.x,&obj->world_pos.y,&obj->world_pos.z);
	//		fgets(line,100,stream);
	//		sscanf(line,"%f %f %f",&width,&length,&height);
	//		fgets(line,100,stream);
	//		sscanf(line,"%f %f %f",&obj->dir.x,&obj->dir.y,&obj->dir.z);
	//		obj->vlist_local[0].x=-width/2;
	//		obj->vlist_local[0].y=height/2;
	//		obj->vlist_local[0].z=-length/2;
	//		obj->vlist_local[1].x=width/2;
	//		obj->vlist_local[1].y=height/2;
	//		obj->vlist_local[1].z=-length/2;
	//		obj->vlist_local[2].x=width/2;
	//		obj->vlist_local[2].y=-height/2;
	//		obj->vlist_local[2].z=-length/2;
	//		obj->vlist_local[3].x=-width/2;
	//		obj->vlist_local[3].y=-height/2;
	//		obj->vlist_local[3].z=-length/2;
	//		obj->vlist_local[4].x=-width/2;
	//		obj->vlist_local[4].y=height/2;
	//		obj->vlist_local[4].z=length/2;
	//		obj->vlist_local[5].x=width/2;
	//		obj->vlist_local[5].y=height/2;
	//		obj->vlist_local[5].z=length/2;
	//		obj->vlist_local[6].x=width/2;
	//		obj->vlist_local[6].y=-height/2;
	//		obj->vlist_local[6].z=length/2;
	//		obj->vlist_local[7].x=-width/2;
	//		obj->vlist_local[7].y=-height/2;
	//		obj->vlist_local[7].z=length/2;
	//	}
	//	else if (strncmp(line,"object",6)==0)
	//	{
	//		obj = (OBJECT4DV1*)malloc( sizeof(OBJECT4DV1));
	//		memset(obj, 0, sizeof(OBJECT4DV1));
	//		// set state of object to active and visible		
	//		obj->state = OBJECT4DV1_STATE_ACTIVE | OBJECT4DV1_STATE_VISIBLE;
	//		strcpy(obj->name, "object");
	//		fgets( line, 100, stream );	  		
	//		sscanf(line,"%f %f %f",&obj->world_pos.x,&obj->world_pos.y,&obj->world_pos.z);						
	//		fgets( line, 100, stream );	  // read direction					
	//		sscanf(line,"%f %f %f",&obj->dir.x,&obj->dir.y,&obj->dir.z);
	//		fgets( line, 100, stream );	  // read scale					
	//		sscanf(line,"%f %f %f",&scale->x,&scale->y,&scale->z);
	//		fgets( line, 100, stream );  // read # of vertices	 
	//		sscanf(line,"%d",&obj->num_vertices);			
	//		for (int vertex=0; vertex<obj->num_vertices; vertex++)
	//		{
	//			obj->vlist_local[obj->num_vertices];
	//			fgets( line, 100, stream );
	//			sscanf(line,"%f %f %f", &obj->vlist_local[vertex].x, 
 //                                    &obj->vlist_local[vertex].y, 
 //                                    &obj->vlist_local[vertex].z);
	//			obj->vlist_local[vertex].w = 1;    
	//			// scale vertices
	//			obj->vlist_local[vertex].x*=scale->x;
	//			obj->vlist_local[vertex].y*=scale->y;
	//			obj->vlist_local[vertex].z*=scale->z;
	//		}
	//		fgets( line, 100, stream );  // read # of polys	  
	//		sscanf(line,"%d",&obj->num_polys);
	//		for (int w=0; w<obj->num_polys; w++)
	//		{						
	//			fgets( line, 100, stream );
	//			sscanf(line, "%s %d %d %d", tmp_string,&obj->plist[w].vert[0],
	//									&obj->plist[w].vert[1],
	//									&obj->plist[w].vert[2]);
	//			 // point polygon vertex list to object's vertex list
	//			// note that this is redundant since the polylist is contained
	//			// within the object in this case and its up to the user to select
	//			// whether the local or transformed vertex list is used when building up
	//			// polygon geometry, might be a better idea to set to NULL in the context
	//			// of polygons that are part of an object
	//			sscanf(tmp_string,"%x",&poly_surface_desc);
	//			
	//			SET_BIT(obj->plist[w].attr,POLY4DV1_ATTR_RGB16 | POLY4DV1_ATTR_SHADE_MODE_FLAT);
	//			int red = ((poly_surface_desc & 0x0f00)>> 8);
	//			int green = ((poly_surface_desc & 0x00f0) >> 4);
	//			int blue = (poly_surface_desc & 0x000f);

	//			obj->plist[w].color = RGB16Bit(red*16,green*16,blue*16);

	//			obj->plist[w].vlist = obj->vlist_local; 
	//			 // finally set the polygon to active
	//			obj->plist[w].state = POLY4DV1_STATE_ACTIVE; 
	//			
	//		}
	//	}		
	//	
	//	obj_list->obj_ptrs[i] = obj;		
	//}
	//// close the file
	//fclose(stream);

	// success
	return 1;
}

int Clip_Line(int& x1, int& y1, int& x2, int& y2)
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

	int xc1 = x1,
		yc1 = y1,
		xc2 = x2,
		yc2 = y2;

	int p1_code = 0,
		p2_code = 0;

	// determine codes for p1 and p2
	if (y1 < min_clip_y)
		p1_code |= CLIP_CODE_N;
	else
		if (y1 > max_clip_y)
			p1_code |= CLIP_CODE_S;

	if (x1 < min_clip_x)
		p1_code |= CLIP_CODE_W;
	else
		if (x1 > max_clip_x)
			p1_code |= CLIP_CODE_E;

	if (y2 < min_clip_y)
		p2_code |= CLIP_CODE_N;
	else
		if (y2 > max_clip_y)
			p2_code |= CLIP_CODE_S;

	if (x2 < min_clip_x)
		p2_code |= CLIP_CODE_W;
	else
		if (x2 > max_clip_x)
			p2_code |= CLIP_CODE_E;

	// try and trivially reject
	if ((p1_code & p2_code))
		return(0);

	// test for totally visible, if so leave points untouched
	if (p1_code == 0 && p2_code == 0)
		return(1);

	// determine end clip point for p1
	switch (p1_code)
	{
	case CLIP_CODE_C: break;

	case CLIP_CODE_N:
	{
		yc1 = min_clip_y;
		xc1 = x1 + 0.5 + (min_clip_y - y1) * (x2 - x1) / (y2 - y1);
	} break;
	case CLIP_CODE_S:
	{
		yc1 = max_clip_y;
		xc1 = x1 + 0.5 + (max_clip_y - y1) * (x2 - x1) / (y2 - y1);
	} break;

	case CLIP_CODE_W:
	{
		xc1 = min_clip_x;
		yc1 = y1 + 0.5 + (min_clip_x - x1) * (y2 - y1) / (x2 - x1);
	} break;

	case CLIP_CODE_E:
	{
		xc1 = max_clip_x;
		yc1 = y1 + 0.5 + (max_clip_x - x1) * (y2 - y1) / (x2 - x1);
	} break;

	// these cases are more complex, must compute 2 intersections
	case CLIP_CODE_NE:
	{
		// north hline intersection
		yc1 = min_clip_y;
		xc1 = x1 + 0.5 + (min_clip_y - y1) * (x2 - x1) / (y2 - y1);

		// test if intersection is valid, of so then done, else compute next
		if (xc1 < min_clip_x || xc1 > max_clip_x)
		{
			// east vline intersection
			xc1 = max_clip_x;
			yc1 = y1 + 0.5 + (max_clip_x - x1) * (y2 - y1) / (x2 - x1);
		} // end if

	} break;

	case CLIP_CODE_SE:
	{
		// south hline intersection
		yc1 = max_clip_y;
		xc1 = x1 + 0.5 + (max_clip_y - y1) * (x2 - x1) / (y2 - y1);

		// test if intersection is valid, of so then done, else compute next
		if (xc1 < min_clip_x || xc1 > max_clip_x)
		{
			// east vline intersection
			xc1 = max_clip_x;
			yc1 = y1 + 0.5 + (max_clip_x - x1) * (y2 - y1) / (x2 - x1);
		} // end if

	} break;

	case CLIP_CODE_NW:
	{
		// north hline intersection
		yc1 = min_clip_y;
		xc1 = x1 + 0.5 + (min_clip_y - y1) * (x2 - x1) / (y2 - y1);

		// test if intersection is valid, of so then done, else compute next
		if (xc1 < min_clip_x || xc1 > max_clip_x)
		{
			xc1 = min_clip_x;
			yc1 = y1 + 0.5 + (min_clip_x - x1) * (y2 - y1) / (x2 - x1);
		} // end if

	} break;

	case CLIP_CODE_SW:
	{
		// south hline intersection
		yc1 = max_clip_y;
		xc1 = x1 + 0.5 + (max_clip_y - y1) * (x2 - x1) / (y2 - y1);

		// test if intersection is valid, of so then done, else compute next
		if (xc1 < min_clip_x || xc1 > max_clip_x)
		{
			xc1 = min_clip_x;
			yc1 = y1 + 0.5 + (min_clip_x - x1) * (y2 - y1) / (x2 - x1);
		} // end if

	} break;

	default:break;

	} // end switch

// determine clip point for p2
	switch (p2_code)
	{
	case CLIP_CODE_C: break;

	case CLIP_CODE_N:
	{
		yc2 = min_clip_y;
		xc2 = x2 + (min_clip_y - y2) * (x1 - x2) / (y1 - y2);
	} break;

	case CLIP_CODE_S:
	{
		yc2 = max_clip_y;
		xc2 = x2 + (max_clip_y - y2) * (x1 - x2) / (y1 - y2);
	} break;

	case CLIP_CODE_W:
	{
		xc2 = min_clip_x;
		yc2 = y2 + (min_clip_x - x2) * (y1 - y2) / (x1 - x2);
	} break;

	case CLIP_CODE_E:
	{
		xc2 = max_clip_x;
		yc2 = y2 + (max_clip_x - x2) * (y1 - y2) / (x1 - x2);
	} break;

	// these cases are more complex, must compute 2 intersections
	case CLIP_CODE_NE:
	{
		// north hline intersection
		yc2 = min_clip_y;
		xc2 = x2 + 0.5 + (min_clip_y - y2) * (x1 - x2) / (y1 - y2);

		// test if intersection is valid, of so then done, else compute next
		if (xc2 < min_clip_x || xc2 > max_clip_x)
		{
			// east vline intersection
			xc2 = max_clip_x;
			yc2 = y2 + 0.5 + (max_clip_x - x2) * (y1 - y2) / (x1 - x2);
		} // end if

	} break;

	case CLIP_CODE_SE:
	{
		// south hline intersection
		yc2 = max_clip_y;
		xc2 = x2 + 0.5 + (max_clip_y - y2) * (x1 - x2) / (y1 - y2);

		// test if intersection is valid, of so then done, else compute next
		if (xc2 < min_clip_x || xc2 > max_clip_x)
		{
			// east vline intersection
			xc2 = max_clip_x;
			yc2 = y2 + 0.5 + (max_clip_x - x2) * (y1 - y2) / (x1 - x2);
		} // end if

	} break;

	case CLIP_CODE_NW:
	{
		// north hline intersection
		yc2 = min_clip_y;
		xc2 = x2 + 0.5 + (min_clip_y - y2) * (x1 - x2) / (y1 - y2);

		// test if intersection is valid, of so then done, else compute next
		if (xc2 < min_clip_x || xc2 > max_clip_x)
		{
			xc2 = min_clip_x;
			yc2 = y2 + 0.5 + (min_clip_x - x2) * (y1 - y2) / (x1 - x2);
		} // end if

	} break;

	case CLIP_CODE_SW:
	{
		// south hline intersection
		yc2 = max_clip_y;
		xc2 = x2 + 0.5 + (max_clip_y - y2) * (x1 - x2) / (y1 - y2);

		// test if intersection is valid, of so then done, else compute next
		if (xc2 < min_clip_x || xc2 > max_clip_x)
		{
			xc2 = min_clip_x;
			yc2 = y2 + 0.5 + (min_clip_x - x2) * (y1 - y2) / (x1 - x2);
		} // end if

	} break;

	default:break;

	} // end switch

// do bounds check
	if ((xc1 < min_clip_x) || (xc1 > max_clip_x) ||
		(yc1 < min_clip_y) || (yc1 > max_clip_y) ||
		(xc2 < min_clip_x) || (xc2 > max_clip_x) ||
		(yc2 < min_clip_y) || (yc2 > max_clip_y))
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

unsigned short ConvertRGB888toRGB565(unsigned int nSourceColor)
{
	unsigned short RGB565;
	// bring r,g, and b to the last 16 bits
	unsigned short r = ((nSourceColor >> 16) & 0x000000FF);
	unsigned short g = ((nSourceColor >> 8) & 0x000000FF);
	unsigned short b = (nSourceColor & 0x000000FF);

	// if you have three 8 bit numbers, and you want 5 6 5
	//(8 - 3) - 5 bits
	//(8 - 2) - 6 bits
	//(8 - 3) - 5 bit
	//  unsigned short  B =  (b  >> 3)        & 0x001F;
 //   unsigned short  G = ((g >> 2) <<  5) & 0x07E0; // not <
 //   unsigned short  R = ((r   >> 3) << 11) & 0xF800; // not <

	//RGB565 = (R | G | B);
	// shift them to fit in 565 format 
	RGB565 = ((r << 8) & 0xF800) | ((g << 3) & 0x07E0) | ((b >> 3) & 0x001F);
	return RGB565;
}

int Draw_Pixel16(int x, int y, int color,
	UCHAR* video_buffer, int lpitch)
{
	// this function plots a single pixel at x,y with color

	((USHORT*)video_buffer)[x + y * (lpitch >> 1)] = color;

	// return success
	return(1);

} // end Draw_Pixel16

int Draw_Line16(int x0, int y0, // starting position 
	int x1, int y1, // ending position
	int color,     // color index
	UCHAR* vb_start, int lpitch) // video buffer and memory pitch
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
	USHORT* vb_start2 = (USHORT*)vb_start + x0 + y0 * lpitch_2;

	// compute horizontal and vertical deltas
	dx = x1 - x0;
	dy = y1 - y0;

	// test which direction the line is going in i.e. slope angle
	if (dx >= 0)
	{
		x_inc = 1;

	} // end if line is moving right
	else
	{
		x_inc = -1;
		dx = -dx;  // need absolute value

	} // end else moving left

 // test y component of slope

	if (dy >= 0)
	{
		y_inc = lpitch_2;
	} // end if line is moving down
	else
	{
		y_inc = -lpitch_2;
		dy = -dy;  // need absolute value

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
		for (index = 0; index <= dx; index++)
		{
			// set the pixel
			*vb_start2 = (USHORT)color;

			// test if error has overflowed
			if (error >= 0)
			{
				error -= dx2;

				// move to next line
				vb_start2 += y_inc;

			} // end if error overflowed

			// adjust the error term
			error += dy2;

			// move to the next pixel
			vb_start2 += x_inc;

		} // end for

	} // end if |slope| <= 1
	else
	{
		// initialize error term
		error = dx2 - dy;

		// draw the line
		for (index = 0; index <= dy; index++)
		{
			// set the pixel
			*vb_start2 = (USHORT)color;

			// test if error overflowed
			if (error >= 0)
			{
				error -= dy2;

				// move to next line
				vb_start2 += x_inc;

			} // end if error overflowed

		 // adjust the error term
			error += dx2;

			// move to the next pixel
			vb_start2 += y_inc;

		} // end for

	} // end else |slope| > 1

 // return success
	return(1);

} // end Draw_Line16

int Draw_Clip_Line(int x0, int y0, int x1, int y1, int color,
	UCHAR* dest_buffer, int lpitch)
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
	if (Clip_Line(cxs, cys, cxe, cye))
		Draw_Line16(cxs, cys, cxe, cye, color, dest_buffer, lpitch);

	// return success
	return(1);

} // end Draw_Clip_Line

unsigned int ExtractGreen(unsigned int nSourceColor)
{
	unsigned int RGBGreen;

	RGBGreen = nSourceColor & 0x0000FF00;
	return RGBGreen;
}

int Load_Bitmap_File(BITMAP_FILE_PTR bitmap, char* filename)
{
	// this function opens a bitmap file and loads the data into bitmap

	HANDLE file_handle,  // the file handle
		index;        // looping index

	DWORD bytesread;

	unsigned int* temp_buffer = NULL; // used to convert 32 bit images to 16 bit
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
	if (ReadFile(file_handle, &bitmap->bitmapfileheader, sizeof(BITMAPFILEHEADER), &bytesread, NULL) == false)
	{
		CloseHandle(file_handle);
		return(0);
	}

	// test if this is a bitmap file
	if (bitmap->bitmapfileheader.bfType != 'MB') //BITMAP_ID)
	{
		// close the file
		CloseHandle(file_handle);

		// return error
		return(0);
	} // end if

 // now we know this is a bitmap, so read in all the sections

 // first the bitmap infoheader

 // now load the bitmap file header
	ReadFile(file_handle, &bitmap->bitmapinfoheader, sizeof(BITMAPINFOHEADER), &bytesread, NULL);

	// finally the image data itself
	SetFilePointer(file_handle, bitmap->bitmapfileheader.bfOffBits, NULL, FILE_BEGIN);

	// now read in the image, if the image is 8 or 16 bit then simply read it
	// but if its 24 bit then read it into a temporary area and then convert
	// it to a 16 bit image

	if (bitmap->bitmapinfoheader.biBitCount == 32)
	{
		// delete the last image if there was one
		if (bitmap->buffer)
			free(bitmap->buffer);

		// allocate the memory for the image
		if (!(bitmap->buffer = (unsigned char*)malloc(bitmap->bitmapinfoheader.biSizeImage)))
		{
			// close the file
			CloseHandle(file_handle);

			// return error
			return(0);
		} // end if

	 // now read it in
		ReadFile(file_handle, bitmap->buffer, bitmap->bitmapinfoheader.biSizeImage, &bytesread, NULL);

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

int Flip_Bitmap(unsigned int* image, int bytes_per_line, int height)
{
	// this function is used to flip bottom-up .BMP images

	unsigned int* buffer; // used to perform the image processing
	int index;     // looping index

	// allocate the temporary buffer
	if (!(buffer = (unsigned int*)malloc(bytes_per_line * height)))
		return(0);

	// copy image to work area
	memcpy(buffer, image, bytes_per_line * height);

	// flip vertically
	for (index = 0; index < height; index++)
		memcpy(&image[((height - 1) - index) * 800],
			&buffer[index * 800], bytes_per_line);

	// release the memory
	free(buffer);

	// return success
	return(1);

} // end Flip_Bitmap
