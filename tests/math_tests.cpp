//
// Created by maksim on 6/29/18.
//
#include "doctest/doctest.h"
#include "../src/math/matrix2.h"
#include "../src/math/matrix3.h"
#include "../src/math/matrix4.h"
#include "../src/math/vector2.h"

using namespace math;

TEST_CASE("mat2d-operations")
{
    mat2 matrix(1, 2, 3, 4);

    SUBCASE("is equal")
    {
        mat2 m(1, 2, 3, 4);
        CHECK(matrix == m);
    }

    SUBCASE("get value at position (i,j)")
    {
        CHECK(matrix(0, 0) == 1);
        CHECK(matrix(0, 1) == 2);
        CHECK(matrix(1, 0) == 3);
        CHECK(matrix(1, 1) == 4);

        SUBCASE("get values at position as const")
        {
            const mat2 const_matrix;
            CHECK(std::is_const<std::remove_reference<decltype(const_matrix(0, 0))>::type>::value);
        }
    }

    SUBCASE("get column values in vec2")
    {
        CHECK(typeid(matrix[0]) == typeid(vec2));

        SUBCASE("get column values as const")
        {
            const mat2 const_matrix;
            CHECK(std::is_const<std::remove_reference<decltype(const_matrix[0])>::type>::value);
        }
    }

    SUBCASE("scalar multiplication")
    {
        float scalar = 8;
        mat2 result = matrix * 8;

        CHECK(result == mat2(8, 16, 24, 32));

        SUBCASE("*= operator with scalar")
        {
            matrix *= 8;
            CHECK(matrix == mat2(8, 16, 24, 32));
        }
    }

    SUBCASE("matrix multiplication")
    {
        mat2 matrix2(1, 2, 3, 4);
        mat2 result = matrix * matrix2;
        CHECK(result == mat2(7, 10, 15, 22));

        SUBCASE("*= operator with matrix")
        {
            matrix *= matrix2;
            CHECK(matrix == mat2(7, 10, 15, 22));
        }
    }

    SUBCASE("matrix addition")
    {
        mat2 matrix2(1, 2, 3, 4);
        mat2 result = matrix + matrix2;
        CHECK(result == mat2(2, 4, 6, 8));

        SUBCASE("+= operator with matrix")
        {
            matrix += matrix2;
            CHECK(matrix == mat2(2, 4, 6, 8));
        }
    }

    SUBCASE("transpose")
    {
        CHECK(matrix.transpose() == mat2(1, 3, 2, 4));
    }

    SUBCASE("determinant")
    {
        CHECK(matrix.determinant() == -2);
    }

    SUBCASE("minor")
    {
        CHECK(matrix.minor() == mat2(4, 3, 2, 1));
    }

    SUBCASE("cofactor")
    {
        CHECK(matrix.cofactor() == mat2(4, -3, -2, 1));
    }

    SUBCASE("adjugate")
    {
        CHECK(matrix.adjugate() == mat2(4, -2, -3, 1));
    }

    SUBCASE("inverse")
    {
        CHECK(matrix * matrix.inverse() == mat2(1,0,0,1));
    }
}

// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------

