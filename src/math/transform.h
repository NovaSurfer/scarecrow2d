//
// Created by Maksim Ruts on 25-Jan-19.
//

#ifndef INC_2D_GAME_TRANSFORM_H
#define INC_2D_GAME_TRANSFORM_H

#include "matrix4.h"
#include "matrix3.h"
#include "vector3.h"

namespace math {

    struct Transform {
        mat4 translation(float x, float y, float z);
        mat4 translation(const vec3& pos);
        vec3 get_translation(const mat4& mat);
        mat4 scale(float x, float y, float z);
        mat4 scale(const vec3& scale);
        vec3 get_scale(const mat4& mat);
        mat4 rotation(float pitch, float yaw, float roll);
        mat3 rotation3x3(float pitch, float yaw, float roll);
        mat4 z_rotation(float angle);
        mat3 z_rotation3x3(float angle);
        mat4 y_rotation(float angle);
        mat3 y_rotation3x3(float angle);       
        mat4 x_rotation(float angle);
        mat3 x_rotation3x3(float angle);
        mat4 axis_angle(const vec3& axis, float angle);
        mat3 axis_angle3x3(const vec3& axis, float angle);
    };
}


#endif //INC_2D_GAME_TRANSFORM_H