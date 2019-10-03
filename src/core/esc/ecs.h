//
// Created by Maksim Ruts on 24/09/2019.
//

#ifndef SCARECROW2D_ECS_H
#define SCARECROW2D_ECS_H

#include "ecs_component.h"
#include "ecs_system.h"
#include <map>

class ECS
{
public:
    ECS(const ECS&) = delete;
    ECS(ECS&&) = delete;
    ECS& operator=(const ECS&) = delete;
    ECS& operator=(ECS&&) = delete;

    // Entity methods
    EntityHandle make_entity(BaseECSComponent* components, const uint32_t* component_ids,
                             size_t num_components);
    void remove_entity(EntityHandle handle);

    // Components methods
    template <typename Component>
    void add_component(EntityHandle entity, Component* component);
    template <typename Component>
    void remove_component(EntityHandle entity);
    template <typename Component>
    void get_component(EntityHandle entity);

    // System methods
    void add_system(BaseECSSystem& system)
    {
        systems.emplace_back(&system);
    }

    void remove_system(BaseECSSystem& system);
    void update_systems(float delta);
private:
    std::vector<BaseECSSystem> systems;
    std::map<uint32_t, std::vector<uint8_t>> components;
    std::vector<std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t>>>*> entities;

    auto handle_to_raw_type(EntityHandle handle)
    {
        return static_cast<std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t>>>*>(
            handle);
    }

    uint32_t handle_to_entity_index(EntityHandle handle)
    {
        return handle_to_raw_type(handle)->first;
    }

    auto& handle_to_entity(EntityHandle handle)
    {
        return handle_to_raw_type(handle)->second;
    }
};

#endif //SCARECROW2D_ECS_H