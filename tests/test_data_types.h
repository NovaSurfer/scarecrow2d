//
// Created by novasurfer on 4/20/20.
//

#ifndef SCARECROW2D_TEST_DATA_TYPES_H
#define SCARECROW2D_TEST_DATA_TYPES_H


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

#endif //SCARECROW2D_TEST_DATA_TYPES_H
