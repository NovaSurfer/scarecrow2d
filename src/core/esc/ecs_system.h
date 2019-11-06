//
// Created by Maksim Ruts on 03/10/2019.
//
// Entity component system from 'thebennybox'
// https://raw.githubusercontent.com/BennyQBD/3DGameProgrammingTutorial/master/LICENSE

#ifndef SCARECROW2D_ECS_SYSTEM_H
#define SCARECROW2D_ECS_SYSTEM_H

#include "ecs_component.h"

/**
 * Contains some list of Components
 */
class BaseECSSystem
{
public:
    /**
     * @param component_types component types ids
     */
    explicit BaseECSSystem(const std::vector<uint32_t>& component_types)
        : component_types(component_types) {};

    virtual ~BaseECSSystem() = default;

    virtual void update_components(float delta, BaseECSComponent** components);

    [[nodiscard]] const std::vector<compId_t>& get_component_types() const
    {
        return component_types;
    }

private:
    // Stores component types ids
    std::vector<compId_t> component_types;
};

#endif //SCARECROW2D_ECS_SYSTEM_H
