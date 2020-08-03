//
// Created by novasurfer on 7/29/20.
//

#include "batchsprite.h"
//#include "glm/gtc/m"
#include "glm/gtc/matrix_transform.hpp"
#include <math/transform.h>

namespace sc2d
{
    void batchsprite::init(const Shader& shader, const math::mat4& proj)
    {
        this->shader = shader;

        u32 indices[MAX_INDICES];
        for(u32 offset = 0, i = 0; i < MAX_INDICES; i += 6) {
            indices[i + 0] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;
            indices[i + 3] = 2 + offset;
            indices[i + 4] = 3 + offset;
            indices[i + 5] = 0 + offset;
            offset += 4;
        }

        glGenVertexArrays(1, &quadvao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glBindVertexArray(quadvao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexV2) * MAX_VERTICES, nullptr, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexV2), (GLvoid*)nullptr);
        glEnableVertexAttribArray(0);
        //        // texture coord attribute
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexV2),
                              (GLvoid*)(sizeof(math::vec2)));
        glEnableVertexAttribArray(1);
//        //         color attribute
//        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(VertexV2),
//                              (GLvoid*)(sizeof(math::vec2) * 2));
//        glEnableVertexAttribArray(2);


        shader.run();
        shader.set_mat4(shader_const::MVP, proj);

        DBG_WARN_ON_RENDER_ERR
    }

    void batchsprite::draw(const math::vec2& pos, const math::vec2& size, const colorRGBA& color) {

        DBG_RETURN_IF(indices_count >= MAX_INDICES, "max vertices per draw call is reached")
        vertxbuff.add(pos, size, color);
        indices_count += 6;
        DBG_WARN_ON_RENDER_ERR
    }

    void batchsprite::flush()
    {
        shader.run();
        GLsizei sz = vertxbuff.index * sizeof(VertexV2);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sz, vertxbuff.buffer);
//                glActiveTexture(GL_TEXTURE0 + texid);
//                glBindTexture(GL_TEXTURE_2D, texid);
        glBindVertexArray(quadvao);
        glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, nullptr);

        // Resetting
        indices_count = 0;
        vertxbuff.index = 0;
        DBG_WARN_ON_RENDER_ERR
    }

    void VertexBuffer::add(const math::vec2& pos, const math::vec2& size, const colorRGBA& color)
    {
        DBG_RETURN_IF(index >= MAX_VERTICES, "max vertices per draw call is reached")
        buffer[index].pos = math::vec2(pos.x, pos.y);
//        buffer->uv = math::vec2(0, 0);
        buffer[index].color = color;
        ++index;
        buffer[index].pos = math::vec2(pos.x + size.x, pos.y);
//        buffer->uv = math::vec2(1, 0);
        buffer[index].color = color;
        ++index;
        buffer[index].pos = math::vec2(pos.x + size.x, pos.y + size.y);
//        buffer->uv = math::vec2(1, 1);
        buffer[index].color = color;
        ++index;
        buffer[index].pos = math::vec2(pos.x, pos.y + size.y);
//        buffer->uv = math::vec2(0, 1);
        buffer[index].color = color;
        ++index;
    }
}