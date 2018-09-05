//
// Created by Maksim Ruts on 29-Aug-18.
//

#ifndef INC_2D_GAME_TEXTURE_H
#define INC_2D_GAME_TEXTURE_H

#include <glad/glad.h>

class Texture2d {
public:
    Texture2d() = default;
    Texture2d(unsigned char* img_data, const GLuint width, const GLuint height);
    Texture2d(unsigned char* img_data, const GLuint width, const GLuint height, const GLuint img_format);
    const GLuint &get_obj_id() const;

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

    unsigned char* data;

    void generate();

};


#endif //INC_2D_GAME_TEXTURE_H