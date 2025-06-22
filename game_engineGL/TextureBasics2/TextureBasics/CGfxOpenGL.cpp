
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN 

#ifdef _WINDOWS
#include <windows.h>
#include <windowsx.h> 
#endif

#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

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
#include <dinput.h>
//#include "T3DLIB1.h" // game library includes
///*#include "T3DLIB2.h"
//#include "T3DLIB3.h"*/
//#include "T3DLIB4.h"
//#include "T3DLIB5.h"
#include "Object.h"
#include "Camera.h"
#include "glext.h"
#include "CGfxOpenGL.h"

#include "CTargaImage.h"

CGfxOpenGL::CGfxOpenGL()
{
}

CGfxOpenGL::~CGfxOpenGL()
{
}

bool CGfxOpenGL::Init(Camera *camera, FILE *fp_override)
{	
	fp_error = fp_override;
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// enable 2D texturing
	glEnable(GL_TEXTURE_2D);

	m_textureOne = new CTargaImage;
	
	// load texture image data
	if (!m_textureOne->Load("rock.tga"))
		return false;

	// retrieve "unused" texture object
	glGenTextures(1, &m_textureObjectOne);

	// bind the texture object
	glBindTexture(GL_TEXTURE_2D, m_textureObjectOne);

	// minimum required to set the min and mag texture filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// now that the texture object is bound, specify a texture for it
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textureOne->GetWidth(), m_textureOne->GetHeight(),
				 0, GL_RGB, GL_UNSIGNED_BYTE, m_textureOne->GetImage());

	// create the second texture object
	glGenTextures(1, &m_textureObjectTwo);

	glBindTexture(GL_TEXTURE_2D, m_textureObjectTwo);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textureOne->GetWidth(), m_textureOne->GetHeight(),
				0, GL_RGB, GL_UNSIGNED_BYTE, m_textureOne->GetImage());

	// initialize movement variables
	m_zMoveNegative = true;
	cam = camera;
	cam->pos.z = 0.0f;

	FILE* stream;
	char line[100];
	char* token, * stopstring;
	float scale = 1.0f, width, height, length;
	float x, y, z;
	Vertex vertex[8];
	int num, vertices;
	char seps[] = " ,\t\n";
	POINT4D pt;
	if (linked_list.empty())
	{
		int result = fopen_s(&stream, "world.lvl", "r+");
		if (result == 0)
		{
			fgets(line, 100, stream);
			int cnt = strtod(line, &stopstring);
			for (int i = 0; i < cnt; i++)
			{
				fgets(line, 100, stream);
				if (strncmp(line, "cube", 4) == 0)
				{
					obj = new Object();
					obj->type = "cube";
					fgets(line, 100, stream);
					obj->name = line;
					obj->name.pop_back(); // remove last character
					fgets(line, 100, stream);
					obj->scriptName = line;
					obj->scriptName.pop_back();
					fgets(line, 100, stream);
					token = strtok(line, seps);
					obj->world_pos.x = ((float)strtod(token, &stopstring)) * scale;
					token = strtok(NULL, " ");
					obj->world_pos.y = ((float)strtod(token, &stopstring)) * scale;
					token = strtok(NULL, " ");
					obj->world_pos.z = ((float)strtod(token, &stopstring)) * scale;
					fgets(line, 100, stream);
					token = strtok(line, " ");
					width = ((float)strtod(token, &stopstring)) * scale;
					token = strtok(NULL, " ");
					height = ((float)strtod(token, &stopstring)) * scale;
					token = strtok(NULL, " ");
					length = ((float)strtod(token, &stopstring)) * scale;
					fgets(line, 100, stream);
					token = strtok(line, " ");
					obj->dir.x = ((float)strtod(token, &stopstring)) * scale;
					token = strtok(NULL, " ");
					obj->dir.y = ((float)strtod(token, &stopstring)) * scale;
					token = strtok(NULL, " ");
					obj->dir.z = ((float)strtod(token, &stopstring)) * scale;
					fgets(line, 100, stream);	  // read scale
					token = strtok(line, " ");
					obj->num_vertices = 8;
					//obj->vlist_local = vector<Point>();
					obj->vlist_local.resize(8);
					obj->vlist_local[0].x = -width / 2;
					obj->vlist_local[0].y = height / 2;
					obj->vlist_local[0].z = -length / 2;
					obj->vlist_local[1].x = width / 2;
					obj->vlist_local[1].y = height / 2;
					obj->vlist_local[1].z = -length / 2;
					obj->vlist_local[2].x = width / 2;
					obj->vlist_local[2].y = -height / 2;
					obj->vlist_local[2].z = -length / 2;
					obj->vlist_local[3].x = -width / 2;
					obj->vlist_local[3].y = -height / 2;
					obj->vlist_local[3].z = -length / 2;
					obj->vlist_local[4].x = -width / 2;
					obj->vlist_local[4].y = height / 2;
					obj->vlist_local[4].z = length / 2;
					obj->vlist_local[5].x = width / 2;
					obj->vlist_local[5].y = height / 2;
					obj->vlist_local[5].z = length / 2;
					obj->vlist_local[6].x = width / 2;
					obj->vlist_local[6].y = -height / 2;
					obj->vlist_local[6].z = length / 2;
					obj->vlist_local[7].x = -width / 2;
					obj->vlist_local[7].y = -height / 2;
					obj->vlist_local[7].z = length / 2;


				}
				else if (strncmp(line, "object", 6) == 0)
				{
					obj = new Object();
					fgets(line, 100, stream);
					obj->name = line;
					obj->type = "object";
					obj->name.pop_back(); // remove last character \n
					fgets(line, 100, stream);
					obj->scriptName = line;
					obj->scriptName.pop_back();
					fgets(line, 100, stream);
					token = strtok(line, seps);
					obj->world_pos.x = ((float)strtod(token, &stopstring)); //*scale;
					token = strtok(NULL, " ");
					obj->world_pos.y = ((float)strtod(token, &stopstring)); //*scale;
					token = strtok(NULL, " ");
					obj->world_pos.z = ((float)strtod(token, &stopstring));// *scale;
					if (obj->name == "camera")
					{
						cam->pos.x = -obj->world_pos.x;
						cam->pos.y = -obj->world_pos.y;
						cam->pos.z = -obj->world_pos.z;
					}
					fgets(line, 100, stream);	  // read direction			
					token = strtok(line, seps);
					obj->dir.x = ((float)strtod(token, &stopstring));
					token = strtok(NULL, " ");
					obj->dir.y = ((float)strtod(token, &stopstring));
					token = strtok(NULL, " ");
					obj->dir.z = ((float)strtod(token, &stopstring));
					if (obj->name == "camera")
					{
						cam->dir.x = obj->dir.x;
						cam->dir.y = obj->dir.y;
						cam->dir.z = obj->dir.z;
					}

					fgets(line, 100, stream);	  // read scale								
					fgets(line, 100, stream);  // read # of vertices	  
					//char* ptr;

					char* token2 = strtok(line, seps);
					int num = strtol(token2, &stopstring, 10);//strtod(token2, &stopstring);
					obj->num_vertices = num;// strtod(line, &ptr);
					obj->vlist_local.resize(num);
					for (int v = 0; v < obj->num_vertices; v++)
					{
						//obj->vlist_local[obj->num_vertices];
						fgets(line, 100, stream);
						token = strtok(line, " ");
						obj->vlist_local[v].x = ((float)strtod(token, &stopstring)) * scale;
						token = strtok(NULL, " ");
						obj->vlist_local[v].y = ((float)strtod(token, &stopstring)) * scale;
						token = strtok(NULL, " ");
						obj->vlist_local[v].z = ((float)strtod(token, &stopstring)) * scale;
					}
					fgets(line, 100, stream);  // read # of polys	  
					obj->num_polys = strtod(line, &stopstring);
					obj->plist.resize(obj->num_polys);
					for (int w = 0; w < obj->num_polys; w++)
					{
						fgets(line, 100, stream);
						token = strtok(line, " ");
						obj->plist[w].vert[0] = atoi(token);
						token = strtok(NULL, " ");
						obj->plist[w].vert[1] = atoi(token);
						token = strtok(NULL, " ");
						obj->plist[w].vert[2] = atoi(token);
					}
				}// end if
				if (obj->name!="camera")
					linked_list.push_back(*obj);
			} // end for		 
			fclose(stream);
		} // end if	        		
	} // end if
	
	return true;
}

