//
// Created by Maksim Ruts on 27/08/2020.
//

#ifndef SCARECROW2D_QUEUE_H
#define SCARECROW2D_QUEUE_H

#include "../core/types.h"
#include <memory/pool_allocator.h>

// WIP
// TODO:  ------------------- Write tests and benchmarks -------------------
// TODO: add pool alloc support


namespace sc2d
{

    template <typename T>
    class queue
    {
    public:

        T push(const T& t);
        T& front() const {return head->data;}
        void pop();
        bool empty();
    private:
        struct node;
        u32 length;
        node* head;
        node* tail;
    };

    template<typename T>
    struct queue<T>::node
    {
        explicit node(const T& t): data(t), next(nullptr) {}

        T data;
        node* next;
    };
    template<typename T>
    T queue<T>::push(const T& t)
    {
        node* n = new node(t);
        n->next = head;
        head = n;
        if(length == 0)
            tail = n;
        ++length;
        return t;
    }

    template <typename T>
    void queue<T>::pop()
    {
        if(length == 0)
            return;
        T t = head->data;
        node* n = head;
        head = head->next;
        delete n;
        if(--length == 0)
            tail == nullptr;
    }

    template <typename T>
    bool queue<T>::empty()
    {
        return head == nullptr;
    }

}

#endif //SCARECROW2D_QUEUE_H
