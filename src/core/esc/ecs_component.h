//
// Created by Maksim Ruts on 02/10/2019.
//
// Entity component system from 'thebennybox'
// https://raw.githubusercontent.com/BennyQBD/3DGameProgrammingTutorial/master/LICENSE

#ifndef SCARECROW2D_ECS_COMPONENT_H
#define SCARECROW2D_ECS_COMPONENT_H

#include <cstdint>
#include <cstdlib>
#include <vector>


struct BaseECSComponent;
using EntityHandle = void*;
using ECSComponentCreateFunction = uint32_t (*)(std::vector<uint8_t>& memory, EntityHandle entity,
                                                BaseECSComponent* comp);
using ECSComponentFreeFunction = uint32_t (*)(BaseECSComponent* comp);

struct BaseECSComponent
{
    static uint32_t next_id();
    EntityHandle entity = nullptr;
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
const uint32_t ECSComponent<T>::id(BaseECSComponent::next_id());

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
