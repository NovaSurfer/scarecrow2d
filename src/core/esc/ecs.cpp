//
// Created by Maksim Ruts on 24/09/2019.
//
// Entity component system from 'thebennybox'
// https://raw.githubusercontent.com/BennyQBD/3DGameProgrammingTutorial/master/LICENSE

#include "ecs.h"
#include "core/log2.h"
#include "math/utils.h"
#include <cstring>

ECS::~ECS()
{
    for(auto& entity : entities)
        delete entity;

    for(auto& component : components) {
        size_t type_size = BaseECSComponent::get_type_size(component.first);
        ECSComponentFreeFunction freefn = BaseECSComponent::get_type_freefn(component.first);
        for(size_t i = 0; i < component.second.size(); i += type_size) {
            freefn((BaseECSComponent*)&component.second[i]);
        }
    }
}

EntityHandle ECS::make_entity(BaseECSComponent* entity_components, const uint32_t* component_ids,
                              size_t num_components)
{
    auto* new_entity = new std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t>>>();
    auto handle = (EntityHandle)new_entity;

    for(size_t i = 0; i < num_components; ++i) {
        if(!BaseECSComponent::is_type_valid(component_ids[i])) {
            log_err_cmd("%u is not a valid component type.", component_ids[i]);
            delete new_entity;
            return nullptr;
        }
        add_component_internal(handle, new_entity->second, component_ids[i], &entity_components[i]);
    }

    new_entity->first = entities.size();
    entities.emplace_back(new_entity);

    return handle;
}

void ECS::remove_entity(EntityHandle handle)
{
    auto& entity = handle_to_entity(handle);
    for(auto& i : entity) {
        delete_component_internal(i.first, i.second);
    }

    uint32_t dest_index = handle_to_entity_index(handle);
    uint32_t src_index = entities.size() - 1;
    delete entities[dest_index];
    entities[dest_index] = entities[src_index];
    entities.pop_back();
}

void ECS::add_component_internal(EntityHandle handle,
                                 std::vector<std::pair<uint32_t, uint32_t>>& entity,
                                 uint32_t component_id, BaseECSComponent* component)
{
    ECSComponentCreateFunction createfn = BaseECSComponent::get_type_createfn(component_id);
    std::pair<uint32_t, uint32_t> new_pair;
    new_pair.first = component_id;
    new_pair.second = createfn(components[component_id], handle, component);
    entity.emplace_back(new_pair);
}

void ECS::delete_component_internal(uint32_t component_id, uint32_t index)
{
    std::vector<uint8_t>& array = components[component_id];
    ECSComponentFreeFunction freefn = BaseECSComponent::get_type_freefn(component_id);
    size_t type_size = BaseECSComponent::get_type_size(component_id);

    uint32_t src_index = array.size() - type_size;
    auto* dest_component = (BaseECSComponent*)&array[index];
    auto* src_component = (BaseECSComponent*)&array[src_index];
    freefn(dest_component);

    // If 'index' is last element
    if(index == src_index) {
        array.resize(src_index);
        return;
    }
    memcpy(dest_component, src_component, type_size);
    auto& src_components = handle_to_entity(src_component->entity);
    for(auto& c : src_components) {
        if(component_id == c.first && src_index == c.second) {
            c.second = index;
            break;
        }
    }
}

void ECS::remove_component_internal(EntityHandle handle, uint32_t component_id)
{
    auto& entity_components = handle_to_entity(handle);
    for(size_t i = 0; i < entity_components.size(); ++i) {
        if(component_id == entity_components[i].first) {
            delete_component_internal(entity_components[i].first, entity_components[i].second);
            uint32_t src_index = entity_components.size() - 1;
            uint32_t dest_index = i;
            entity_components[dest_index] = entity_components[src_index];
            entity_components.pop_back();
            return;
        }
    }
}

BaseECSComponent*
ECS::get_component_internal(std::vector<std::pair<uint32_t, uint32_t>>& entity_components,
                            std::vector<uint8_t>& array, uint32_t component_id) const
{
    for(auto& c : entity_components) {
        if(component_id == c.first) {
            return (BaseECSComponent*)&array[c.second];
        }
    }
    return nullptr;
}

void ECS::remove_system(BaseECSSystem& system)
{
    for(size_t i = 0; i < systems.size(); ++i) {
        if(&system == systems[i]) {
            systems.erase(systems.begin() + i);
        }
    }
}
void ECS::update_systems(float delta)
{
    std::vector<BaseECSComponent*> component_param;
    std::vector<std::vector<uint8_t>*> component_array;
    for(size_t i = 0; i < systems.size(); ++i) {
        const std::vector<uint32_t>& component_types = systems[i]->get_component_types();
        if(component_types.size() == 1) {
            size_t type_size = BaseECSComponent::get_type_size(component_types[0]);
            std::vector<uint8_t>& comps_array = components[component_types[0]];
            for(size_t j = 0; j < comps_array.size(); j += type_size) {
                auto component = (BaseECSComponent*)&comps_array[j];
                systems[i]->update_components(delta, &component);
            }
        } else {
            update_system_components(i, delta, component_types, component_param, component_array);
        }
    }
}

void ECS::update_system_components(size_t index, float delta,
                                   const std::vector<uint32_t>& component_types,
                                   std::vector<BaseECSComponent*>& component_param,
                                   std::vector<std::vector<uint8_t>*>& component_array)
{
    component_param.resize(math::utils::max(component_param.size(), component_types.size()));
    component_array.resize(math::utils::max(component_param.size(), component_array.size()));

    for(size_t i = 0; i < component_param.size(); ++i) {
        component_array[i] = &components[component_types[i]];
    }
    uint32_t min_size_index = find_least_common_component(component_types);
    size_t type_size = BaseECSComponent::get_type_size(component_types[0]);

    std::vector<uint8_t>& min_comp_array = *component_array[min_size_index];
    for(size_t i = 0; i < min_comp_array.size(); i += type_size) {
        component_param[min_size_index] = (BaseECSComponent*)&min_comp_array[i];
        auto& entity_components = handle_to_entity(component_param[min_size_index]->entity);

        bool is_valid = true;
        for(size_t j = 0; j < component_types.size(); j++) {
            if(j == min_size_index)
                continue;

            component_param[j] =
                get_component_internal(entity_components, *component_array[j], component_types[j]);
            if(component_param[j] == nullptr) {
                is_valid = false;
                break;
            }
        }
        if(is_valid)
            systems[index]->update_components(delta, &component_param[0]);
    }
}

uint32_t ECS::find_least_common_component(const std::vector<uint32_t>& component_types)
{
    size_t min_size =
        components[component_types[0]].size() / BaseECSComponent::get_type_size(component_types[0]);
    size_t min_index = 1;

    for(size_t i = 0; i < component_types.size(); ++i) {
        size_t type_size = BaseECSComponent::get_type_size(component_types[i]);
        uint32_t size = components[component_types[i]].size() / type_size;
        if(size < min_size) {
            min_size = size;
            min_index = i;
        }
    }

    return min_index;
}
