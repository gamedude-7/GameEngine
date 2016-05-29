#include <vector>
#include <string>
#include "Object.h"
#include "Cube.h"
#include "Color.h"
#include "C3DModel.h"

using namespace std;

#ifndef LEVEL_H
#define LEVEL_H

class Level
{
public:
	Level(Vector *scale, vector< Object > *obj_list, Color *c);
	Level(string filename);
	vector< Object > objectList;
	vector< C3DModel> models;
	vector< D3DXMATRIX> matrices;
private:
	
	int numOfObjects;
};

#endif