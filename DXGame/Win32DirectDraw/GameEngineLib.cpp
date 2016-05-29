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