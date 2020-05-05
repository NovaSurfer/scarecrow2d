//
// Created by novasurfer on 20.12.18.
//

#ifndef INC_2D_GAME_TYPES_H
#define INC_2D_GAME_TYPES_H

#include "math/vector2.h"

namespace sc2d
{

    constexpr float DEFAULT_Z_NEAR = -1.0f;
    constexpr float DEFAULT_Z_FAR = 1.0f;
    constexpr int VERTICES_PER_QUAD = 4;
    constexpr int QUAD_INDICES[] {
        0, 1, 3, // First triangle
        1, 2, 3 // Second triangle
    };

    struct Color
    {
        Color() = default;

        Color(float r, float g, float b, float a)
            : r {r}
            , g {g}
            , b {b}
            , a {b} {};
        float r, g, b, a;
    };

    struct Vertex
    {
        math::vec2 pos;
        math::vec2 uv;
        //        Color color;
    };

    struct Quad
    {
        // Top right
        Vertex tr;
        // Bottom right
        Vertex br;
        // Bottom left
        Vertex bl;
        // Top left
        Vertex tl;
    };

    constexpr Quad SPRITE_QUAD {
        //positions      //tex coords  //colors (RGBA)
        {{0.5f, 0.5f}, {1.0f, 1.0f}, /*{1.0f, 0.0f, 0.0f, 1.0}*/}, // top right
        {{0.5f, -0.5f}, {1.0f, 0.0f}, /*{0.0f, 1.0f, 0.0f, 1.0}*/}, // bottom right
        {{-0.5f, -0.5f}, {0.0f, 0.0f}, /*{0.0f, 0.0f, 1.0f, 1.0}*/}, // bottom left
        {{-0.5f, 0.5f}, {0.0f, 1.0f}, /*{1.0f, 1.0f, 0.0f, 1.0}*/}, // top left
    };

    constexpr Vertex QUAD_VERTICES[VERTICES_PER_QUAD] {
        SPRITE_QUAD.tr,
        SPRITE_QUAD.br,
        SPRITE_QUAD.bl,
        SPRITE_QUAD.tl,
    };
}

#endif //INC_2D_GAME_TYPES_H