TEST_CASE("mat3d-operations")
{
    mat3 matrix(1, 1, 1, 2, 2, 2, 3, 3, 3);
    mat3 matx3(1, 1, 1, 2, 5, 8, 9, 3, 3);
    
    SUBCASE("is equal")
    {
        mat3 m(1, 1, 1, 2, 2, 2, 3, 3, 3);
        CHECK(matrix == m);
    }

    SUBCASE("get value at position (i,j)")
    {
        CHECK(matrix(0, 0) == 1);
        CHECK(matrix(0, 1) == 1);
        CHECK(matrix(0, 2) == 1);

        CHECK(matrix(1, 0) == 2);
        CHECK(matrix(1, 1) == 2);
        CHECK(matrix(1, 2) == 2);

        CHECK(matrix(2, 0) == 3);
        CHECK(matrix(2, 1) == 3);
        CHECK(matrix(2, 2) == 3);


        SUBCASE("get values at position as const")
        {
            const mat3 const_matrix;
            CHECK(std::is_const<std::remove_reference<decltype(const_matrix(0, 0))>::type>::value);
        }
    }

    SUBCASE("get column values in vec3")
    {
        CHECK(typeid(matrix[0]) == typeid(vec3));

        SUBCASE("get column values as const")
        {
            const mat3 const_matrix;
            CHECK(std::is_const<std::remove_reference<decltype(const_matrix[0])>::type>::value);
        }
    }

    SUBCASE("scalar multiplication")
    {
        float scalar = 8;
        mat3 result = matrix * 8;

        CHECK(result == mat3(8, 8, 8, 16, 16, 16, 24, 24, 24));

        SUBCASE("*= operator with scalar")
        {
            matrix *= 8;
            CHECK(matrix == mat3(8, 8, 8, 16, 16, 16, 24, 24, 24));
        }
    }

    SUBCASE("matrix multiplication")
    {
        mat3 matrix2(1, 1, 1, 2, 2, 2, 3, 3, 3);
        mat3 result = matrix * matrix2;
        CHECK(result == mat3(6, 6, 6, 12, 12, 12, 18, 18, 18));

        SUBCASE("*= operator with matrix")
        {
            matrix *= matrix2;
            CHECK(matrix == mat3(6, 6, 6, 12, 12, 12, 18, 18, 18));
        }
    }

    SUBCASE("matrix addition")
    {
        mat3 matrix2(1, 1, 1, 2, 2, 2, 3, 3, 3);
        mat3 result = matrix + matrix2;
        CHECK(result == mat3(2, 2, 2, 4, 4, 4, 6, 6, 6));

        SUBCASE("+= operator with matrix")
        {
            matrix += matrix2;
            CHECK(matrix == mat3(2, 2, 2, 4, 4, 4, 6, 6, 6));
        }
    }

    SUBCASE("transpose")
    {
        CHECK(matrix.transpose() == mat3(1, 2, 3, 1, 2, 3, 1, 2, 3));
    }

    SUBCASE("determinant")
    {
        CHECK(matx3.determinant() == 18);
    }

    SUBCASE("minor")
    {
        CHECK(matx3.minor() == mat3(-9, -66, -39, 0, -6, -6, 3, 6, 3));
    }

    SUBCASE("cofactor")
    {
        CHECK(matx3.cofactor() == mat3(-9, 66, -39, -0, -6, 6, 3, -6, 3));
    }

    SUBCASE("adjugate")
    {
        CHECK(matx3.adjugate() == mat3(-9, 0, 3, 66, -6, -6, -39, 6, 3));
    }
    // TODO:
    // SUBCASE("inverse")
    // {
    //     mat3 matrix2(1, 1, 1, 2, 5, 8, 9, 3, 3);
    //     std::cout << matrix2.inverse();
    //     CHECK(matrix2 * matrix2.inverse() == mat3(1, 0, 0, 0, 1, 0, 0, 0, 1));
    // }
}

// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------

TEST_CASE("mat4d-operations")
{
    mat4 matrix(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 5, 8, 9, 4, 4, 4);
    mat4 matx3(1, 1, 2, 1, 2, 4, 2, 2, 2, 5, 5, 8, 9, 4, 4, 4);

    SUBCASE("is equal")
    {
        mat4 m(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 5, 8, 9, 4, 4, 4);
        CHECK(matrix == m);
    }

    SUBCASE("get value at position (i,j)")
    {
        CHECK(matrix(0, 0) == 1);
        CHECK(matrix(0, 1) == 1);
        CHECK(matrix(0, 2) == 1);
        CHECK(matrix(0, 3) == 1);

        CHECK(matrix(1, 0) == 2);
        CHECK(matrix(1, 1) == 2);
        CHECK(matrix(1, 2) == 2);
        CHECK(matrix(1, 3) == 2);

        CHECK(matrix(2, 0) == 3);
        CHECK(matrix(2, 1) == 3);
        CHECK(matrix(2, 2) == 5);
        CHECK(matrix(2, 3) == 8);

        CHECK(matrix(3, 0) == 9);
        CHECK(matrix(3, 1) == 4);
        CHECK(matrix(3, 2) == 4);
        CHECK(matrix(3, 3) == 4);

        SUBCASE("get values at position as const")
        {
            const mat4 const_matrix;
            CHECK(std::is_const<std::remove_reference<decltype(const_matrix(0, 0))>::type>::value);
        }
    }

    SUBCASE("get column values in vec4")
    {
        CHECK(typeid(matrix[0]) == typeid(vec4));

        SUBCASE("get column values as const")
        {
            const mat4 const_matrix;
            CHECK(std::is_const<std::remove_reference<decltype(const_matrix[0])>::type>::value);
        }
    }

    SUBCASE("scalar multiplication")
    {
        float scalar = 8;
        mat4 result = matrix * 8;

        CHECK(result == mat4(8,8,8,8,16,16,16,16,24,24,40,64,72,32,32,32));

        SUBCASE("*= operator with scalar")
        {
            matrix *= 8;
            CHECK(matrix == mat4(8,8,8,8,16,16,16,16,24,24,40,64,72,32,32,32));
        }
    }

    SUBCASE("matrix multiplication")
    {
        mat4 matrix2(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4);
        mat4 result = matrix * matrix2;
        CHECK(result == mat4(10,10,10,10,20,20,20,20,56,56,56,56,45,45,45,45));

        SUBCASE("*= operator with matrix")
        {
            matrix *= matrix2;
            CHECK(matrix == mat4(10,10,10,10,20,20,20,20,56,56,56,56,45,45,45,45));
        }
    }

    SUBCASE("matrix addition")
    {
        mat4 matrix2(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4);
        mat4 result = matrix + matrix2;
        CHECK(result == mat4(2, 2, 2, 2, 4, 4, 4, 4, 6, 6, 8, 11, 13, 8, 8, 8));

        SUBCASE("+= operator with matrix")
        {
            matrix += matrix2;
            CHECK(matrix == mat4(2, 2, 2, 2, 4, 4, 4, 4, 6, 6, 8, 11, 13, 8, 8, 8));
        }
    }

    SUBCASE("transpose")
    {
        CHECK(matrix.transpose() == mat4(1, 2, 3, 9, 1, 2, 3, 4, 1, 2, 5, 4, 1, 2, 8, 4));
    }
    
    SUBCASE("determinant")
    {
        CHECK(matx3.determinant() == 188);
    }

    SUBCASE("minor")
    {
        CHECK(matx3.minor() == mat4(-24, 30, 158, 74, 12, 79, 15, -37, -8, 10, -10, -38, -28, -12, 12, 8));
    }

    SUBCASE("cofactor")
    {
        CHECK(matx3.cofactor() == mat4(-24, -30, 158, -74, -12, 79, -15, -37, -8, -10, -10, 38, 28, -12, -12, 8));
    }

    SUBCASE("adjugate")
    {
        CHECK(matx3.adjugate() == mat4(-24, -12, -8, 28, -30, 79, -10, -12, 158, -15, -10, -12, -74, -37, 38, 8));
    }

//     SUBCASE("inverse")
//     {
//         CHECK(matx3 * matx3.inverse() == mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
//     }
}


