#include "Object.h"

#ifndef CUBE_H
#define CUBE_H

using namespace std;
class Cube : public Object
{
public:
	Cube();
	float width, length, height;
};

#endif