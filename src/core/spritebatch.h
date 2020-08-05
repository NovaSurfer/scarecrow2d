//
// Created by novasurfer on 7/29/20.
//

#ifndef SCARECROW2D_SPRITEBATCH_H
#define SCARECROW2D_SPRITEBATCH_H

#include "renderable.h"
#include "dbg/dbg_asserts.h"

namespace sc2d
{

    class SpriteBatch
    {
    public:
        void init(const Shader& shader, const math::mat4& proj);
        void draw(const math::vec2& pos, const math::vec2& size, const colorRGBA& color);
        void flush();
    private:
        QuadBuffer quadbuff;
        GLuint vbo, quadvao;
        GLuint indices_count;
        GLuint texid;
        Shader shader;
    };
}

#endif //SCARECROW2D_SPRITEBATCH_H
