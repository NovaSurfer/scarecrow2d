//
// Created by maksim.ruts on 3.4.19.
//
#include "../src/collections/vec.h"
#include "../src/memory/pool_allocator.h"
#include "doctest/doctest.h"
#include <vector>

TEST_CASE("vector-operations")
{
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
        CHECK(v.capacity() == 4);
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

    SUBCASE("copy assignment operator")
    {
        sc2d::vec<double> v({1.99, 2.99, 3.99, 4.99, 5.99});
        sc2d::vec<double> v2(2, 5.0);
        v2 = v;

        CHECK(v2.capacity() == 10);
        CHECK(v2[0] == 1.99);
        CHECK(v2[1] == 2.99);
        CHECK(v2[2] == 3.99);
        CHECK(v2[3] == 4.99);
        CHECK(v2[4] == 5.99);
    }

    SUBCASE("move assignment operator")
    {
        sc2d::vec<double> v({1.99, 2.99, 3.99, 4.99, 5.99});
        sc2d::vec<double> v2(2, 5.0);
        v2 = std::move(v);

        CHECK(v2.capacity() == 10);
        CHECK(v2[0] == 1.99);
        CHECK(v2[1] == 2.99);
        CHECK(v2[2] == 3.99);
        CHECK(v2[3] == 4.99);
        CHECK(v2[4] == 5.99);
    }

    SUBCASE("copy assignment initializer_list")
    {
        sc2d::vec<double> v(2, 5.0);
        v = std::initializer_list<double> {1.99, 2.99, 3.99, 4.99, 5.99};

        CHECK(v.capacity() == 10);
        CHECK(v[0] == 1.99);
        CHECK(v[1] == 2.99);
        CHECK(v[2] == 3.99);
        CHECK(v[3] == 4.99);
        CHECK(v[4] == 5.99);
    }

    SUBCASE("assign(size, data)")
    {
        sc2d::vec<double> v;
        v.assign(4, 10.5);
        CHECK(v.capacity() == 4);
        CHECK(v[0] == 10.5);
        CHECK(v[1] == 10.5);
        CHECK(v[2] == 10.5);
        CHECK(v[3] == 10.5);
    }

    SUBCASE("[c]begin() | [c]end() | [c]rbegin() | [c]rend() iterators")
    {
        sc2d::vec<double> v({1.1, 2.1});
        CHECK(*v.begin() == 1.1);
        CHECK(*(v.end() - 1) == 2.1);

        CHECK(*v.cbegin() == 1.1);
        CHECK(*(v.cend() - 1) == 2.1);

        CHECK(*v.rbegin() == 2.1);
        CHECK(*(v.rend() - 1) == 1.1);

        CHECK(*v.crbegin() == 2.1);
        CHECK(*(v.crend() - 1) == 1.1);
    }

    SUBCASE("assign(inter_first, iter_last)")
    {
        sc2d::vec<double> v;
        sc2d::vec<double> v2({1.99, 2.99, 3.99, 4.99, 5.99});
        v.assign(v2.begin() + 1, v2.end() - 1);
        CHECK(v.capacity() == 4);
        CHECK(v[0] == 2.99);
        CHECK(v[1] == 3.99);
        CHECK(v[2] == 4.99);
    }

    SUBCASE("assign(initializer_list)")
    {
        sc2d::vec<double> v;
        v.assign(std::initializer_list<double> {2.99, 3.99, 4.99});
        CHECK(v.capacity() == 4);
        CHECK(v[0] == 2.99);
        CHECK(v[1] == 3.99);
        CHECK(v[2] == 4.99);
    }

    SUBCASE("size()")
    {
        sc2d::vec<double> v({1.1});
        v.push_back(2.2);
        v.push_back(3.3);
        CHECK(v.size() == 3);
        CHECK(v.capacity() == 4);
    }

    SUBCASE("resize()")
    {
        sc2d::vec<double> v({1.1});
        v.push_back(2.2);
        v.push_back(3.3);
        CHECK(v.size() == 3);

        // Increasing size
        v.resize(5);

        CHECK(v.size() == 5);
        CHECK(v[0] == 1.1);
        CHECK(v[1] == 2.2);
        CHECK(v[2] == 3.3);

        v.push_back(4.4);
        v.push_back(5.5);
        v.push_back(6.6);

        CHECK(v.size() == 8);

        // Decreasing size
        v.resize(2);
        CHECK(v[0] == 1.1);
        CHECK(v[1] == 2.2);
    }

    SUBCASE("reserve()")
    {
        sc2d::vec<double> v({1.1});
        v.reserve(5);
        CHECK(v.size() == 1);
        CHECK(v.capacity() == 5);
    }

    SUBCASE("shrink_to_fit()")
    {
        sc2d::vec<double> v({1.1});
        v.push_back(2.2);
        v.push_back(3.3);
        CHECK(v.size() == 3);
        CHECK(v.capacity() == 4);
        v.shrink_to_fit();

        CHECK(v.size() == 3);
        CHECK(v.capacity() == 3);
    }

    SUBCASE("at()")
    {
        sc2d::vec<double> v({1.1, 2.2, 3.3});
        CHECK(v.at(1) == 2.2);
    }

    SUBCASE("front() & back()")
    {
        sc2d::vec<double> v({1.1, 2.2, 3.3});
        CHECK(v.front() == 1.1);
        CHECK(v.back() == 3.3);
    }

    SUBCASE("data()")
    {
        sc2d::vec<double> v({1.1, 2.2, 3.3});
        CHECK(v[0] == *v.data());
    }

    SUBCASE("emplace_back()")
    {
        sc2d::vec<double> v;
        v.emplace_back(1.1);
        v.emplace_back(2.1);
        v.emplace_back(3.1);

        CHECK(v[0] == 1.1);
        CHECK(v[1] == 2.1);
        CHECK(v[2] == 3.1);
    }

    SUBCASE("pop_back()")
    {
        sc2d::vec<double> v({1.1, 2.2, 3.3, 4.4});
        v.pop_back();
        CHECK(v.back() == v[2]);
    }

    SUBCASE("emplace()")
    {
        sc2d::vec<double> v({1.1, 2.2, 3.3});
        v.emplace(v.cbegin(), 5.5);
        v.emplace(v.end(), 7.7);

        CHECK(v.size() == 5);
        CHECK(v.capacity() == 6);
        CHECK(v[0] == 5.5);
        CHECK(v[1] == 1.1);
        CHECK(v[2] == 2.2);
        CHECK(v[3] == 3.3);
        CHECK(v[4] == 7.7);
    }

    SUBCASE("insert()")
    {
        sc2d::vec<double> v({1.1, 2.2, 3.3});
        v.insert(v.cbegin(), 5.5);
        v.insert(v.end(), 7.7);

        CHECK(v.size() == 5);
        CHECK(v.capacity() == 6);
        CHECK(v[0] == 5.5);
        CHECK(v[1] == 1.1);
        CHECK(v[2] == 2.2);
        CHECK(v[3] == 3.3);
        CHECK(v[4] == 7.7);
    }

    SUBCASE("insert(T&&)")
    {
        sc2d::vec<double> v({1.1, 2.2, 3.3});
        //trivially-copyable type, no effect
        v.insert(v.cbegin(), std::move(5.5));
        v.insert(v.end(), std::move(7.7));

        CHECK(v.size() == 5);
        CHECK(v.capacity() == 6);
        CHECK(v[0] == 5.5);
        CHECK(v[1] == 1.1);
        CHECK(v[2] == 2.2);
        CHECK(v[3] == 3.3);
        CHECK(v[4] == 7.7);
    }

    SUBCASE("insert(first, last iterators)")
    {
        sc2d::vec<double> v({1.1, 2.2, 3.3});
        v.insert(v.cbegin(), v.begin(), v.begin() + 2);
        v.insert(v.end(), v.end() - 2, v.end());

        CHECK(v.size() == 7);
        CHECK(v.capacity() == 16);
        CHECK(v[0] == 1.1);
        CHECK(v[1] == 2.2);
        CHECK(v[2] == 1.1);
        CHECK(v[3] == 2.2);
        CHECK(v[4] == 3.3);
        CHECK(v[5] == 2.2);
        CHECK(v[6] == 3.3);
    }

    SUBCASE("insert(std::initializer_list<T>)")
    {
        sc2d::vec<double> v({1.1, 2.2, 3.3});
        v.insert(v.cbegin(), {5.5, 5.5});
        v.insert(v.end(), {7.7, 7.7});

        CHECK(v.size() == 7);
        CHECK(v.capacity() == 16);
        CHECK(v[0] == 5.5);
        CHECK(v[1] == 5.5);
        CHECK(v[2] == 1.1);
        CHECK(v[3] == 2.2);
        CHECK(v[4] == 3.3);
        CHECK(v[5] == 7.7);
        CHECK(v[6] == 7.7);
    }
}
