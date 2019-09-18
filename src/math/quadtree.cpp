//
// Created by Maksim Ruts on 18/09/2019.
//

#include "quadtree.h"
#include <queue>
namespace math
{
    size_t QuadTreeNode::max_depth = 5;
    size_t QuadTreeNode::max_depth_per_node = 15;

    bool QuadTreeNode::is_leaf()
    {
        return childrens.size() == 0;
    }

    size_t QuadTreeNode::size()
    {
        reset();
        size_t object_count = content.size();

        for(size_t i = 0; i < object_count; ++i) {
            content[i]->flag = true;
        }

        std::vector<QuadTreeNode*> process;
        process.emplace_back(this);

        while(process.size() > 0) {
            QuadTreeNode* processing = process.back();
            if(!processing->is_leaf()) {
                for(auto& children : processing->childrens) {
                    process.emplace_back(&children);
                }
            } else {
                for(auto& c : processing->content) {
                    if(!c->flag) {
                        c->flag = true;
                        object_count++;
                    }
                }
            }
            process.erase(process.begin());
        }
        reset();
        return object_count;
    }

    void QuadTreeNode::insert(QuadTreeData& data) {}
    void QuadTreeNode::remove(QuadTreeData& data) {}
    void QuadTreeNode::update(QuadTreeData& data) {}
    void QuadTreeNode::snake() {}
    void QuadTreeNode::split() {}
    void QuadTreeNode::reset() {}

    std::vector<QuadTreeData*> QuadTreeNode::query(const rect2d& area)
    {
        return std::vector<QuadTreeData*>();
    }
}
