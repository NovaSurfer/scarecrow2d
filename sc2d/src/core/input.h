//
// Created by novasurfer on 4/19/20.
//

#ifndef SCARECROW2D_INPUT_H
#define SCARECROW2D_INPUT_H


class GLFWwindow;
namespace sc2d
{
    class Window;
    class Input
    {
    public:
        Input() = default;
        Input(const Window& window);
        static void read(GLFWwindow* window, int key, int scancode, int action, int mode);
        bool get_key(int key);
        bool get_key_down(int key);
        bool get_key_up(int key);

    private:
        int key;
        int scancode;
        int action;
        int mode;

        void set_key_input(int key, int scancode, int action, int mode);
    };
}

#endif //SCARECROW2D_INPUT_H
