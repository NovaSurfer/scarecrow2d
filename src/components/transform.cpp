//
// Created by Maksim Ruts on 25-Apr-18.
//

#include "transform.h"

void Transform::init() {
    xpos = 0;
    ypos = 0;
}

void Transform::setPos(int x, int y) {
    xpos = x;
    ypos = y;
}

void Transform::update() {
    xpos++;
    ypos++;
}
