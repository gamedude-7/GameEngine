#pragma once


#ifndef CAMERA_H
#define CAMERA_H

#include "GameEngineLib.h"
#include "Camera.h"
#include "Vector.h"
//#include <d3d11.h>
//#include <directxmath.h>

//using namespace DirectX;


// defines for special types of camera projections
#define CAM_PROJ_NORMALIZED        0x0001
#define CAM_PROJ_SCREEN            0x0002
#define CAM_PROJ_FOV90             0x0004

#define CAM_MODEL_EULER            0x0008
#define CAM_MODEL_UVN              0x0010

#define UVN_MODE_SIMPLE            0 
#define UVN_MODE_SPHERICAL         1

class Camera
{
public:
	Camera(		
                  Vector cam_pos,   // initial camera position
                  Vector cam_dir,  // initial camera angles
                  Vector *cam_target, // UVN target
                  float near_clip_z,     // near and far clipping planes
                  float far_clip_z,
                  float fov,             // field of view in degrees
                  float viewport_width,  // size of final screen viewport
                  float viewport_height);
    Vector pos;
    Vector dir;   
    Vector target;
    Vector up;
private:	
	Vector camera_direction;
	float field_of_view;
	float viewport_width;   
    float viewport_height;
    float near_clip_z;     // near and far clipping planes
    float far_clip_z;
} ;

#endif