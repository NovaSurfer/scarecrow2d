//
// Created by novasurfer on 20.12.18.
//

#ifndef INC_2D_GAME_SPRITE_H
#define INC_2D_GAME_SPRITE_H

#include "shader.h"
#include "texture.h"
#include "sc2dTypes.h"
#include "math/vector2.h"
#include "math/size2d.h"

namespace sc2d {
    class Sprite {
    public:
        explicit Sprite(const Shader& shader);
        void draw(const Texture2d& tex2d, math::vec2 pos,
                math::size2d = {10,10}, float rotate = 0.0);

    private:
        static Vertex quad_vertices[VERTICES_PER_QUAD];
        Shader shader;
        GLuint quad_vao;

        void init_data();
    };
}


#endif //INC_2D_GAME_SPRITE_H
