//
// Created by Maksim Ruts on 02/10/2019.
//
// Entity component system from 'thebennybox'
// https://raw.githubusercontent.com/BennyQBD/3DGameProgrammingTutorial/master/LICENSE

#include "ecs_component.h"

static uint32_t common_id = 0;

uint32_t BaseECSComponent::next_id()
{
    return common_id++;
}
