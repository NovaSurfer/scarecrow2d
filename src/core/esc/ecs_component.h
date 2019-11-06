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

// Define function pointers
using ECSComponentCreateFunction = uint32_t (*)(std::vector<uint8_t>& memory, EntityHandle entity,
                                                BaseECSComponent* comp);
using ECSComponentFreeFunction = void (*)(BaseECSComponent* comp);

using compId_t = uint32_t;

class BaseECSComponent
{
public:
    static size_t register_component_type(ECSComponentCreateFunction createfn,
                                          ECSComponentFreeFunction freefn, size_t size);
    EntityHandle entity = nullptr;

    static ECSComponentCreateFunction get_type_createfn(compId_t id)
    {
        return std::get<0>(component_types[id]);
    }

    static ECSComponentFreeFunction get_type_freefn(compId_t id)
    {
        return std::get<1>(component_types[id]);
    }

    static size_t get_type_size(compId_t id)
    {
        return std::get<2>(component_types[id]);
    }

    static bool is_type_valid(compId_t id)
    {
        return id >= component_types.size();
    }

private:
    static std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>>
        component_types;
};

/**
 * ECS Component
 * We are using 'Curiously recurring template pattern'
 * In order to get static variables in every derived component class
 * @tparam T the component class itself
 */
template <typename T>
struct ECSComponent : public BaseECSComponent
{
    static const ECSComponentCreateFunction CREATE_FUNCTION;
    static const ECSComponentFreeFunction FREE_FUNCTION;
    // Index for component type in oder to distinguish type from another
    static const compId_t id;
    // Component type size
    static const size_t size;
};

/**
 * Creates component and allocates memory for it.
 * @tparam Component component class
 * @param memory
 * @param entity Entity in which the Component will be stored
 * @param comp component
 * @return Component index
 */
template <typename Component>
uint32_t ECSComponentCreate(std::vector<uint8_t>& memory, EntityHandle entity,
                            BaseECSComponent* comp)
{
    size_t index = memory.size();
    // Resizing, making an offset with 'last index + component size'
    memory.resize(index + Component::size);
    // Construct new component in the address of 'memory' which is already allocated
    Component* component = new(&memory[index]) Component(*(Component*)comp);
    component->entity = entity;
    return index;
}

/**
 * Frees component from memory
 * @tparam Component component class
 * @param comp component
 * @return
 */
template <typename Component>
void ECSComponentFree(BaseECSComponent* comp)
{
    Component* component = (Component*)comp;
    component->~Component();
}

template <typename T>
const uint32_t ECSComponent<T>::id(BaseECSComponent::register_component_type(ECSComponentCreate<T>,
                                                                             ECSComponentFree<T>,
                                                                             sizeof(T)));

/**
 * Size of Component, needed for Component allocation
 * @tparam T Component
 */
template <typename T>
const size_t ECSComponent<T>::size(sizeof(T));

/**
 * Init create function pointer
 * @tparam T component class
 */
template <typename T>
const ECSComponentCreateFunction ECSComponent<T>::CREATE_FUNCTION(ECSComponentCreate<T>);

/**
 * Init free function pointer
 * @tparam T component class
 */
template <typename T>
const ECSComponentFreeFunction ECSComponent<T>::FREE_FUNCTION(ECSComponentFree<T>);

// EXAMPLE
struct TestComponent : ECSComponent<TestComponent>
{
    float x;
    float y;
};

#endif //SCARECROW2D_ECS_COMPONENT_H
