//
// Created by novasurfer on 7/7/19.
//

#ifndef INC_2D_GAME_SPRITE_SHEET_INST_H
#define INC_2D_GAME_SPRITE_SHEET_INST_H

#include "debug_utils.h"
#include "math/size2d.h"
#include "math/transform.h"
#include "math/vector2.h"
#include "sc2dTypes.h"
#include "shader.h"
#include <vector>

namespace sc2d
{

    template <size_t N>
    struct SpriteSheetInstanceData
    {
        uint32_t gid[N] {};
        math::vec2 pos[N];
    };

    class SpriteSheetInstanced
    {
    public:
        SpriteSheetInstanced() = default;
        void draw(const GLuint tex_id);

        template <size_t SPRITES_COUNT>
        void init_data(const sc2d::Shader& spr_shader, const math::size2d& spr_size,
                       const SpriteSheetInstanceData<SPRITES_COUNT>& sid)
        {
            shader = spr_shader;
            sprites_count = SPRITES_COUNT;

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
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QUAD_INDICES), QUAD_INDICES,
                         GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)nullptr);
            // texture coord attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                  (GLvoid*)(sizeof(math::vec2)));
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);

            // instance 'model' attribute, located in 'model_vbo' buffer
            math::mat4 model_matrices[SPRITES_COUNT];
            for(size_t i = 0; i < SPRITES_COUNT; ++i) {
                model_matrices[i] =
                    math::transform(math::vec3(spr_size.width, spr_size.height, 1.0f),
                                    math::vec3(0.0f, 0.0f, 1.0f), 0,
                                    math::vec3(0.5f * spr_size.width + sid.pos[i].x,
                                               0.5f * spr_size.height + sid.pos[i].y, 0.0f));
            }
            glBindBuffer(GL_ARRAY_BUFFER, model_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(math::mat4) * SPRITES_COUNT, &model_matrices[0],
                         GL_STATIC_DRAW);

            size_t matrow_size = sizeof(float) * 4;
            for(size_t i = 0; i < SPRITES_COUNT; ++i) {
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

            // instance 'tile_index' attribute, located in 'gid_vbo' buffer
            glBindBuffer(GL_ARRAY_BUFFER, gid_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(uint32_t) * SPRITES_COUNT, &sid.gid,
                         GL_STATIC_DRAW);
            glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, sizeof(uint32_t), (GLvoid*)nullptr);
            glEnableVertexAttribArray(2);
            glVertexAttribDivisor(2, 1);

            log_gl_error_cmd();
        }

    private:
        static Vertex quad_vertices[VERTICES_PER_QUAD];
        Shader shader;
        size_t sprites_count;
        GLuint quad_vao;
    };
}

#endif //INC_2D_GAME_SPRITE_SHEET_INST_H
