#include "stdafx.h"
#include "Vector.h"
#include "Level.h"
#include "Color.h"
#include <iostream>
#include <sstream>
#include <fstream>


using namespace std;

Level::Level(string filename)
{
	ifstream fileStream;
	Color color;
	string buffer;
	string type;
	
	// Step 2: open the file for reading
	fileStream.open(filename, ios_base::in);
	vector< Cube > listOfObjects;
	
	if (fileStream.is_open() && fileStream.good())
	{
		
		
		fileStream >> numOfObjects;
		for (int i=0; i < numOfObjects; i ++)
		{
			fileStream >> type;
			if (type == "cube")
			{
				Cube cube;
				fileStream >> cube.world_pos.x >> cube.world_pos.y >> cube.world_pos.z;
				fileStream >> cube.width >> cube.height >> cube.length;
				fileStream >> cube.dir.x >> cube.dir.y >> cube.dir.z;
				fileStream >> cube.scale.x >> cube.scale.y >> cube.scale.z;
				//cube.vlist_local = vector<Point>();
				listOfObjects.push_back(cube);
			}
			else if (type == "object")
			{
				Object object;			
				D3DXMATRIX matrix;
				fileStream >> object.world_pos.x >> object.world_pos.y >> object.world_pos.z;
				fileStream >> object.dir.x >> object.dir.y >> object.dir.z;
				fileStream >> object.scale.x >> object.scale.y >> object.scale.z;
				fileStream >> object.num_vertices;
				double x, y, z;
				
				for (int i = 0; i < object.num_vertices; i++)
				{					
					fileStream >> x >> y >> z;
					Point p(x,y,z);
				
					object.AddLocalVertex(p);
				}
				
				fileStream >> object.num_polys;
				for (int i = 0; i < object.num_polys; i++)
				{
					fileStream >> x >> y >> z;
					Point p(x,y,z);
					object.AddTransformedVertex(p);
					Poly poly;
					poly.vert[0] = x;
					poly.vert[1] = y;
					poly.vert[2] = z;
					object.plist.push_back(poly);					
				}
				objectList.push_back(object);
				matrices.push_back(matrix);
				
			}
		}		
		//objectList = listOfObjects;
		fileStream.close();
	}
	
}

Level::Level(Vector *scale, vector< Object > *obj_list, Color *c)
{
	ifstream fileStream;
	Color color;
	string buffer;

	// Step 2: open the file for reading
	fileStream.open("compiled.lvl", ios_base::in);

	if (fileStream.is_open() && fileStream.good())
	{
		getline(fileStream, buffer);
		
		color.r = (unsigned char) strtok((char*)buffer.c_str(), " ");
		color.g = (unsigned char) strtok((char*)buffer.c_str(), " ");
		color.b = (unsigned char) strtok((char*)buffer.c_str(), " ");
		color.a = (unsigned char) strtok((char*)buffer.c_str(), " ");
	}
}