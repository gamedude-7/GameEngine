
#include <list>
#include "Camera.h"
using namespace std;
#ifndef __GL_COMPONENT
#define __GL_COMPONENT

#define PI           3.14159
#define TWO_PI       PI*2.0
#define HALF_PI      PI/2.0

class CTargaImage;

struct Vertex
{
	float x,y,z;
};

class CGfxOpenGL
{
private:
	int m_windowWidth;
	int m_windowHeight;
	
	CTargaImage *m_textureOne;

	unsigned int m_textureObjectOne;
	unsigned int m_textureObjectTwo;
	
	bool  m_zMoveNegative;
	Camera *cam;     // the single camera
	Object *obj;     // used to hold our cube mesh      
	FILE* fp_error;
public:
	CGfxOpenGL();
	virtual ~CGfxOpenGL();

	bool Init(Camera *camera, FILE *fp_override);
	bool Shutdown();

	void SetupProjection(int width, int height);

	void Prepare(float dt);
	void Render();

	void DrawObjects();
	void setCam(Camera *camera) { cam = camera;  }
	list<Object> linked_list;
};

#endif