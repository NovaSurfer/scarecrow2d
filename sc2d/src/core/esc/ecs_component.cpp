//
// Created by Maksim Ruts on 02/10/2019.
//
// Entity component system from 'thebennybox'
// https://raw.githubusercontent.com/BennyQBD/3DGameProgrammingTutorial/master/LICENSE

#include "ecs_component.h"

std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>>
    BaseECSComponent::component_types;

size_t BaseECSComponent::register_component_type(ECSComponentCreateFunction createfn,
                                                 ECSComponentFreeFunction freefn, size_t size)
{
    size_t component_id = component_types.size();
    component_types.emplace_back((std::forward_as_tuple(createfn, freefn, size)));
    return component_id;
}
