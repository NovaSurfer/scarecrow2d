//
// Created by novasurfer on 11/8/21.
//

#ifndef SCARECROW2D_RENDER_H
#define SCARECROW2D_RENDER_H


namespace sc2d
{
    struct WindowSize;

    template <typename R>
    class Render : public R
    {
    public:
        void create(const WindowSize* window_size) const;
    };

    class opengl_render
    {
    protected:
        void init(const WindowSize* window_size) const;
    };
}


#endif //SCARECROW2D_RENDER_H
