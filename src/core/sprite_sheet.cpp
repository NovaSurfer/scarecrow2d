//
// Created by novasurfer on 7/7/19.
//

#include "sprite_sheet.h"

namespace sc2d
{
    Vertex SpriteSheet::quad_vertices[VERTICES_PER_QUAD]{
        SPRITE_QUAD.tr,
        SPRITE_QUAD.br,
        SPRITE_QUAD.bl,
        SPRITE_QUAD.tl
    };

    SpriteSheet::SpriteSheet(const sc2d::Shader& shader)
    {
        this->shader = shader;
        init_data();
    }

    void SpriteSheet::init_data()
    {
        GLuint vbo;
        GLuint ebo;

        glGenVertexArrays(1, &quad_vao);

        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * VERTICES_PER_QUAD, quad_vertices,
                     GL_STATIC_DRAW);
        glBindVertexArray(quad_vao);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QUAD_INDICES), QUAD_INDICES, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)nullptr);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (GLvoid*)(sizeof(math::vec2)));
        glEnableVertexAttribArray(1);
    }
}