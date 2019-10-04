//
// Created by Maksim Ruts on 24/09/2019.
//

#include "ecs.h"
#include "core/log2.h"

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
    EntityHandle handle = (EntityHandle)new_entity;

    for(size_t i = 0; i < num_components; ++i) {
        if(!BaseECSComponent::is_type_valid(component_ids[i])) {
            log_err_cmd("%u is not a valid component type.", component_ids[i]);
            delete new_entity;
            return nullptr;
        }

        ECSComponentCreateFunction createfn = BaseECSComponent::get_type_createfn(component_ids[i]);
        std::pair<uint32_t, uint32_t> new_pair;
        new_pair.first = component_ids[i];
        new_pair.second =
             createfn(entity_components[component_ids[i]], handle, &entity_components[i]);
        new_entity->second.emplace_back(new_pair);
    }

    new_entity->first = entities.size();
    entities.emplace_back(new_entity);

    return handle;
}
void ECS::remove_entity(EntityHandle handle)
{
    auto& entity = handle_to_entity(handle);
    for(auto& i : entity) {
        remove_component_internal(i.first, i.second);
    }

    uint32_t dest_index = handle_to_entity_index(handle);
    uint32_t src_index = entities.size() - 1;
    delete entities[dest_index];
    entities[dest_index] = entities[src_index];
    entities.pop_back();
}
