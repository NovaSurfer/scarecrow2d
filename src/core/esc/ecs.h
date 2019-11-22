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

/**
 * Main class for Entity Component System
 */
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
    /**
     * Makes entity
     * @param entity_components components attached to the entity
     * @param component_ids components types ids
     * @param num_components nubmer of components
     * @return
     */
    EntityHandle make_entity(BaseECSComponent* entity_components, const compId_t* component_ids,
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
        systems.emplace_back(&system);
    }

    void remove_system(BaseECSSystem& system);
    void update_systems(float delta);

private:
    std::vector<BaseECSSystem*> systems;
    // contains: component id, component's memory
    std::map<compId_t, std::vector<uint8_t>> components;
    // [vector]<[pair]<index in array it self,[vector]<[pair]< component id, index of component in components array>>>>
    std::vector<std::pair<uint32_t, std::vector<std::pair<compId_t, uint32_t>>>*> entities;

    /**
     * Utility method: casts Entity handle to raw entity type
     * @param handle Entity handle
     * @return
     */
    auto handle_to_raw_type(EntityHandle handle) const
    {
        return static_cast<std::pair<uint32_t, std::vector<std::pair<compId_t, uint32_t>>>*>(
            handle);
    }

    /**
     * Utility method: casts Entity handle to entity index in entities vector
     * @param handle Entity handle
     * @return
     */
    uint32_t handle_to_entity_index(EntityHandle handle) const
    {
        return handle_to_raw_type(handle)->first;
    }

    /**
     * Utility method: casts Entity handle to entity type
     * @param handle Entity handle
     * @return
     */
    std::vector<std::pair<compId_t, uint32_t>>& handle_to_entity(EntityHandle handle) const
    {
        return handle_to_raw_type(handle)->second;
    }

    void update_system_components(size_t index, float delta,
                                  const std::vector<uint32_t>& component_types,
                                  std::vector<BaseECSComponent*>& component_param,
                                  std::vector<std::vector<uint8_t>*>& component_array);
    void add_component_internal(EntityHandle handle,
                                std::vector<std::pair<compId_t, uint32_t>>& entity,
                                compId_t component_id, BaseECSComponent* component);
    void remove_component_internal(EntityHandle handle, compId_t component_id);
    void delete_component_internal(compId_t component_id, uint32_t index);
    BaseECSComponent*
    get_component_internal(std::vector<std::pair<compId_t, uint32_t>>& entity_components,
                           std::vector<uint8_t>& array, uint32_t component_id) const;
    uint32_t find_least_common_component(const std::vector<uint32_t>& component_types);
};

#endif //SCARECROW2D_ECS_H