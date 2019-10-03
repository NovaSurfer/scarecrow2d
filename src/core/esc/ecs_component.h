//
// Created by Maksim Ruts on 02/10/2019.
//
// Entity component system from 'thebennybox'
// https://raw.githubusercontent.com/BennyQBD/3DGameProgrammingTutorial/master/LICENSE

#ifndef SCARECROW2D_ECS_COMPONENT_H
#define SCARECROW2D_ECS_COMPONENT_H

#include <vector>
#include <tuple>

struct BaseECSComponent;
using EntityHandle = void*;
using ECSComponentCreateFunction = uint32_t (*)(std::vector<uint8_t>& memory, EntityHandle entity,
                                                BaseECSComponent* comp);
using ECSComponentFreeFunction = uint32_t (*)(BaseECSComponent* comp);

class BaseECSComponent
{
public:
    static size_t register_component_type(ECSComponentCreateFunction createfn,
                                          ECSComponentFreeFunction freefn, size_t size);
    EntityHandle entity = nullptr;

    static ECSComponentCreateFunction get_type_createfn(uint32_t id)
    {
        return std::get<0>(component_types[id]);
    }

    static ECSComponentFreeFunction get_type_freefn(uint32_t id)
    {
        return std::get<1>(component_types[id]);
    }

    static size_t get_type_size(uint32_t id)
    {
        return std::get<2>(component_types[id]);
    }

private:
    static std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>>
        component_types;
};

template <typename T>
struct ECSComponent : public BaseECSComponent
{
    static const ECSComponentCreateFunction CREATE_FUNCTION;
    static const ECSComponentFreeFunction FREE_FUNCTION;
    static const uint32_t id;
    static const size_t size;
};

template <typename Component>
uint32_t ECSComponentCreate(std::vector<uint8_t>& memory, EntityHandle entity,
                            BaseECSComponent* comp)
{
    size_t index = memory.size();
    memory.resize(index + Component::size);
    Component* component = new(&memory[index]) Component(*(Component*)comp);
    component->entity = entity;
    return index;
}

template <typename Component>
uint32_t ECSComponentFree(BaseECSComponent* comp)
{
    Component* component = (Component*)comp;
    component->~Component();
}

template <typename T>
const uint32_t ECSComponent<T>::id(BaseECSComponent::register_component_type(ECSComponentCreate<T>,
                                                                             ECSComponentFree<T>,
                                                                             sizeof(T)));

template <typename T>
const size_t ECSComponent<T>::size(sizeof(T));

template <typename T>
const ECSComponentCreateFunction ECSComponent<T>::CREATE_FUNCTION(ECSComponentCreate<T>);

template <typename T>
const ECSComponentFreeFunction ECSComponent<T>::FREE_FUNCTION(ECSComponentFree<T>);

// EXAMPLE
struct TestComponent : ECSComponent<TestComponent>
{
    float x;
    float y;
};

#endif //SCARECROW2D_ECS_COMPONENT_H
