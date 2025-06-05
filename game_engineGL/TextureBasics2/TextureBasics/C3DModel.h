//#include <d3dx9math.h>

#include <windows.h>
#include <algorithm>
#include <utility>


#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>

using namespace DirectX;
//#define DllExports   __declspec( dllexport )

/*#include <windows.h>
#include <objidl.h>
//#include <gdiplus.h>
#include <gdiplusbase.h>
using namespace Gdiplus;

#pragma comment (lib,"Gdiplus.lib")
#include <gdiplusmatrix.h>*/

#include "Vector.h"

#ifndef C3DMODEL_H
#define C3DMODEL_H

#define D3DXMATRIX XMMATRIX   //XMFLOAT4X4//

class C3DModel
{
public:
	C3DModel( Point position, Vector rotation, Vector scale);
	D3DXMATRIX MakeWorldMatrix( );	
	void SetPosition(float x, float y, float z);
	void SetRotation(float pitch, float yaw, float roll);
	void SetScale(float x, float y, float z);
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
	float m_xScale, m_yScale, m_zScale;
};

#endif