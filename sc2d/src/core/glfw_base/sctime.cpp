//
// Created by novasurfer on 11/7/21.
//

#include "sctime.h"
#include <GLFW/glfw3.h>

namespace sc2d
{
    double Time::get_time()
    {
        return glfwGetTime();
    }

    void Time::set_time(double time)
    {
        glfwSetTime(time);
    }
}
