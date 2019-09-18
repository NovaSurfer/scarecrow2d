//
// Created by Maksim Ruts on 18/09/2019.
//

#ifndef SCARECROW2D_QUADTREE_H
#define SCARECROW2D_QUADTREE_H
#include "geometry2d.h"
#include <vector>

namespace math
{

    struct QuadTreeData
    {
        void* object;
        rect2d bounds;
        bool flag;

        QuadTreeData(void* obj, const rect2d& rect)
            : object(obj)
            , bounds(rect)
            , flag(false)
        {}
    };

    class QuadTreeNode
    {
    public:
        explicit QuadTreeNode(const rect2d& bounds)
            : node_bounds(bounds)
            , current_depth(0) {};

        bool is_leaf();
        size_t size();
        void insert(QuadTreeData& data);
        void remove(QuadTreeData& data);
        void update(QuadTreeData& data);
        void snake();
        void split();
        void reset();
        std::vector<QuadTreeData*> query(const rect2d& area);

    private:
        std::vector<QuadTreeNode> childrens;
        std::vector<QuadTreeData*> content;
        rect2d node_bounds;
        size_t current_depth;
        static size_t max_depth;
        static size_t max_depth_per_node;
    };
};
#endif //SCARECROW2D_QUADTREE_H
