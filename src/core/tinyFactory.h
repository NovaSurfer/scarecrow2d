//
// Created by Maksim Ruts on 06-Dec-18.
//

#ifndef INC_2D_GAME_TINY_FACTORY_H
#define INC_2D_GAME_TINY_FACTORY_H

template <typename R, typename... Args>
using Factory = R(*)(Args...);

#endif //INC_2D_GAME_TINY_FACTORY_H
