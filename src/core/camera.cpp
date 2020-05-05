//
// Created by novasurfer on 5/5/20.
//

#include "camera.h"
#include "math/transform.h"

namespace sc2d
{

    void Camera::make_orthographic(f32 width, f32 height, f32 near, f32 far)
    {
        this->width = width;
        this->height = height;
        this->near = near;
        this->far = far;
        proj = math::ortho(0.0, width, height, 0.0, near, far);
    }
}
