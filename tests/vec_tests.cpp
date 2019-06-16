//
// Created by maksim.ruts on 3.4.19.
//
#include "catch2/catch.hpp"
#include "../src/memory/pool_allocator.h"
#include "../src/collections/vec.h"


TEST_CASE("vector-operations", "[collections]") {
//    struct trivial_type {
//        int int_a = 9;
//        char char_a = 'z';
//        bool bool_a = false;
//    };
//
//    class non_trivial_type {
//    public:
//        non_trivial_type() {
//            int_a = 8;
//            char_a = 'm';
//            bool_a = true;
//        }
//
//    private:
//        int int_a;
//        char char_a;
//        bool bool_a;
//    };
//
//    trivial_type trivial_obj;
//    non_trivial_type non_trivial_obj;

    SECTION("default constructor")
    {
        sc2d::vec<double> v;
        REQUIRE(v.capacity() == 2);
    }

    SECTION("constructor with size")
    {
        sc2d::vec<double> v(2);
        REQUIRE(v.capacity() == 4);
    }

    SECTION("constructor with size, filled with some value")
    {
        double value = 5.799;
        sc2d::vec<double> v(4, value);

        REQUIRE(v.capacity() == 8);
        REQUIRE(v[0] == 5.799);
        REQUIRE(v[1] == 5.799);
        REQUIRE(v[2] == 5.799);
        REQUIRE(v[3] == 5.799);
    }

    SECTION("constructor with first, last iterators")
    {
        double value = 5.799;
        sc2d::vec<double> v_1(4, value);

        sc2d::vec<double> v(v_1.begin(), v_1.end());
        REQUIRE(v.capacity() == 8);
        REQUIRE(v[0] == 5.799);
        REQUIRE(v[1] == 5.799);
        REQUIRE(v[2] == 5.799);
        REQUIRE(v[3] == 5.799);
    }

    SECTION("constructor with initialization list")
    {
        sc2d::vec<double> v({1.99, 2.99, 3.99, 4.99, 5.99});
        REQUIRE(v.capacity() == 10);
        REQUIRE(v[0] == 1.99);
        REQUIRE(v[1] == 2.99);
        REQUIRE(v[2] == 3.99);
        REQUIRE(v[3] == 4.99);
        REQUIRE(v[4] == 5.99);
    }

    SECTION("constructor with ref to other vector")
    {

    }


    SECTION("constructor with lvalue to other vector")
    {

    }
}

