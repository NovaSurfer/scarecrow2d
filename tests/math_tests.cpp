//
// Created by maksim on 6/29/18.
//
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

    // TODO: transpose, determinant, minor, cofactor, adjugate
}