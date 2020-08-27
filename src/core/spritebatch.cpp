//
// Created by novasurfer on 7/29/20.
//

#include "spritebatch.h"
#include <math/transform.h>

namespace sc2d
{
    void SpriteBatch::init(const Shader& shader, const math::mat4& proj)
    {
        this->shader = shader;
        GLuint ebo;
        quadbuff.index = 0;
        indices_count = 0;

        u32 indices[limits::DRAWCALL_INDICES];
        for(u32 offset = 0, i = 0; i < limits::DRAWCALL_INDICES; i += 6) {
            indices[i + 0] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 3 + offset;
            indices[i + 3] = 1 + offset;
            indices[i + 4] = 2 + offset;
            indices[i + 5] = 3 + offset;
            offset += 4;
        }

        glGenVertexArrays(1, &quadvao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glBindVertexArray(quadvao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexColored) * limits::DRAWCALL_VERTICES, nullptr,
                     GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexColored), (GLvoid*)nullptr);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexColored),
                              (GLvoid*)(sizeof(math::vec2)));
        // color attribute
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(VertexColored),
                              (GLvoid*)(sizeof(math::vec2) * 2));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        // Generating texture
        const u32 white = 0xffffffff;
        glGenTextures(1, &texid);
        glBindTexture(GL_TEXTURE_2D, texid);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &white);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        shader.run();
        shader.set_mat4(shader_const::PROJ, proj);
        shader.set_int("img", texid);

        DBG_WARN_ON_RENDER_ERR
    }

    void SpriteBatch::draw(const math::vec2& pos, const math::vec2& size, const colorRGBA& color)
    {
        // If max indices per draw call reached we should split draw calls
        if(indices_count >= limits::DRAWCALL_INDICES) {
            flush();
        }
        quadbuff.add(pos, size, color);
        indices_count += 6;

        DBG_WARN_ON_RENDER_ERR
    }
    void SpriteBatch::flush()
    {
        shader.run();
        // num_of_objects * sizeof(Vertex) * 4_indices_per_quad
        const GLsizei vertices_size = quadbuff.index * sizeof(VertexColored) * 4;
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_size, quadbuff.data);
        glActiveTexture(GL_TEXTURE0 + texid);
        glBindTexture(GL_TEXTURE_2D, texid);
        glBindVertexArray(quadvao);
        glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, nullptr);

        // Resetting
        indices_count = 0;
        quadbuff.index = 0;
        DBG_WARN_ON_RENDER_ERR
    }
}