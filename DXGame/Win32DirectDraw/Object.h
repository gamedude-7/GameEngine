#include <string>
#include <vector>
#include "Vector.h"
#include "Poly.h"

#ifndef OBJECT_H
#define OBJECT_H

#define OBJECT_MAX_VERTICES	64
#define OBJECT_MAX_POLYS	128
using namespace std;

class Object
{
public:
	Object();
	Point world_pos;  // position of object in world
    Vector dir;         // rotation angles of object in world
                                // cords or unit direction vector user defined ???
	Vector scale;

	int num_vertices;    // number of verticesof this object
	//Poly plist[OBJECT_MAX_POLYS];  // array of polygons  
	vector< Poly > plist;
	vector< Point > vlist_trans;    // array of transformed vertices
	vector< Point > vlist_local;	//array of local vertices
	int num_polys;   // number of polygons in object mesh
	void AddLocalVertex(Point);
	void AddTransformedVertex(Point);
protected:

	
private:
	int id;
	string name;
	int poly_num_verts;
	int state;           //state of object
    int attr;              // attributes of object
       
    float avg_radius; // average radius of object used for collision detection
    float max_radius;//maximum radius of object

   
         
    Vector ux,uy,uz;  //local axes to track full orientation
                                //this is updated automatically during rotation calls
  
	//Point vlist_local[OBJECT_MAX_VERTICES];// = new Point[OBJECT_MAX_VERTICES];    // array of local vertices
    
   
     
};

#endif