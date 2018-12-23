//
// Created by novasurfer on 20.12.18.
//

#include "sprite.h"

namespace sc2d {

    Vertex Sprite::quad_vertices[VERTICES_PER_QUAD]{
            SpriteTypes::SPRITE_QUAD.tr,
            SpriteTypes::SPRITE_QUAD.br,
            SpriteTypes::SPRITE_QUAD.bl,
            SpriteTypes::SPRITE_QUAD.tl};

    Sprite::Sprite(const Shader& shader)
    {

    }

    void Sprite::draw_sprite(const Texture2d& tex2d, math::vec2 pos, math::size2d size, float rotate)
    {

    }

    void Sprite::init_data()
    {
        GLuint vbo;
        GLuint ebo;

        glGenVertexArrays(1, &quad_vao);

        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * VERTICES_PER_QUAD, quad_vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QUAD_INDICES), QUAD_INDICES, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) nullptr);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vertex)));
        glEnableVertexAttribArray(1);
        // color attribute
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vertex) * 2));
        glEnableVertexAttribArray(2);
    }
}
