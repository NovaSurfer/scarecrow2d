//
// Created by novasurfer on 7/1/19.
//

#ifndef INC_2D_GAME_TEXTURE_ATLAS_H
#define INC_2D_GAME_TEXTURE_ATLAS_H

#include <glad/glad.h>
#include <string>

// For now Texture Atlas class looks almost the same as Texture2d,
// but in future Texture2d or TextureAtlas may use additional rendering techniques.
// For now I don't want make any abstract classes, because I don't want to pay for that abstraction
// or for code branching as Texture2d and TextureAtlas will be used quite often.

class TextureAtlas
{
    TextureAtlas() = default;
    TextureAtlas(unsigned char* img_data, const GLuint width, const GLuint height,
                 const GLuint img_format);
    void bind() const;
    const GLuint& get_obj_id() const;

private:
    GLuint obj_id;
    GLuint width;
    GLuint height;
    GLuint internal_format;
    GLuint image_format;
    GLuint wrap_s;
    GLuint wrap_t;
    GLuint filter_min;
    GLuint filter_max;
    GLenum texture_type;

    unsigned char* data;

    void generate();
};

#endif //INC_2D_GAME_TEXTURE_ATLAS_H
