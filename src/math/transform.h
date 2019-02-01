//
// Created by Maksim Ruts on 25-Jan-19.
//

#ifndef INC_2D_GAME_TRANSFORM_H
#define INC_2D_GAME_TRANSFORM_H

#include "matrix4.h"
#include "matrix3.h"
#include "vector3.h"
#include "vector4.h"

namespace math {
    /// Matrices transformation operations
    struct Transform {

        /**
         * Creates translation matrix
         * @param x component
         * @param y component
         * @param z component
         * @return identity matrix with translation stored in 41, 42, 43 elements (x, y, z)
         */
        mat4 translation(float x, float y, float z) const;

        /**
         * Creates translation matrix
         * @param pos translation vector3
         * @return identity matrix with translation stored in 41, 42, 43 elements
         */
        mat4 translation(const vec3& pos) const;

        /**
         * Returns translation vector
         * @param mat
         * @return translation vector
         */
        vec3 get_translation(const mat4& mat) const;

        /**
         * Creates scaling matrix
         * @param x component
         * @param y component
         * @param z component
         * @return identity matrix with translation stored in 11, 22, 33 elements (x, y, z)
         */
        mat4 scale(float x, float y, float z) const;

        /**
         * Creates scaling matrix
         * @param scale vector
         * @return identity matrix with translation stored in 11, 22, 33 elements
         */
        mat4 scale(const vec3& scale) const;

        /**
         * Returns scaling vector
         * @param mat
         * @return vector with scale for each axis
         */
        vec3 get_scale(const mat4& mat) const;

        /**
         * Combines Euler angles that represent rotation around each matrix
         * @param pitch object's local Lateral Axis (X-Axis)
         * @param yaw object's local Perpendicular Axis (Y-Axis)
         * @param roll object's local Longitudinal Axis (Z-Axis)
         * @return rotated matrix
         */
        mat4 rotation(float pitch, float yaw, float roll) const;

        /**
         * Combines Euler angles that represent rotation around each matrix
         * @param pitch object's local Lateral Axis (X-Axis)
         * @param yaw object's local Perpendicular Axis (Y-Axis)
         * @param roll object's local Longitudinal Axis (Z-Axis)
         * @return rotated matrix
         */
        mat3 rotation3x3(float pitch, float yaw, float roll) const;

        /**
         * Rotates Z-basis vector for the matrix by given angle
         * @param angle rotation
         * @return identity matrix with rotated Z-basis vector
         */
        mat4 z_rotation(float angle) const;

        /**
         * Rotates Z-basis vector for the matrix by given angle
         * @param angle rotation
         * @return identity matrix with rotated Z-basis vector
         */
        mat3 z_rotation3x3(float angle) const;

        /**
         * Rotates Y-basis vector for the matrix by given angle
         * @param angle rotation
         * @return identity matrix with rotated Y-basis vector
         */
        mat4 y_rotation(float angle) const;

        /**
         * Rotates Y-basis vector for the matrix by given angle
         * @param angle rotation
         * @return identity matrix with rotated Y-basis vector
         */
        mat3 y_rotation3x3(float angle) const;

        /**
         * Rotates X-basis vector for the matrix by given angle
         * @param angle rotation
         * @return identity matrix with rotated X-basis vector
         */
        mat4 x_rotation(float angle) const;

        /**
         * Rotates X-basis vector for the matrix by given angle
         * @param angle rotation
         * @return identity matrix with rotated X-basis vector
         */
        mat3 x_rotation3x3(float angle) const;

        /**
         * Rotates around given axis
         * @param axis
         * @param angle
         * @return rotated axis
         * @details https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
         *          https://en.wikipedia.org/wiki/Symmetric_matrix
         *          https://en.wikipedia.org/wiki/Skew-symmetric_matrix
         */
        mat4 axis_angle(const vec3& axis, float angle) const;

        /**
         * Rotates around given axis
         * @param axis
         * @param angle
         * @return rotates matrix
         * @details https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
         *          https://en.wikipedia.org/wiki/Symmetric_matrix
         *          https://en.wikipedia.org/wiki/Skew-symmetric_matrix
         */
        mat3 axis_angle3x3(const vec3& axis, float angle) const;

        /**
         * Pre multiplication (left to right) [vector * matrix]
         * @param vec
         * @param mat
         * @return multiplication result for each row stored in each axis of vector
         */
        vec3 multiply_vector(const vec3& vec, const mat3& mat) const;

        /**
         * Pre multiplication (left to right) [vector * matrix]
         * @param vec
         * @param mat
         * @return multiplication result for each row stored in each axis of vector
         */
        vec4 multiply_vector(const vec4& vec, const mat4& mat) const;

        /**
         * Creates World Transform Matrix (Scale-Rotate-Translate)
         * @param scale
         * @param euler_rot
         * @param translate
         * @return transformed matrix
         */
        mat4 transform(const vec3& scale, const vec3& euler_rot, const vec3& translate) const;

        /**
         * Creates World Transform Matrix (Scale-Rotate-Translate)
         * @param scale
         * @param euler_rot
         * @param translate
         * @return transformed matrix
         */
        mat4 transform(const vec3& scale, const vec3& rot_axis, float rot_angle, const vec3& translate) const;

        /**
         * Creates rotation basis
         * @param pos object's position
         * @param target position where the object is looking at
         * @param up world up
         * @return View Transform Matrix
         * @details http://www.songho.ca/opengl/gl_camera.html#lookat
         */
        mat4 look_at(const vec3& pos, const vec3& target, const vec3& up) const;

        /**
         * Creates Perspective projection matrix
         * @param fov field of view
         * @param aspect proportional relationship between view volume's width and height
         * @param z_near near clipping plane. All coordinates that are in front of the near plane will not be drawn
         * @param z_far far clipping plane. All coordinates behind far plane will not be drawn
         * @return projection matrix
         * @details https://www.codeguru.com/cpp/misc/misc/graphics/article.php/c10123/Deriving-Projection-Matrices.htm
         */
        mat4 perspective(float fov, float aspect, float z_near, float z_far) const;

        /**
         * Creates Orthographic projection matrix
         * @param left coordinate of the ortho frustum
         * @param right coordinate of the ortho frustum
         * @param bottom coordinate of the ortho frustum
         * @param top coordinate of the ortho frustum
         * @param z_near near clipping plane. All coordinates that are in front of the near plane will not be drawn
         * @param z_far far clipping plane. All coordinates behind far plane will not be drawn
         * @return projection matrix
         * @details https://www.codeguru.com/cpp/misc/misc/graphics/article.php/c10123/Deriving-Projection-Matrices.htm
         */
        mat4 ortho(float left, float right, float bottom, float top, float z_near, float z_far) const;
    };
}


#endif //INC_2D_GAME_TRANSFORM_H