
#include <list>
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
	CAM4DV1_PTR cam;     // the single camera
	OBJECT4DV1_PTR obj;     // used to hold our cube mesh                   
public:
	CGfxOpenGL();
	virtual ~CGfxOpenGL();

	bool Init(CAM4DV1 *camera);
	bool Shutdown();

	void SetupProjection(int width, int height);

	void Prepare(float dt);
	void Render();

	void DrawPlane();
	void setCam(CAM4DV1 *camera) { cam = camera;  }
	list<OBJECT4DV1> linked_list;
};

#endif