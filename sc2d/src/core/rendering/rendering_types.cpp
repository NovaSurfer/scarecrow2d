//
// Created by novasurfer on 8/6/20.
//

#include "rendering_types.h"

namespace sc2d
{

    void QuadBuffer::add(const math::vec2& pos, const math::vec2& size, const colorRGBA& color)
    {
        data[index].tr = {math::vec2(pos.x, pos.y + size.y), math::vec2(0, 1), color};
        data[index].br = {math::vec2(pos.x + size.x, pos.y + size.y), math::vec2(1, 1), color};
        data[index].bl = {math::vec2(pos.x + size.x, pos.y), math::vec2(1, 0), color};
        data[index].tl = {math::vec2(pos.x, pos.y), math::vec2(0, 0), color};
        ++index;
    }
}