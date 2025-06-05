//#include "stdafx.h"
#include "Camera.h"

Camera::Camera(	 
                  Vector cam_pos,   // initial camera position
                  Vector cam_dir,  // initial camera angles
                  Vector *cam_target, // UVN target
                  float near_clip_z,     // near and far clipping planes
                  float far_clip_z,
                  float fov,             // field of view in degrees
                  float viewport_width,  // size of final screen viewport
                  float viewport_height)
{	
	camera_direction = cam_dir;
	field_of_view = fov;
	this->viewport_width = viewport_width;
	this->viewport_height = viewport_height;
    pos = cam_pos;
    dir = cam_dir;
    if (cam_target!=NULL)
        target = *cam_target;
}
