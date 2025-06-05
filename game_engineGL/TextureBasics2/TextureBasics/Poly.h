#include "Vector.h"

#ifndef POLYGON_H
#define POLYGON_H

class Poly
{
public:
	Poly();
	int vert[3];  // the indices into the vertex list
private:
	int state;    // state information
    int attr;      // physical attributes of polygon
    int color;    // color of polygon

    Point vlist[3];  // the vertices of this triangle
    Point tvlist[3]; // the vertices after transformation if needed

	

    //Poly *next;  // pointer to next polygon in list??
    //Poly *prev;  // pointer to previous polygon in list??
};

#endif