//
// Created by Maksim Ruts on 25-Jan-19.
//

#include "transform.h"
#include "utils.h"

namespace math {

    mat4 Transform::translation(float x, float y, float z)
    {
        return mat4(1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    x,    y,    z,    1.0f);
    }

    mat4 Transform::translation(const vec3& pos)
    {
        return mat4(1.0f, 0.0f, 0.0f, 0.0f,      
                    0.0f, 1.0f, 0.0f, 0.0f,      
                    0.0f, 0.0f, 1.0f, 0.0f,     
                    pos.x,pos.y,pos.z,1.0f);
    }

    vec3 Transform::get_translation(const mat4& mat)
    {
        return vec3(mat.n[3][0], mat.n[3][1], mat.n[3][2]);
    }

    mat4 Transform::scale(float x, float y, float z)
    {
           return mat4(x,    0.0f, 0.0f, 0.0f,       
                       0.0f,    y, 0.0f, 0.0f,       
                       0.0f, 0.0f,    z, 0.0f,      
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    mat4 Transform::scale(const vec3& scale)
    {
           return mat4(scale.x, 0.0f, 0.0f, 0.0f,       
                       0.0f, scale.y, 0.0f, 0.0f,       
                       0.0f, 0.0f, scale.z, 0.0f,      
                       0.0f, 0.0f, 0.0f, 1.0f  );
    }

    mat4 Transform::rotation(float pitch, float yaw, float roll)
    {
        return z_rotation(roll) * x_rotation(pitch) * y_rotation(yaw);
    }

    mat3 Transform::rotation3x3(float pitch, float yaw, float roll)
    {
        return z_rotation3x3(roll) * x_rotation3x3(pitch) * y_rotation3x3(yaw);
    }

    mat4 Transform::z_rotation(float angle)
    {
        angle = utils::deg2rad(angle);
        return mat4(cosf(angle), sinf(angle), 0.0f, 0.0f,
                    -sinf(angle), cosf(angle), 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
    }

    mat3 Transform::z_rotation3x3(float angle)
    {
        angle = utils::deg2rad(angle);
        return mat3(cosf(angle), sinf(angle), 0.0f,
                    -sinf(angle), cosf(angle), 0.0f,
                    0.0f, 0.0f, 1.0f);
    }

    mat4 Transform::y_rotation(float angle)
    {
        angle = utils::deg2rad(angle);
        return mat4(cosf(angle), 0.0f, -sinf(angle), 0.0f, 
                    0.0f, 1.0f, 0.0f, 0.0f, 
                    sinf(angle), 0.0f, cosf(angle), 0.0f,      
                    0.0f, 0.0f, 0.0f, 1.0f); 
    }

    mat3 Transform::y_rotation3x3(float angle)
    {
        angle = utils::deg2rad(angle);
        return mat3(cosf(angle), 0.0f, -sinf(angle), 
                    0.0f, 1.0f, 0.0f,
                    sinf(angle), 0.0f, cosf(angle)); 
    }

    mat4 Transform::x_rotation(float angle)
    {
        angle = utils::deg2rad(angle);
        return mat4(1.0f, 0.0f, 0.0f, 0.0f,       
                    0.0f, cosf(angle), sinf(angle), 0.0f,       
                    0.0f, -sinf(angle), cos(angle), 0.0f,       
                    0.0f, 0.0f, 0.0f, 1.0f);
    }

    mat3 Transform::x_rotation3x3(float angle)
    {
        angle = utils::deg2rad(angle);
        return mat3(1.0f, 0.0f, 0.0f,
                    0.0f, cosf(angle), sinf(angle),
                    0.0f, -sinf(angle), cos(angle)); 
    }

    mat4 Transform::axis_angle(const vec3& axis, float angle)
    {
        angle = utils::deg2rad(angle);
        float c = cosf(angle);
        float s = sinf(angle);
        float t = 1.0f - cosf(angle);

        vec3 v = axis;

        if(!utils::cmp(magnitudeSq(axis), 1.0f))
        {
            v = normalize(v);
        }

        return mat4(
                t * (v.x * v.x) + c, t * v.x * v.y + s * v.z, t * v.x * v.z - s * v.y, 0.0f,
                t * v.x * v.y - s * v.z, t * (v.y * v.y) + c, t * v.y * v.z + s * v.x, 0.0f,
                t * v.x * v.z + s * v.y, t * v.y * v.z - s * v.x, t * (v.z * v.z) + c, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
    }

    mat3 Transform::axis_angle3x3(const vec3& axis, float angle)
    {
        angle = utils::deg2rad(angle);
        float c = cosf(angle);
        float s = sinf(angle);
        float t = 1.0f - cosf(angle);

        vec3 v = axis;

        if(!utils::cmp(magnitudeSq(axis), 1.0f))
        {
            v = normalize(v);
        }

        return mat3(
                t * (v.x * v.x) + c, t * v.x * v.y + s * v.z, t * v.x * v.z - s * v.y,
                t * v.x * v.y - s * v.z, t * (v.y * v.y) + c, t * v.y * v.z + s * v.x,
                t * v.x * v.z + s * v.y, t * v.y * v.z - s * v.x, t * (v.z * v.z) + c);
    }
}