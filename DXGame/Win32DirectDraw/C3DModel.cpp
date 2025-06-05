#include "stdafx.h"
#include "C3DModel.h"

C3DModel::C3DModel( Point position, Vector rotation, Vector scale)
{
	SetPosition(position.x, position.y, position.z);
	SetRotation(rotation.getX(), rotation.getY(), rotation.getZ());
    SetScale(scale.x, scale.y, scale.z);
    //*pMatWorld = MakeWorldMatrix(*pMatWorld);
}

D3DXMATRIX C3DModel::MakeWorldMatrix(  )
{
    D3DXMATRIX MatTemp;  // Temp matrix for rotations.
    D3DXMATRIX MatRot;   // Final rotation matrix, applied to 
                         // pMatWorld.
    D3DXMATRIX pMatWorld;
    // Using the left-to-right order of matrix concatenation,
    // apply the translation to the object's world position
    // before applying the rotations.
    pMatWorld = XMMatrixSet(m_xPos, m_yPos, m_zPos, 1,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0);
        //XMMatrixTranslation(m_xPos, m_yPos, m_zPos);
    //D3DXMatrixTranslation(pMatWorld, m_xPos, m_yPos, m_zPos);
    MatRot = XMMatrixIdentity();//D3DXMatrixIdentity(&MatRot);

    // Now, apply the orientation variables to the world matrix
    if(m_fPitch || m_fYaw || m_fRoll) {
        // Produce and combine the rotation matrices.
        MatTemp = XMMatrixRotationX(m_fPitch);
        //D3DXMatrixRotationX(&MatTemp, m_fPitch);         // Pitch
        MatRot = XMMatrixMultiply(MatRot, MatTemp);
        //D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);
        MatTemp = XMMatrixRotationY(m_fYaw);
        //D3DXMatrixRotationY(&MatTemp, m_fYaw);           // Yaw
        MatRot = XMMatrixMultiply(MatRot, MatTemp);
        //D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);
        MatTemp = XMMatrixRotationZ( m_fRoll);          // Roll
        MatRot = XMMatrixMultiply(MatRot,MatTemp);
        
        // Apply the rotation matrices to complete the world matrix.
        //D3DXMatrixMultiply(pMatWorld, &MatRot, pMatWorld);
        pMatWorld = MatRot;//XMMatrixMultiply(pMatWorld,MatRot );
    }
    return MatRot;// pMatWorld;
}

void C3DModel::SetPosition(float x, float y, float z)
{
	m_xPos = x;
	m_yPos = y;
	m_zPos = z;
}

void C3DModel::SetRotation(float pitch, float yaw, float roll)
{
	m_fPitch = pitch;
	m_fYaw = yaw;
	m_fRoll = roll;
}

void C3DModel::SetScale(float x, float y, float z)
{
    m_xScale = x;
    m_yScale = y;
    m_zScale = z;
}

D3DXMATRIX C3DModel::ProjectionMatrix(const float near_plane, // Distance to near clipping 
                                         // plane
                 const float far_plane,  // Distance to far clipping 
                                         // plane
                 const float fov_horiz,  // Horizontal field of view 
                                         // angle, in radians
                 const float fov_vert)   // Vertical field of view 
                                         // angle, in radians
{
    float    h, w, Q;

    w = (float)1/tan(fov_horiz*0.5);  // 1/tan(x) == cot(x)
    h = (float)1/tan(fov_vert*0.5);   // 1/tan(x) == cot(x)
    Q = far_plane/(far_plane - near_plane);

    D3DXMATRIX ret;
    
    ZeroMemory(&ret, sizeof(ret));
    ret = XMMatrixSet(w, 0, 0, 0,
        0, h, 0, 0,
        0, 0, Q, 1,
        0, 0, -Q * near_plane, 0);
    /*ret._11 = w;
    ret._22 = h;
    ret._33 = Q;
    ret._43 = -Q * near_plane;
    ret._34 = 1;*/
    /*ret(0, 0) = w;
    ret(1, 1) = h;
    ret(2, 2) = Q;
    ret(3, 2) = -Q*near_plane;
    ret(2, 3) = 1;*/
    return ret;
}   // End of ProjectionMatrix