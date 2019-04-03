//
// Created by maksim.ruts on 3.4.19.
//
#include <type_traits>
#include "catch2/catch.hpp"
#include "../src/collections/vec.h"

TEST_CASE("vector-operations", "[collections]")
{
    struct trivial_type
    {
        int int_a = 9;
        char char_a = 'z';
        bool bool_a = false;
    };

    class non_trivial_type
    {
    public:
        non_trivial_type()
        {
            int_a = 8;
            char_a = 'm';
            bool_a = true;
        }

    private:
        int int_a;
        char char_a;
        bool bool_a;
    };

    trivial_type trivial_obj;
    non_trivial_type non_trivial_obj;

//    sc2d::vec<double> triv_objs;
//    sc2d::vec<non_trivial_type> non_triv_objs;
}

