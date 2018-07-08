//
// Created by maksim on 6/29/18.
//
#include <iostream>
#include "catch2/catch.hpp"
#include "../src/math/matrices.h"
#include "../src/math/vector.h"

using namespace math;

TEST_CASE("mat2d-operations", "[math]")
{
    mat2 matrix(1, 2, 3, 4);

    SECTION("is equal")
    {
        mat2 m(1, 2, 3, 4);
        REQUIRE(matrix == m);
    }

    SECTION("get value at position (i,j)")
    {
        REQUIRE(matrix(0, 0) == 1);
        REQUIRE(matrix(0, 1) == 2);
        REQUIRE(matrix(1, 0) == 3);
        REQUIRE(matrix(1, 1) == 4);

        SECTION("get values at position as const")
        {
            const mat2 const_matrix;
            REQUIRE(std::is_const<std::remove_reference<decltype(const_matrix(0, 0))>::type>::value);
        }
    }

    SECTION("get column values in vec2")
    {
        REQUIRE(typeid(matrix[0]) == typeid(vec2));

        SECTION("get column values as const")
        {
            const mat2 const_matrix;
            REQUIRE(std::is_const<std::remove_reference<decltype(const_matrix[0])>::type>::value);
        }

    }

    SECTION("scalar multiplication")
    {
        float scalar = 8;
        mat2 result = matrix * 8;

        REQUIRE(result == mat2(8, 16, 24, 32));

        SECTION("*= operator with scalar")
        {
            matrix *= 8;
            REQUIRE(matrix == mat2(8, 16, 24, 32));
        }
    }

    SECTION("matrix multiplication")
    {
        mat2 matrix2(1, 2, 3, 4);
        mat2 result = matrix * matrix2;
        REQUIRE(result == mat2(7, 10, 15, 22));

        SECTION("*= operator with matrix")
        {
            matrix *= matrix2;
            REQUIRE(matrix == mat2(7, 10, 15, 22));
        }
    }

    SECTION("transpose")
    {
        REQUIRE(matrix.transpose() == mat2(1, 3, 2, 4));
    }

    SECTION("determinant")
    {
        REQUIRE(matrix.determinant() == -2);
    }

    SECTION("minor")
    {
        REQUIRE(matrix.minor() == mat2(4, 3, 2, 1));
    }

    SECTION("cofactor")
    {
        REQUIRE(matrix.cofactor() == mat2(4, -3, -2, 1));
    }

    SECTION("adjugate")
    {
        REQUIRE(matrix.adjugate() == mat2(4, -2, -3, 1));
    }

    SECTION("inverse")
    {
        REQUIRE(matrix * matrix.inverse() == mat2(1,0,0,1));
    }
}

TEST_CASE("vec2d-operations", "[math]")
{
    vec2 vector(1, 2);

    SECTION("is equal")
    {
        vec2 v(1, 2);
        REQUIRE(vector == v);
    }

    SECTION("get element as array")
    {
        REQUIRE(vector[0] == 1);
        REQUIRE(vector[1] == 2);

        SECTION("get element as const")
        {
            const vec2 const_v;
            REQUIRE(std::is_const<std::remove_reference<decltype(const_v[0])>::type>::value);
        }
    }

    SECTION("scalar multiplication")
    {
        float scalar = 8;
        vec2 result = vector * 8;

        REQUIRE(result == vec2(8, 16));

        SECTION("*= operator with scalar")
        {
            vector *= 8;
            REQUIRE(vector == vec2(8, 16));
        }
    }

    SECTION("scalar division")
    {
        float scalar = 2;
        vec2 result = vector / 2;

        REQUIRE(result == vec2(0.5f, 1.0f));

        SECTION("/= operator with scalar")
        {
            vector /= 2;
            REQUIRE(vector == vec2(0.5f, 1.0f));
        }
    }

    SECTION("vector addition")
    {
        vec2 v(1, 2);
        vec2 result = vector + v;

        REQUIRE(result == vec2(2, 4));

        SECTION("+= operator")
        {
            vector += v;
            REQUIRE(vector == vec2(2, 4));
        }
    }

    SECTION("vector subtraction")
    {
        vec2 v(1, 2);
        vec2 result = vector - v;

        REQUIRE(result == vec2());

        SECTION("-= operator")
        {
            vector -= v;
            REQUIRE(vector == vec2());
        }
    }

    SECTION("dot product")
    {
        vec2 v(2, 4);
        float result = dot(vector, v);
        REQUIRE(result == 10.0f);
    };

    SECTION("magnitude")
    {
        float result = magnitude(vector);
        REQUIRE(result == Approx(2.236067f));
    }

    SECTION("squire magnitude")
    {
        REQUIRE(magnitudeSq(vector) == 5.0f);
    }

    SECTION("distance")
    {
        REQUIRE(distance(vec2(4, 6), vector) == 5.0f);
    }

    SECTION("normalize")
    {
        //  FAILED:
        //  REQUIRE( magnitude(normalize(vector)) == 1.0f )
        //  with expansion:
        //  1.0f == 1.0f
        REQUIRE(magnitude(normalize(vector)) == Approx(1.0f));
    }

    SECTION("get angle")
    {
        REQUIRE(angle(vector, vector) == 0.0f);
    }

    SECTION("projection")
    {
        vec2 v(3, 6);
        REQUIRE(project(vector, v) == vec2(1, 2));
    }

    SECTION("perpendicular")
    {
        vec2 v(3, 6);
        REQUIRE(perpendicular(vector, v) == vec2());
    }

    SECTION("reflection")
    {
        REQUIRE(reflection(vector, normalize(vector)) == vec2(-1,-2));
    }
}