TEST_CASE("vec2d-operations")
{
    vec2 vector(1, 2);

    SUBCASE("is equal")
    {
        vec2 v(1, 2);
        CHECK(vector == v);
    }

    SUBCASE("get element as array")
    {
        CHECK(vector[0] == 1);
        CHECK(vector[1] == 2);

        SUBCASE("get element as const")
        {
            const vec2 const_v;
            CHECK(std::is_const<std::remove_reference<decltype(const_v[0])>::type>::value);
        }
    }

    SUBCASE("scalar multiplication")
    {
        float scalar = 8;
        vec2 result = vector * 8;

        CHECK(result == vec2(8, 16));

        SUBCASE("*= operator with scalar")
        {
            vector *= 8;
            CHECK(vector == vec2(8, 16));
        }
    }

    SUBCASE("scalar division")
    {
        float scalar = 2;
        vec2 result = vector / 2;

        CHECK(result == vec2(0.5f, 1.0f));

        SUBCASE("/= operator with scalar")
        {
            vector /= 2;
            CHECK(vector == vec2(0.5f, 1.0f));
        }
    }

    SUBCASE("vector addition")
    {
        vec2 v(1, 2);
        vec2 result = vector + v;

        CHECK(result == vec2(2, 4));

        SUBCASE("+= operator")
        {
            vector += v;
            CHECK(vector == vec2(2, 4));
        }
    }

    SUBCASE("vector subtraction")
    {
        vec2 v(1, 2);
        vec2 result = vector - v;

        CHECK(result == vec2());

        SUBCASE("-= operator")
        {
            vector -= v;
            CHECK(vector == vec2());
        }
    }

    SUBCASE("dot product")
    {
        vec2 v(2, 4);
        float result = dot(vector, v);
        CHECK(result == 10.0f);
    }

    SUBCASE("magnitude")
    {
        float result = magnitude(vector);
        CHECK(result == doctest::Approx(2.236067f));
    }

    SUBCASE("squire magnitude")
    {
        CHECK(magnitudeSq(vector) == 5.0f);
    }

    SUBCASE("distance")
    {
        CHECK(distance(vec2(4, 6), vector) == 5.0f);
    }

    SUBCASE("normalize")
    {
        //  FAILED:
        //  CHECK( magnitude(normalize(vector)) == 1.0f )
        //  with expansion:
        //  1.0f == 1.0f
        CHECK(magnitude(normalize(vector)) == doctest::Approx(1.0f));
    }

    SUBCASE("get angle")
    {
        CHECK(angle(vector, vector) == 0.0f);
    }

    SUBCASE("projection")
    {
        vec2 v(3, 6);
        CHECK(project(vector, v) == vec2(1, 2));
    }

    SUBCASE("perpendicular")
    {
        vec2 v(3, 6);
        CHECK(perpendicular(vector, v) == vec2());
    }

    SUBCASE("reflection")
    {
        CHECK(reflection(vector, normalize(vector)) == vec2(-1,-2));
    }
}