bool CGfxOpenGL::Shutdown()
{
	glDeleteTextures(1, &m_textureObjectOne);
	glDeleteTextures(1, &m_textureObjectTwo);

	m_textureOne->Release();
	delete m_textureOne;

	return true;
}

void CGfxOpenGL::SetupProjection(int width, int height)
{
	if (height == 0)					// don't want a divide by zero
	{
		height = 1;					
	}

	glViewport(0, 0, width, height);		// reset the viewport to new dimensions
	glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
	glLoadIdentity();						// reset projection matrix

	// calculate perspective
	gluPerspective(54.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);

	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
	glLoadIdentity();						// reset modelview matrix

	m_windowWidth = width;
	m_windowHeight = height;
}

void CGfxOpenGL::Prepare(float dt)
{
	// change polygon z position
/*	if (m_zMoveNegative)
		m_zPos -= 5.0f*dt;
	else 
		m_zPos += 5.0f*dt;

	if (m_zPos > -5.0f)
	{
		m_zPos = -5.0f;
		m_zMoveNegative = true;
	}
	if (m_zPos < -20.0f)
	{
		m_zPos = -20.0f;
		m_zMoveNegative = false;
	}
*/	
}

void CGfxOpenGL::DrawObjects()
{
/*	//file handle
	HANDLE hFile;
	//something to contain the number of bytes read
	DWORD dwNumRead;
	//a boolean test variable, to test for success of reads
	BOOL bTest;
	//a buffer¡­ can actually be of any type
	DWORD dwBuffer[256];

	hFile = CreateFile("C:\\Documents and Settings\\Administrator\\My Documents\\Visual Studio 2005\\Projects\\GameEngine_v2.0\\GameEngine", GENERIC_READ, FILE_SHARE_READ,
                   NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	/* if there is a problem opening the file, a call to
 GetLastError will tell you what it is 

	bTest= ReadFile(hFile, dwBuffer, sizeof(DWORD)*256, &dwNumRead,NULL);
bTest=CloseHandle(hFile);
/* bTest will be TRUE if the read is successful.
 If false, take a look at GetLastError */
	Write_Error(fp_error, "Drawing objects...\n");
  
	 list<Object>::iterator it;
	 for(it=linked_list.begin(); it != linked_list.end();it++)
	 {
		*obj = (Object)*it;
		obj->vlist_trans.resize(obj->num_vertices);
		Write_Error(fp_error, "# of vertices: %d\n", obj->num_vertices);
		for (int j=0;j< obj->num_vertices;j++)
		{
			obj->vlist_trans[j].x=obj->world_pos.x + obj->vlist_local[j].x;
			obj->vlist_trans[j].y=obj->world_pos.y + obj->vlist_local[j].y;
			obj->vlist_trans[j].z=obj->world_pos.z + obj->vlist_local[j].z;
		}			
		if ( strncmp(obj->type.c_str(), "cube", 4) == 0)//(obj->name.substr(4) == "cube")
		{
			//front
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0, 2.0); glVertex3f(obj->vlist_trans[0].x, obj->vlist_trans[0].y,obj->vlist_trans[0].z);
				glTexCoord2f(2.0, 2.0); glVertex3f(obj->vlist_trans[1].x, obj->vlist_trans[1].y,obj->vlist_trans[1].z);
				glTexCoord2f(2.0, 0.0);	glVertex3f(obj->vlist_trans[2].x, obj->vlist_trans[2].y,obj->vlist_trans[2].z);
				glTexCoord2f(0.0, 0.0);	glVertex3f(obj->vlist_trans[3].x, obj->vlist_trans[3].y,obj->vlist_trans[3].z);
			glEnd();	
			// back
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0, 2.0); glVertex3f(obj->vlist_trans[4].x, obj->vlist_trans[4].y,obj->vlist_trans[4].z);
				glTexCoord2f(2.0, 2.0); glVertex3f(obj->vlist_trans[5].x, obj->vlist_trans[5].y,obj->vlist_trans[5].z);
				glTexCoord2f(2.0, 0.0);	glVertex3f(obj->vlist_trans[6].x, obj->vlist_trans[6].y,obj->vlist_trans[6].z);
				glTexCoord2f(0.0, 0.0);	glVertex3f(obj->vlist_trans[7].x, obj->vlist_trans[7].y,obj->vlist_trans[7].z);
			glEnd();	
			// top   
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0, 2.0); glVertex3f(obj->vlist_trans[4].x, obj->vlist_trans[4].y,obj->vlist_trans[4].z);
				glTexCoord2f(2.0, 2.0); glVertex3f(obj->vlist_trans[5].x, obj->vlist_trans[5].y,obj->vlist_trans[5].z);
				glTexCoord2f(2.0, 0.0);	glVertex3f(obj->vlist_trans[1].x, obj->vlist_trans[1].y,obj->vlist_trans[1].z);
				glTexCoord2f(0.0, 0.0);	glVertex3f(obj->vlist_trans[0].x, obj->vlist_trans[0].y,obj->vlist_trans[0].z);
			glEnd();
			// bottom   
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0, 2.0); glVertex3f(obj->vlist_trans[6].x, obj->vlist_trans[6].y,obj->vlist_trans[6].z);
				glTexCoord2f(2.0, 2.0); glVertex3f(obj->vlist_trans[7].x, obj->vlist_trans[7].y,obj->vlist_trans[7].z);
				glTexCoord2f(2.0, 0.0);	glVertex3f(obj->vlist_trans[2].x, obj->vlist_trans[2].y,obj->vlist_trans[2].z);
				glTexCoord2f(0.0, 0.0);	glVertex3f(obj->vlist_trans[3].x, obj->vlist_trans[3].y,obj->vlist_trans[3].z);
			glEnd();
			// left side  
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0, 2.0); glVertex3f(obj->vlist_trans[4].x, obj->vlist_trans[4].y,obj->vlist_trans[4].z);
				glTexCoord2f(2.0, 2.0); glVertex3f(obj->vlist_trans[0].x, obj->vlist_trans[0].y,obj->vlist_trans[0].z);
				glTexCoord2f(2.0, 0.0);	glVertex3f(obj->vlist_trans[3].x, obj->vlist_trans[3].y,obj->vlist_trans[3].z);
				glTexCoord2f(0.0, 0.0);	glVertex3f(obj->vlist_trans[7].x, obj->vlist_trans[7].y,obj->vlist_trans[7].z);
			glEnd();
			// right side  
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0, 2.0); glVertex3f(obj->vlist_trans[1].x, obj->vlist_trans[1].y,obj->vlist_trans[1].z);
				glTexCoord2f(2.0, 2.0); glVertex3f(obj->vlist_trans[5].x, obj->vlist_trans[5].y,obj->vlist_trans[5].z);
				glTexCoord2f(2.0, 0.0);	glVertex3f(obj->vlist_trans[6].x, obj->vlist_trans[6].y,obj->vlist_trans[6].z);
				glTexCoord2f(0.0, 0.0);	glVertex3f(obj->vlist_trans[2].x, obj->vlist_trans[2].y,obj->vlist_trans[2].z);
			glEnd();
		}
		else if (obj->type =="object") //(strncmp(obj->name,"object",6)==0)
		{
			int v1,v2,v3;
			for (int j=0;j<obj->num_vertices;j++)
			{
				obj->vlist_trans[j].x=obj->world_pos.x + obj->vlist_local[j].x;
				obj->vlist_trans[j].y=obj->world_pos.y + obj->vlist_local[j].y;
				obj->vlist_trans[j].z=obj->world_pos.z + obj->vlist_local[j].z;
			}

			for (int a=0; a<obj->num_polys; a++)
			{				
				glBegin(GL_TRIANGLES);										
					v1 = obj->plist[a].vert[0];
					v2 = obj->plist[a].vert[1];
					v3 = obj->plist[a].vert[2];
					glColor3f(1.0,0.0,0.0);
					glVertex3f(obj->vlist_trans[v1].x,obj->vlist_trans[v1].y,obj->vlist_trans[v1].z);
					glColor3f(0.0,1.0,0.0);
					glVertex3f(obj->vlist_trans[v2].x,obj->vlist_trans[v2].y,obj->vlist_trans[v2].z);
					glColor3f(0.0,0.0,1.0);
					glVertex3f(obj->vlist_trans[v3].x,obj->vlist_trans[v3].y,obj->vlist_trans[v3].z);
					glColor3f(1.0,1.0,1.0);					
				glEnd();
			}
		}

   }	

