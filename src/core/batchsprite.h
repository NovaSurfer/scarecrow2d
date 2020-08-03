//
// Created by novasurfer on 7/29/20.
//

#ifndef SCARECROW2D_BATCHSPRITE_H
#define SCARECROW2D_BATCHSPRITE_H

#include "renderable.h"
#include "rendering_types.h"
#include "shader.h"
#include "types.h"
#include "dbg/dbg_asserts.h"

namespace sc2d
{
    constexpr u32 MAX_QUADS = 1024;
    constexpr u32 MAX_VERTICES = MAX_QUADS * 4;
    constexpr u32 MAX_INDICES = MAX_QUADS * 6;

    struct VertexV2
    {
        math::vec2 pos;
//        math::vec2 uv;
        colorRGBA color;
    };

    struct VertexBuffer
    {
        void add(const math::vec2& pos, const math::vec2& size, const colorRGBA& color);
//        VertexV2 buffer[4] =
//        {
////             {position}, {color}
//            {{0.5f, 0.5f}, {1.0f, 0.0f,0.0f,1.0f}},
//            {{0.5f, -0.5f}, {1.0f, 0.0f,0.0f,1.0f}},
//            {{-0.5f, -0.5f}, {1.0f, 0.0f,0.0f,1.0f}},
//            {{-0.5f, 0.5f}, {1.0f, 0.0f,0.0f,1.0f}}
//        };
//        VertexV2* buffptr = buffer + 4;

//        VertexV2* buffer;
//        VertexV2* buffptr;
        VertexV2 buffer[MAX_VERTICES];
        size_t index = 0;
    };


    struct batchsprite
    {
        void init(const Shader& shader, const math::mat4& proj);
        void draw(const math::vec2& pos, const math::vec2& size, const colorRGBA& color);
        void flush();
        VertexBuffer vertxbuff;
        GLuint ebo = 0, vbo = 0, quadvao = 0;
        GLuint indices_count = 0;
        Shader shader;
    };
}

#endif //SCARECROW2D_BATCHSPRITE_H
