//
// Created by novasurfer on 5/5/20.
//

#ifndef SCARECROW2D_CAMERA_H
#define SCARECROW2D_CAMERA_H

#include "base/types.h"
#include "math/matrix4.h"

namespace sc2d
{

    class Camera
    {
    public:
        void make_orthographic(f32 width, f32 height, f32 near, f32 far);
        math::mat4 get_proj() const
        {
            return proj;
        }

    private:
        f32 width;
        f32 height;
        f32 Near;
        f32 Far;
        f32 aspect;
        math::mat4 proj;
    };
}

#endif //SCARECROW2D_CAMERA_H
