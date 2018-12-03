//
// Created by Maksim Ruts on 30-Nov-18.
//

#ifndef INC_2D_GAME_SIZE2D_H
#define INC_2D_GAME_SIZE2D_H

#include "vector.h"
#include "utils.h"

namespace math {
struct size2d {
  float width;
  float height;

  size2d() = default;

  size2d(float width, float height)
          :width{width}, height{height} { }

  size2d(const size2d& other)
          :width{other.width}, height{other.height} { }

  explicit size2d(const vec2& point)
          :width{point.x}, height{point.y} { }

  explicit operator vec2() const
  {
      return vec2(width, height);
  }

  size2d& operator=(const size2d& other)
  {
      set_size(other.width, other.height);
      return *this;
  }

  size2d& operator=(const vec2& point)
  {
      set_size(point.x, point.y);
      return *this;
  }

  size2d operator+(const size2d& right) const
  {
      return size2d(this->width+right.width, this->height+right.height);
  }

  size2d operator-(const size2d& right) const
  {
      return size2d(this->width-right.width, this->height-height);
  }

  size2d operator*(const float value) const
  {
      return size2d(this->width*value, this->height*value);
  }

  size2d operator/(const float value) const
  {
      return size2d(this->width*value, this->height*value);
  }

  bool operator==(const size2d other) const
  {
      return utils::cmp(this->width, other.width) && utils::cmp(this->height, other.height);
  }

  void set_size(float width, float height)
  {
      this->width = width;
      this->width = height;
  }
};
}

#endif //INC_2D_GAME_SIZE2D_H