/*bTest will be true if the file closed correctly. 
 If false, take a look at GetLastError 

	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(2.0, 0.0); glVertex3f(2.0, -2.0, -2.0);
		glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -2.0, -2.0);
		glTexCoord2f(2.0, 2.0);	glVertex3f(2.0, -2.0, 2.0);
		glTexCoord2f(0.0, 2.0);	glVertex3f(-2.0, -2.0, 2.0);
	glEnd();	*/
}

void CGfxOpenGL::Render()
{	
	// clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// load the identity matrix (clear to default position and orientation)
	glLoadIdentity();

	float angY = cam->dir.y*3.14/180.0;
	float angX = cam->dir.x*3.14/180.0;

//gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x,0.0f, cam->pos.z+1.0f, 0.0f, 1.0f,0.0f);
	while (angY<0)
		angY+=6.28;
	while (angY>6.28)
		angY-=6.28;		

	while (angX<0)
		angX+=6.28;
	while (angX>6.28)
		angX-=6.28;		

	//if (angY>=0.0 && angY< 1.57 )			
	//{
	//	if (angY>0.785) // angYle > 45 degrees
	//	{
	//		angY=3.14f/2.0f-angY;
	//		gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x+sin(angY),cam->pos.y, cam->pos.z+cos(angY), 0.0f, 1.0f,0.0f);
	//	}
	//	else
	//		gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x+cos(angY),cam->pos.y, cam->pos.z+sin(angY), 0.0f, 1.0f,0.0f);
	//}
	//else if ( angY>1.57 && angY<3.14 )
	//{		
	//	angY-=1.57f;
	//	if (angY>0.785)
	//	{
	//		angY=3.14f/2.0f-angY;
	//		gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x-cos(angY),cam->pos.y, cam->pos.z+sin(angY), 0.0f, 1.0f,0.0f);
	//	}	
	//	else
	//		gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x-sin(angY),cam->pos.y, cam->pos.z+cos(angY), 0.0f, 1.0f,0.0f);
	//}
	//else if ( angY>=3.14 && angY<4.71 )
	//{
	//	angY-=3.14f;
	//	if (angY>0.785)
	//	{
	//		angY=3.14f/2.0f-angY;
	//		gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x-sin(angY),cam->pos.y, cam->pos.z-cos(angY), 0.0f, 1.0f,0.0f);
	//	}	
	//	else
	//		gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x-cos(angY),cam->pos.y, cam->pos.z-sin(angY), 0.0f, 1.0f,0.0f);
	//}
	//else if ( angY>4.71 && angY<=6.28 )
	//{
	//	angY-=4.71f;
	//	if (angY>0.785)
	//	{
	//		angY=3.14f/2.0f-angY;
	//		gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x+cos(angY),cam->pos.y, cam->pos.z-sin(angY), 0.0f, 1.0f,0.0f);
	//	}	
	//	else
	//		gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x+sin(angY),cam->pos.y, cam->pos.z-cos(angY), 0.0f, 1.0f,0.0f);
	//}

	//if (angX>=0.0 && angX< 1.57 ) // 1st quadrant	
	//{
	//	if (angX>0.785) // angleX > 45 degrees
	//	{
	//		angX=3.14f/2.0f-angX;
	//		gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x,cam->pos.y+sin(angX), cam->pos.z+cos(angX), 0.0f,-cos(angX), sin(angX));
	//	}
	//	else
	//		gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x,cam->pos.y+cos(angX), cam->pos.z+sin(angX), 0.0f,-sin(angX), cos(angX));
	//}
	//else if ( angX>1.57 && angX<3.14 ) // 2nd quadrant
	//{		
	//	angX-=1.57f;
	//	if (angX>0.785)
	//	{
	//		angX=3.14f/2.0f-angX;
	//		gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x,cam->pos.y-cos(angX), cam->pos.z+sin(angX), 0.0f,-sin(angX), -cos(angX));
	//	}	
	//	else
	//		gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x,cam->pos.y-sin(angX), cam->pos.z+cos(angX), 0.0f,-cos(angX), -sin(angX));
	//}
	//else if ( angX>=3.14 && angX<4.71 ) // 3rd quadrant
	//{
	//	angX-=3.14f;
	//	if (angX>0.785)
	//	{
	//		angX=3.14f/2.0f-angX;
	//		gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x,cam->pos.y-sin(angX), cam->pos.z-cos(angX), 0.0f,cos(angX), -sin(angX));
	//	}	
	//	else
	//		gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x,cam->pos.y-cos(angX), cam->pos.z-sin(angX), 0.0f,sin(angX), -cos(angX));
	//}
	//else if ( angX>4.71 && angX<=6.28 ) 
	//{
	//	angX-=4.71f;
	//	if (angX>0.785)
	//	{
	//		angX=3.14f/2.0f-angX;
	//		gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x,cam->pos.y+cos(angX), cam->pos.z-sin(angX), 0.0f,sin(angX),cos(angX) );
	//	}	
	//	else
	//		gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->pos.x,cam->pos.y+sin(angX), cam->pos.z-cos(angX), 0.0f,cos(angX), sin(angX));
	//}
	float radius = 1;
	cam->target.y = cam->pos.y+radius*sin(angX); 
	float newHradius = radius*cos(angX);
	cam->target.x = cam->pos.x+newHradius*cos(angY);
	cam->target.z = cam->pos.z+newHradius * sin(angY);

	cam->up.x = cam->pos.x - cam->target.x;
	cam->up.z = cam->pos.z - cam->target.z;
	cam->up.y = cam->pos.y+ radius*sin(angX+3.14/2);

	gluLookAt(cam->pos.x,cam->pos.y,cam->pos.z,cam->target.x, cam->target.y, cam->target.z, cam->up.x,cam->up.y, cam->up.z);
	Write_Error(fp_error,"camera angle: %f\n",angY);	
	
	// do it all again for the right polygon
	glPushMatrix();		
		glBindTexture(GL_TEXTURE_2D, m_textureObjectTwo);
		DrawObjects();
	glPopMatrix();
}
