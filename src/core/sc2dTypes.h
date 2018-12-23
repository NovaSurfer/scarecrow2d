//
// Created by novasurfer on 20.12.18.
//

#ifndef INC_2D_GAME_TYPES_H
#define INC_2D_GAME_TYPES_H

#include "math/vector.h"

namespace sc2d {

    constexpr int VERTICES_PER_QUAD = 4;
    constexpr int QUAD_INDICES[]
            {
                    0, 1, 3,    // First triangle
                    1, 2, 3     // Second triangle
            };

    struct Color {
        Color() = default;

        Color(float r, float g, float b, float a)
                :r{r}, g{g}, b{b}, a{b} { };
        float r, g, b, a;
    };

    struct Vertex {
        math::vec2 pos;
        math::vec2 uv;
        Color color;
    };

    struct Quad {
        // Top right
        Vertex tr;
        // Bottom right
        Vertex br;
        // Bottom left
        Vertex bl;
        // Top left
        Vertex tl;
    };
}

#endif //INC_2D_GAME_TYPES_H
