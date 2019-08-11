//
// Created by novasurfer on 7/7/19.
//

#include "sprite_sheet.h"
#include "math/transform.h"
#include "texture_atlas.h"

namespace sc2d
{
    Vertex SpriteSheet::quad_vertices[VERTICES_PER_QUAD] {SPRITE_QUAD.tr, SPRITE_QUAD.br,
                                                          SPRITE_QUAD.bl, SPRITE_QUAD.tl};

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

    void SpriteSheet::draw(const sc2d::TextureAtlas& texatlas, const math::vec2& pos,
                           const math::size2d& size, const float rotate)
    {
        shader.run();
        math::mat4 model =
            math::transform(math::vec3(size.width, size.height, 1.0f), math::vec3(0.0f, 0.0f, 1.0f),
                            rotate, math::vec3(0.5f * size.width, 0.5f * size.height, 0.0f));

        shader.set_mat4("model", model);
        shader.set_vec3("spriteColor", math::vec3(1.0f, 1.0f, 1.0f));

        glActiveTexture(GL_TEXTURE0);
        texatlas.bind();

        glBindVertexArray(quad_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }
}