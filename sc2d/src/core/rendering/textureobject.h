//
// Created by novasurfer on 8/22/20.
//

#ifndef SCARECROW2D_TEXTUREOBJECT_H
#define SCARECROW2D_TEXTUREOBJECT_H

#include "core/compiler.h"
#include "aglet/aglet.h"

namespace sc2d
{

    struct texgen
    {
        template <typename T>
        static void generate(T* texdata);
    };

    class default_tex2d
    {
        friend texgen;

    public:
        default_tex2d() = default;
        default_tex2d(const GLuint width, const GLuint height, const GLuint internal_format,
                      const GLuint image_format, const GLuint wrap_s, const GLuint wrap_t,
                      const GLuint filter_min, const GLuint filter_max, unsigned char* img_data);

        forceinline const GLuint& get_obj_id() const
        {
            return obj_id;
        }

        forceinline operator GLuint() const
        {
            return obj_id;
        }

    protected:
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
    };

    class default_tex2darr : public default_tex2d
    {
        friend texgen;

    public:
        using default_tex2d::default_tex2d;
        default_tex2darr(const GLuint width, const GLuint height, const GLuint internal_format,
                         const GLuint image_format, const GLuint wrap_s, const GLuint wrap_t,
                         const GLuint filter_min, const GLuint filter_max, unsigned char* img_data,
                         GLuint rows, GLuint columns);

    protected:
        GLuint rows;
        GLuint columns;
    };
}

#endif //SCARECROW2D_TEXTUREOBJECT_H
