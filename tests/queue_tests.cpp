//
// Created by novasurfer on 8/31/20.
//

#include "../src/collections/queue.h"
#include "doctest/doctest.h"
#include <queue>

TEST_CASE("queue-operations")
{
    sc2d::queue<int> q;

    for(int i = 0; i < 5; ++i) {
        q.push(i);
    }

    for(int i = 5; --i > 0;) {
        CHECK(q.front() == i);
        q.pop();
    }
}
