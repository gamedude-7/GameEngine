// GAMEENGINELIB.H - Header file for GAMEENGINELIB.CPP game engine library

// watch for multiple inclusions
#ifndef GAMEENGINELIB
#define GAMEENGINELIB

#define MAX_OBJECTS						  32768
// defines for objects version 1
#define OBJECT4DV1_MAX_VERTICES           1024  // 64
#define OBJECT4DV1_MAX_POLYS              1024 // 128

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600
#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600
#define SCREEN_BPP		16

typedef struct VECTOR4D_TYP
{
union
    {
    float M[4]; // array indexed storage

    // explicit names
    struct
         {
         float x,y,z,w;
         }; // end struct
    }; // end union

} VECTOR4D, POINT4D, *VECTOR4D_PTR, *POINT4D_PTR;

// RGB+alpha color
typedef struct RGBAV1_TYP
{
union 
    {
    int rgba;                    // compressed format
    UCHAR rgba_M[4];             // array format
    struct {  UCHAR a,b,g,r;  }; // explict name format
    }; // end union
    
} RGBAV1, *RGBAV1_PTR;

// a polygon based on an external vertex list
typedef struct POLY4DV1_TYP
{
int state;    // state information
int attr;     // physical attributes of polygon
int color;    // color of polygon

POINT4D_PTR vlist; // the vertex list itself
int vert[3];       // the indices into the vertex list

} POLY4DV1, *POLY4DV1_PTR;

// an object based on a vertex list and list of polygons
typedef struct OBJECT4DV1_TYP
{
int  id;           // numeric id of this object
char name[64];     // ASCII name of object just for kicks
int  state;        // state of object
int  attr;         // attributes of object
float avg_radius;  // average radius of object used for collision detection
float max_radius;  // maximum radius of object

POINT4D world_pos;  // position of object in world

VECTOR4D dir;       // rotation angles of object in local
                    // cords or unit direction vector user defined???

VECTOR4D ux,uy,uz;  // local axes to track full orientation
                    // this is updated automatically during
                    // rotation calls

int num_vertices;   // number of vertices of this object

POINT4D vlist_local[OBJECT4DV1_MAX_VERTICES]; // array of local vertices
POINT4D vlist_trans[OBJECT4DV1_MAX_VERTICES]; // array of transformed vertices

int num_polys;        // number of polygons in object mesh


POLY4DV1 plist[OBJECT4DV1_MAX_POLYS];  // array of polygons

} OBJECT4DV1, *OBJECT4DV1_PTR;

typedef struct OBJECTLIST4DV1_TYP
{
// the object list is an array of pointers each pointing to 
// a self contained "object"
OBJECT4DV1_PTR obj_ptrs[MAX_OBJECTS];

int num_objs; // number of polys in render list
} OBJECTLIST4DV1, *OBJECTLIST4DV1_PTR;

// container structure for bitmaps .BMP file
typedef struct BITMAP_FILE_TAG
{
    BITMAPFILEHEADER bitmapfileheader;  // this contains the bitmapfile header
    BITMAPINFOHEADER bitmapinfoheader;  // this is all the info including the palette
    PALETTEENTRY     palette[256];      // we will store the palette here
    UCHAR* buffer;           // this is a pointer to the data

} BITMAP_FILE, * BITMAP_FILE_PTR;

int LoadLevel_LVL(VECTOR4D_PTR scale, OBJECTLIST4DV1_PTR obj_list, RGBAV1_PTR color);

unsigned int ExtractGreen(unsigned int nSourceColor);
unsigned short ConvertRGB888toRGB565(unsigned int nSourceColor);
int Draw_Pixel16(int x, int y, int color, UCHAR* video_buffer, int lpitch);
int Draw_Line16(int xo, int yo, int x1, int y1, int color, UCHAR* vb_start, int lpitch);
int Draw_Clip_Line(int x0, int y0, int x1, int y1, int color,
    UCHAR* dest_buffer, int lpitch);
int Clip_Line(int& x1, int& y1, int& x2, int& y2);

int Load_Bitmap_File(BITMAP_FILE_PTR bitmap, char* filename);
int Flip_Bitmap(unsigned int* image, int bytes_per_line, int height);
#endif