
#include <d3dx9math.h>

#include "Vector.h"

#ifndef C3DMODEL_H
#define C3DMODEL_H

class C3DModel
{
public:
	C3DModel(D3DXMATRIX * pMatWorld, Point position, Vector rotation);
	void MakeWorldMatrix( D3DXMATRIX * pMatWorld );
	void SetPosition(float x, float y, float z);
	void SetRotation(float pitch, float yaw, float roll);
	D3DXMATRIX ProjectionMatrix(const float near_plane, // Distance to near clipping 
                                         // plane
                 const float far_plane,  // Distance to far clipping 
                                         // plane
                 const float fov_horiz,  // Horizontal field of view 
                                         // angle, in radians
                 const float fov_vert);   // Vertical field of view 
                                         // angle, in radians
private:
	float m_xPos, m_yPos, m_zPos;
	float m_fPitch, m_fYaw, m_fRoll;
};

#endif