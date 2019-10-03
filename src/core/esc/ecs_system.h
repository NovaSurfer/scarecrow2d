//
// Created by Maksim Ruts on 03/10/2019.
//

#ifndef SCARECROW2D_ECS_SYSTEM_H
#define SCARECROW2D_ECS_SYSTEM_H

#include "ecs_component.h"

class BaseECSSystem
{
public:
    explicit BaseECSSystem(const std::vector<uint32_t>& component_types)
        : component_types(component_types) {};
    virtual void update_components(float delta, BaseECSComponent** components) {}
    [[nodiscard]] const std::vector<uint32_t>& get_component_types() const
    {
        return component_types;
    }
    virtual ~BaseECSSystem() = default;

private:
    std::vector<uint32_t> component_types;
};

#endif //SCARECROW2D_ECS_SYSTEM_H
