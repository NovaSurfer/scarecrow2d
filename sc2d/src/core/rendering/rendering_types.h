//
// Created by novasurfer on 20.12.18.
//

#ifndef INC_2D_GAME_TYPES_H
#define INC_2D_GAME_TYPES_H

#include "core/limits.h"
#include "math/vector2.h"
#include "math/vector3.h"
#include "math/vector4.h"

namespace sc2d
{
    using size2d = math::vec2;
    using colorRGB = math::vec3;
    using colorRGBA = math::vec4;

    constexpr float DEFAULT_Z_NEAR = -1.0f;
    constexpr float DEFAULT_Z_FAR = 1.0f;
    constexpr u32 VERTICES_PER_QUAD = 4;
    constexpr u32 QUAD_INDICES[] {
        0, 1, 3, // First triangle
        1, 2, 3 // Second triangle
    };

    namespace Color
    {
        constexpr math::vec3 WHITE {1.0f, 1.0f, 1.0f};
        constexpr math::vec3 MAGENTA {1.0f, 0.0f, 1.0f};
        constexpr math::vec3 CYAN {0.0f, 1.0f, 1.0f};
    }

    struct Vertex
    {
        math::vec2 pos;
        math::vec2 uv;
    };

    struct VertexColored
    {
        math::vec2 pos;
        math::vec2 uv;
        colorRGBA color;
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

    struct QuadColored
    {
        // Top right
        VertexColored tr;
        // Bottom right
        VertexColored br;
        // Bottom left
        VertexColored bl;
        // Top left
        VertexColored tl;
    };


    class SpriteBatch;

    class QuadBuffer
    {
        friend SpriteBatch;
    public:
        void add(const math::vec2& pos, const math::vec2& size, const colorRGBA& color);
        QuadColored data[limits::DRAWCALL_QUADS];
    private:
        size_t index;
    };

    constexpr Quad SPRITE_QUAD {
        //positions    //tex coords
        {{0.5f, 0.5f}, {1.0f, 1.0f}}, // top right
        {{0.5f, -0.5f}, {1.0f, 0.0f}}, // bottom right
        {{-0.5f, -0.5f}, {0.0f, 0.0f}}, // bottom left
        {{-0.5f, 0.5f}, {0.0f, 1.0f}}, // top left
    };

    constexpr Vertex QUAD_VERTICES[VERTICES_PER_QUAD] {
        SPRITE_QUAD.tr,
        SPRITE_QUAD.br,
        SPRITE_QUAD.bl,
        SPRITE_QUAD.tl,
    };
}

#endif //INC_2D_GAME_TYPES_H
