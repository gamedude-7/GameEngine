//#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	scriptName = "";
	scale = Vector(1,1,1,1);
	num_vertices = 0;
	max_radius = 0;
}

void Object::AddLocalVertex(Point p)
{
	vlist_local.push_back(p);

}

void Object::AddTransformedVertex(Point p)
{
	vlist_trans.push_back(p);	
}

void Object::setMaxRadius(float r)
{
	max_radius = r;
}