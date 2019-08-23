//
// Created by maksim.ruts on 3.4.19.
//
#include "doctest/doctest.h"
#include "../src/memory/pool_allocator.h"
#include "../src/collections/vec.h"


TEST_CASE("vector-operations") {
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

    SUBCASE("default constructor")
    {
        sc2d::vec<double> v;
        CHECK(v.capacity() == 2);
    }

    SUBCASE("constructor with size")
    {
        sc2d::vec<double> v(2);
        CHECK(v.capacity() == 4);
    }

    SUBCASE("constructor with size, filled with some value")
    {
        double value = 5.799;
        sc2d::vec<double> v(4, value);

        CHECK(v.capacity() == 8);
        CHECK(v[0] == 5.799);
        CHECK(v[1] == 5.799);
        CHECK(v[2] == 5.799);
        CHECK(v[3] == 5.799);
    }

    SUBCASE("constructor with first, last iterators")
    {
        double value = 5.799;
        sc2d::vec<double> v_1(4, value);

        sc2d::vec<double> v(v_1.begin(), v_1.end());
        CHECK(v.capacity() == 8);
        CHECK(v[0] == 5.799);
        CHECK(v[1] == 5.799);
        CHECK(v[2] == 5.799);
        CHECK(v[3] == 5.799);
    }

    SUBCASE("constructor with initialization list")
    {
        sc2d::vec<double> v({1.99, 2.99, 3.99, 4.99, 5.99});
        CHECK(v.capacity() == 10);
        CHECK(v[0] == 1.99);
        CHECK(v[1] == 2.99);
        CHECK(v[2] == 3.99);
        CHECK(v[3] == 4.99);
        CHECK(v[4] == 5.99);
    }

    SUBCASE("constructor with ref to other vector")
    {
        sc2d::vec<double> v({1.99, 2.99, 3.99, 4.99, 5.99});
        sc2d::vec<double> v2(v);
        CHECK(v2.capacity() == 10);
        CHECK(v2[0] == 1.99);
        CHECK(v2[1] == 2.99);
        CHECK(v2[2] == 3.99);
        CHECK(v2[3] == 4.99);
        CHECK(v2[4] == 5.99);
    }


    SUBCASE("constructor with lvalue ref to other vector")
    {
        sc2d::vec<double> v({1.99, 2.99, 3.99, 4.99, 5.99});
        sc2d::vec<double> v2(std::move(v));
        CHECK(v2.capacity() == 10);
        CHECK(v2[0] == 1.99);
        CHECK(v2[1] == 2.99);
        CHECK(v2[2] == 3.99);
        CHECK(v2[3] == 4.99);
        CHECK(v2[4] == 5.99);
    }

//    SUBCASE("copy assignment operator")
//    {
//        sc2d::vec<double> v({1.99, 2.99, 3.99, 4.99, 5.99});
//        sc2d::vec<double> v2(2, 5.0);
//        v2 = v;
//
//        CHECK(v2.capacity() == 10);
//        CHECK(v2[0] == 1.99);
//        CHECK(v2[1] == 2.99);
//        CHECK(v2[2] == 3.99);
//        CHECK(v2[3] == 4.99);
//        CHECK(v2[4] == 5.99);
//    }

//    SUBCASE("move assignment operator")
//    {
//        sc2d::vec<double> v({1.99, 2.99, 3.99, 4.99, 5.99});
//        sc2d::vec<double> v2(2, 5.0);
//        v2 = std::move(v);
//
//        CHECK(v2.capacity() == 10);
//        CHECK(v2[0] == 1.99);
//        CHECK(v2[1] == 2.99);
//        CHECK(v2[2] == 3.99);
//        CHECK(v2[3] == 4.99);
//        CHECK(v2[4] == 5.99);
//    }

//    SUBCASE("copy assignment initializer_list")
//    {
//        sc2d::vec<double> v(2, 5.0);
//        v = std::initializer_list<double> {1.99, 2.99, 3.99, 4.99, 5.99};
//
//        CHECK(v.capacity() == 10);
//        CHECK(v[0] == 1.99);
//        CHECK(v[1] == 2.99);
//        CHECK(v[2] == 3.99);
//        CHECK(v[3] == 4.99);
//        CHECK(v[4] == 5.99);
//    }
}

