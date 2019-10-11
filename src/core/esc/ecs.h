//
// Created by Maksim Ruts on 24/09/2019.
//
// Entity component system from 'thebennybox'
// https://raw.githubusercontent.com/BennyQBD/3DGameProgrammingTutorial/master/LICENSE

#ifndef SCARECROW2D_ECS_H
#define SCARECROW2D_ECS_H

#include "ecs_component.h"
#include "ecs_system.h"
#include <map>

class ECS
{
public:
    ECS() = default;
    ~ECS();
    ECS(const ECS&) = delete;
    ECS(ECS&&) = delete;
    ECS& operator=(const ECS&) = delete;
    ECS& operator=(ECS&&) = delete;

    // Entity methods
    EntityHandle make_entity(BaseECSComponent* entity_components, const uint32_t* component_ids,
                             size_t num_components);
    void remove_entity(EntityHandle handle);

    // Components methods
    template <typename Component>
    void add_component(EntityHandle entity, Component* component)
    {
        add_component_internal(entity, handle_to_entity(entity), Component::id, Component::size);
    }

    template <typename Component>
    void remove_component(EntityHandle entity)
    {
        remove_component_internal(entity, Component::id);
    }

    template <typename Component>
    Component* get_component(EntityHandle entity) const
    {
        return get_component_internal(handle_to_entity(entity), components[Component::id],
                                      Component::id);
    }

    // System methods
    void add_system(BaseECSSystem& system)
    {
        systems.emplace_back(system);
    }

    void remove_system(BaseECSSystem& system);
    void update_systems(float delta);

private:
    std::vector<BaseECSSystem> systems;
    std::map<uint32_t, std::vector<uint8_t>> components;
    std::vector<std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t>>>*> entities;
    auto handle_to_raw_type(EntityHandle handle) const
    {
        return static_cast<std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t>>>*>(
            handle);
    }

    uint32_t handle_to_entity_index(EntityHandle handle) const
    {
        return handle_to_raw_type(handle)->first;
    }

    std::vector<std::pair<uint32_t, uint32_t>>& handle_to_entity(EntityHandle handle) const
    {
        return handle_to_raw_type(handle)->second;
    }

    void update_system_components(size_t index, float delta,
                                  const std::vector<uint32_t>& component_types,
                                  std::vector<BaseECSComponent*>& component_param,
                                  std::vector<std::vector<uint8_t>*>& component_array);
    void add_component_internal(EntityHandle handle,
                                std::vector<std::pair<uint32_t, uint32_t>>& entity,
                                uint32_t component_id, BaseECSComponent* component);
    void remove_component_internal(EntityHandle handle, uint32_t component_id);
    void delete_component_internal(uint32_t component_id, uint32_t index);
    BaseECSComponent*
    get_component_internal(std::vector<std::pair<uint32_t, uint32_t>>& entity_components,
                           std::vector<uint8_t>& array, uint32_t component_id) const;
    uint32_t find_least_common_component(const std::vector<uint32_t>& component_types);
};

#endif //SCARECROW2D_ECS_H