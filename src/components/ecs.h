//
// Created by Maksim Ruts on 21-Apr-18.
//

#ifndef INC_2D_ENGINE_ECS_H
#define INC_2D_ENGINE_ECS_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;

class Entity;

constexpr std::size_t maxComponents = 32;
using ComponentID = std::size_t;
using ComponentBitSet = std::bitset<maxComponents>;
// TODO: make it a unique_pointer
using ComponentArray = std::array<Component *, maxComponents>;

inline ComponentID get_component_type_id()
{
    static ComponentID lastID = 0;
    return lastID++;
}

template<typename T>
inline ComponentID get_component_type_id() noexcept
{
    static ComponentID typeID = get_component_type_id();
    return typeID;
}

class Component {
public:
    Entity *entity;

    virtual void init() {}

    virtual void update() {}

    virtual void draw() {}

    virtual ~Component() {};
};

class Entity {
private:
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;
    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
public:
    void update()
    {
        for (auto &c: components) c->update();
    }

    void draw()
    {
        for (auto &c: components) c->draw();
    }

    void destroy() { active = false; }

    bool is_active() const { return active; }

    template<typename T>
    bool has_component() const
    {
        return componentBitSet[get_component_type_id<T>()];
    }

    template<typename T, typename... TArgs>
    T &add_component(TArgs &&... mArgs)
    {
        T *c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> u_ptr{c};
        components.emplace_back(std::move(u_ptr));
        componentArray[get_component_type_id<T>()] = c;
        componentBitSet[get_component_type_id<T>()] = true;

        c->init();
        return *c;
    }

    template<typename T>
    T &get_component() const
    {
        auto ptr = (componentArray[get_component_type_id<T>()]);
        return *static_cast<T *>(ptr);
    }
};

class Manager {
private:
    std::vector<std::unique_ptr<Entity>> entities;
public:
    void update()
    {
        for (auto &e : entities) e->update();
    }

    void draw()
    {
        for (auto &e : entities) e->draw();
    }

    void refresh()
    {
        // Remove entity if it's not active
        entities.erase(std::remove_if(
                entities.begin(),
                entities.end(),
                [](const std::unique_ptr<Entity> &mEntity) {
                    return !mEntity->is_active();
                }),
                       std::end(entities));

    }

    Entity &add_entity()
    {
        Entity *e = new Entity();
        std::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr));
        return *e;
    }

/*    Entity& add_entity()
    {
        std::unique_ptr<Entity> e = std::make_unique<Entity>();
        entities.emplace_back(std::move(e));
        return *e;
    }*/


};


#endif //INC_2D_ENGINE_ECS_H
