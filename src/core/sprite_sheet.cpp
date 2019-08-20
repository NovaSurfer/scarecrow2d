//
// Created by novasurfer on 7/7/19.
//

#include "sprite_sheet.h"
#include "core/debug_utils.h"
#include "math/transform.h"
#include "texture_atlas.h"

namespace sc2d
{
    Vertex SpriteSheet::quad_vertices[VERTICES_PER_QUAD] {SPRITE_QUAD.tr, SPRITE_QUAD.br,
                                                          SPRITE_QUAD.bl, SPRITE_QUAD.tl};

    SpriteSheet::SpriteSheet(const sc2d::Shader& shader, const math::size2d& size,
                             std::vector<math::vec2>&& pos, std::vector<uint32_t>&& gid)
        : shader {shader}
        , size {size}
        , positions {pos}
        , gids {gid}
    {
        init_data();
    }

    void SpriteSheet::init_data()
    {
        GLuint vbo;
        GLuint model_vbo;
        GLuint gid_vbo;
        GLuint ebo;

        glGenVertexArrays(1, &quad_vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &model_vbo);
        glGenBuffers(1, &gid_vbo);
        glGenBuffers(1, &ebo);
        glBindVertexArray(quad_vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * VERTICES_PER_QUAD, quad_vertices,
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QUAD_INDICES), QUAD_INDICES, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)nullptr);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (GLvoid*)(sizeof(math::vec2)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // instance 'model' attribute, which is located in another buffer
        math::mat4 model_matrices[positions.size()];
        for(size_t i = 0; i < positions.size(); ++i) {
            model_matrices[i] = math::transform(
                math::vec3(size.width, size.height, 1.0f), math::vec3(0.0f, 0.0f, 1.0f), 0,
                math::vec3(0.5f * size.width + positions[i].x, 0.5f * size.height + positions[i].y,
                           0.0f));
        }
        glBindBuffer(GL_ARRAY_BUFFER, model_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(math::mat4) * positions.size(), &model_matrices[0],
                     GL_STATIC_DRAW);

        size_t matrow_size = sizeof(float) * 4;
        for(size_t i = 0; i < positions.size(); ++i) {
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * matrow_size, (GLvoid*)nullptr);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * matrow_size,
                                  (GLvoid*)(matrow_size));
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * matrow_size,
                                  (GLvoid*)(2 * matrow_size));
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * matrow_size,
                                  (GLvoid*)(3 * matrow_size));

            glEnableVertexAttribArray(3);
            glEnableVertexAttribArray(4);
            glEnableVertexAttribArray(5);
            glEnableVertexAttribArray(6);

            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);
        }

        // instance tile_index attribute, located in another buffer
        glBindBuffer(GL_ARRAY_BUFFER, gid_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(uint32_t) * gids.size(), &gids.data()[0],
                     GL_STATIC_DRAW);
        glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, sizeof(uint32_t), (GLvoid*)nullptr);
        glEnableVertexAttribArray(2);
        glVertexAttribDivisor(2, 1);




        log_gl_error_cmd();
    }

    void SpriteSheet::draw(const sc2d::TextureAtlas& texatlas)
    {
        shader.run();
        shader.set_vec3("spriteColor", math::vec3(1.0f, 1.0f, 1.0f));

        glActiveTexture(GL_TEXTURE0);
        texatlas.bind();

//        glBindVertexArray(quad_vao);
        //        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, positions.size());
//        glBindVertexArray(0);
        log_gl_error_cmd();
    }
}