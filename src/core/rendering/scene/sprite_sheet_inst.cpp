//
// Created by novasurfer on 7/7/19.
//

#include "sprite_sheet_inst.h"
#include "core/rendering/texture_atlas.h"
#include "collections/arr.h"

namespace sc2d
{

    void SpriteSheetInstanced::init(const Shader& spr_shader, const math::vec2& spr_size,
                                    const size_t spr_count, const math::mat4& projection,
                                    const SpriteSheetInstData& sid)
    {
        shader = spr_shader;
        instances_count = spr_count;
        this->size = spr_size;

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

        // instance 'tile_index' attribute, located in 'gid_vbo' buffer
        glBindBuffer(GL_ARRAY_BUFFER, gid_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(uint32_t) * spr_count, sid.gid.get(), GL_STATIC_DRAW);
        glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(uint32_t), (GLvoid*)nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribDivisor(0, 1);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * VERTICES_PER_QUAD, QUAD_VERTICES,
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QUAD_INDICES), QUAD_INDICES, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)nullptr);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (GLvoid*)(sizeof(math::vec2)));
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        // instance 'model' attribute, located in 'model_vbo' buffer
        DBG_FAIL_IF(spr_count > limits::SPRITE_INSTANCES, "sprite sheet contains to many sprites")
        arr<math::mat4, limits::SPRITE_INSTANCES> model_matrices;
        for(size_t i = 0; i < spr_count; ++i) {
            model_matrices[i] = math::transform(
                math::vec3(size.x, size.y, 1.0f), math::vec3(0.0f, 0.0f, 1.0f), 0,
                math::vec3(0.5f * size.x + sid.pos[i].x, 0.5f * size.y + sid.pos[i].y, 0.0f)) * projection;
        }
        glBindBuffer(GL_ARRAY_BUFFER, model_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(math::mat4) * spr_count, &model_matrices[0],
                     GL_STATIC_DRAW);

        constexpr size_t matrow_size = sizeof(float) * 4;
        for(size_t i = 0; i < spr_count; ++i) {
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

        //        log_gl_error_cmd();
    }

    void SpriteSheetInstanced::draw() const
    {
        shader.run();
        glActiveTexture(GL_TEXTURE0 + texid);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texid);
        glBindVertexArray(quad_vao);
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, instances_count);
    }
}