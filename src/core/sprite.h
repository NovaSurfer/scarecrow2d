//
// Created by novasurfer on 20.12.18.
//

#ifndef INC_2D_GAME_SPRITE_H
#define INC_2D_GAME_SPRITE_H

#include "math/size2d.h"
#include "math/vector2.h"
#include "rendering_types.h"
#include "shader.h"

namespace sc2d
{
    class Texture2d;

    class Sprite
    {
    public:
        void init(const Shader& shader);
        void draw(const GLuint tex2d, const math::vec2& pos, const math::size2d& size,
                  const float rotate = 0.0);
    private:
        static Vertex quad_vertices[VERTICES_PER_QUAD];
        Shader shader;

        GLuint quad_vao;
    };
}

#endif //INC_2D_GAME_SPRITE_H
