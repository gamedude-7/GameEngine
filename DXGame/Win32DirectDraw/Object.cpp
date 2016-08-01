#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	scale = Vector(1,1,1,1);
	num_vertices = 0;
}

void Object::AddLocalVertex(Point p)
{
	vlist_local.push_back(p);

}

void Object::AddTransformedVertex(Point p)
{
	vlist_trans.push_back(p);	
}