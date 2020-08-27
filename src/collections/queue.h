//
// Created by Maksim Ruts on 27/08/2020.
//

#ifndef SCARECROW2D_QUEUE_H
#define SCARECROW2D_QUEUE_H

#include "core/types.h"

// WIP
// TODO:  ------------------- Write tests and benchmarks -------------------
// TODO: add pool alloc support


namespace sc2d
{

    template <typename T>
    class queue
    {
    public:
        queue() = default;

        T push(const T& t);
        T pop();
        bool empty();
    private:

        struct node;
        node* head;
        node* tail;
        u32 length;
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
        if(!n)
            tail = n;
        ++length;
        return t;
    }
    template <typename T>
    T queue<T>::pop()
    {
        if(length == 0)
            return;
        T t = head->data;
        node* n = head;
        head = head->next;
        delete n;
        if(--length == 0)
            tail == nullptr;
        return t;
    }

    template <typename T>
    bool queue<T>::empty()
    {
        return head == nullptr;
    }

}

#endif //SCARECROW2D_QUEUE_H
