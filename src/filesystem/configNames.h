//
// Created by Maksim Ruts on 04-Nov-18.
//

#ifndef INC_2D_GAME_CONFIGNAMES_H
#define INC_2D_GAME_CONFIGNAMES_H

#include <experimental/string_view>

struct configNames
{
    using string_view = std::experimental::string_view;

    static constexpr string_view RES_SPRITE {"sprites"};
    static constexpr string_view RES_SHARER {"shaders"};
};


#endif //INC_2D_GAME_CONFIGNAMES_H
