//
// Created by Maksim Ruts on 25-Jan-19.
//

#include "transform.h"
#include "utils.h"

namespace math {

    mat4 translation(float x, float y, float z)
    {
        return mat4(1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    x,    y,    z,    1.0f);
    }

    mat4 translation(const vec3& pos)
    {
        return mat4(1.0f, 0.0f, 0.0f, 0.0f,      
                    0.0f, 1.0f, 0.0f, 0.0f,      
                    0.0f, 0.0f, 1.0f, 0.0f,     
                    pos.x,pos.y,pos.z,1.0f);
    }

    vec3 get_translation(const mat4& mat)
    {
        return vec3(mat.n[3][0], mat.n[3][1], mat.n[3][2]);
    }

    mat4 scale(float x, float y, float z)
    {
           return mat4(x,    0.0f, 0.0f, 0.0f,       
                       0.0f,    y, 0.0f, 0.0f,       
                       0.0f, 0.0f,    z, 0.0f,      
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    mat4 scale(const vec3& scale)
    {
           return mat4(scale.x, 0.0f, 0.0f, 0.0f,       
                       0.0f, scale.y, 0.0f, 0.0f,       
                       0.0f, 0.0f, scale.z, 0.0f,      
                       0.0f, 0.0f, 0.0f, 1.0f  );
    }

    vec3 get_scale(const mat4 &mat)
    {
        return vec3(mat.n[0][0], mat.n[1][1], mat.n[2][2]);
    }

    mat4 rotation(float pitch, float yaw, float roll)
    {
        return z_rotation(roll) * x_rotation(pitch) * y_rotation(yaw);
    }

    mat3 rotation3x3(float pitch, float yaw, float roll)
    {
        return z_rotation3x3(roll) * x_rotation3x3(pitch) * y_rotation3x3(yaw);
    }

    mat4 z_rotation(float angle)
    {
        angle = utils::deg2rad(angle);
        return mat4(cosf(angle), sinf(angle), 0.0f, 0.0f,
                    -sinf(angle), cosf(angle), 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
    }

    mat3 z_rotation3x3(float angle)
    {
        angle = utils::deg2rad(angle);
        return mat3(cosf(angle), sinf(angle), 0.0f,
                    -sinf(angle), cosf(angle), 0.0f,
                    0.0f, 0.0f, 1.0f);
    }

    mat4 y_rotation(float angle)
    {
        angle = utils::deg2rad(angle);
        return mat4(cosf(angle), 0.0f, -sinf(angle), 0.0f, 
                    0.0f, 1.0f, 0.0f, 0.0f, 
                    sinf(angle), 0.0f, cosf(angle), 0.0f,      
                    0.0f, 0.0f, 0.0f, 1.0f); 
    }

    mat3 y_rotation3x3(float angle)
    {
        angle = utils::deg2rad(angle);
        return mat3(cosf(angle), 0.0f, -sinf(angle), 
                    0.0f, 1.0f, 0.0f,
                    sinf(angle), 0.0f, cosf(angle)); 
    }

    mat4 x_rotation(float angle)
    {
        angle = utils::deg2rad(angle);
        return mat4(1.0f, 0.0f, 0.0f, 0.0f,       
                    0.0f, cosf(angle), sinf(angle), 0.0f,       
                    0.0f, -sinf(angle), cos(angle), 0.0f,       
                    0.0f, 0.0f, 0.0f, 1.0f);
    }

    mat3 x_rotation3x3(float angle)
    {
        angle = utils::deg2rad(angle);
        return mat3(1.0f, 0.0f, 0.0f,
                    0.0f, cosf(angle), sinf(angle),
                    0.0f, -sinf(angle), cos(angle)); 
    }

    mat4 axis_angle(const vec3& axis, float angle)
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

    mat3 axis_angle3x3(const vec3& axis, float angle)
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

    vec3 multiply_vector(const vec3& vec, const mat3& mat)
    {
        vec3 result;
        result.x = dot(vec, mat[0]);
        result.y = dot(vec, mat[1]);
        result.z = dot(vec, mat[2]);
        return result;
    }

    vec4 multiply_vector(const vec4& vec, const mat4& mat)
    {
        vec4 result;
        result.x = dot(vec, mat[0]);
        result.y = dot(vec, mat[1]);
        result.z = dot(vec, mat[2]);
        result.w = dot(vec, mat[3]);
        return result;
    }

    mat4 transform(const vec3& scale, const vec3& euler_rot, const vec3& translate)
    {
        return math::scale(scale) * rotation(euler_rot.x, euler_rot.y, euler_rot.z) * translation(translate);
    }

    mat4 transform(const vec3& scale, const vec3& rot_axis, float rot_angle, const vec3& translate)
    {
        return math::scale(scale) * axis_angle(rot_axis, rot_angle) * translation(translate);
    }

    mat4 look_at(const vec3& pos, const vec3& target, const vec3& up)
    {
        vec3 forward = normalize(target - pos);
        vec3 right = normalize(cross(up,forward));
        vec3 new_up = cross(forward, right);

        return mat4(
                right.x, new_up.x, forward.x, 0.0f,
                right.y, new_up.y, forward.y, 0.0f,
                right.z, new_up.z, forward.z, 0.0f,
                -dot(right, pos), -dot(new_up, pos), -dot(forward, pos), 1.0f);
    }

    mat4 perspective(float fov, float aspect, float z_near, float z_far)
    {
        float tan_half_fov = tanf(utils::deg2rad((fov * 0.5f)));
        float fov_y = 1.0f / tan_half_fov; // cot(fov/2)
        float fov_x= fov_y / aspect;       // cot(fov/2) / aspect
        mat4 result;
        result.n[0][0] = fov_x;
        result.n[1][1] = fov_y;
        // n[2][2] = far / range
        result.n[2][2] = z_far / (z_far - z_near);
        result.n[2][3] = 1.0f;
        // n[3][2] = - near * (far / range)
        result.n[3][2] = -z_near * result.n[2][2];
        result.n[3][3] = 0.0f;
        return result;
    }

    mat4 ortho(float left, float right, float bottom, float top, float z_near, float z_far)
    {
        float _11 = 2.0f / (right - left);
        float _22 = 2.0f / (top - bottom);
        float _33 = 1.0f / (z_far - z_near);
        float _41 = (left + right) / (left - right);
        float _42 = (top + bottom) / (bottom - top);
        float _43 = (z_near) / (z_near - z_far);
        return mat4(
                _11, 0.0f, 0.0f, 0.0f,
                0.0f, _22, 0.0f, 0.0f,
                0.0f, 0.0f, _33, 0.0f,
                _41, _42, _43, 1.0f
        );
    }
}