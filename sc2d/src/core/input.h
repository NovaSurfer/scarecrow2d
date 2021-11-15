//
// Created by novasurfer on 4/19/20.
//

#ifndef SCARECROW2D_INPUT_H
#define SCARECROW2D_INPUT_H


class GLFWwindow;
namespace sc2d
{

    struct Input
    {
        static void read(GLFWwindow* window, int key, int scancode, int action, int mode);
    };
}

#endif //SCARECROW2D_INPUT_H
