#include "stdafx.h"
#include "Triangle.h"
#include <vector>

Triangle::Triangle(Point v1, Point v2, Point v3)
{
	vlist_trans.push_back(v1);
	vlist_trans.push_back(v2);
	vlist_trans.push_back(v3);
}