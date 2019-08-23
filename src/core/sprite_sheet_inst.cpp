//
// Created by novasurfer on 7/7/19.
//

#include "sprite_sheet_inst.h"
#include "texture_atlas.h"

namespace sc2d
{
    Vertex SpriteSheetInstanced::quad_vertices[VERTICES_PER_QUAD] {SPRITE_QUAD.tr, SPRITE_QUAD.br,
                                                                   SPRITE_QUAD.bl, SPRITE_QUAD.tl};

    void SpriteSheetInstanced::draw(const GLuint tex_id)
    {
        shader.run();
        shader.set_vec3("spriteColor", math::vec3(1.0f, 1.0f, 1.0f));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D_ARRAY, tex_id);
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, sprites_count);
        log_gl_error_cmd();
    }
}