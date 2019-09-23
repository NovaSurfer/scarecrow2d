//
// Created by Maksim Ruts on 18/09/2019.
//

#include "quadtree.h"
#include "physics/collision2d.h"
#include <queue>
namespace math
{
    size_t QuadTreeNode::max_depth = 5;
    size_t QuadTreeNode::max_objects_per_node = 15;

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
        // Adds current node to the vector with each node
        process.emplace_back(this);

        // For each node in 'process' vector
        while(process.size() > 0) {
            QuadTreeNode* processing = process.back();
            // If current node, that we are checking, is 'leaf'
            if(!processing->is_leaf()) {
                for(auto& children : processing->childrens) {
                    // push each children of 'leaf' node to 'process' vector
                    process.emplace_back(&children);
                }
            } else {
                // If not, increment 'object_count' for each node's 'content'
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

    void QuadTreeNode::insert(QuadTreeData& data)
    {
        if(!physics::collision2d::rectangle_rectangle(data.bounds, node_bounds))
            return;
        if(is_leaf() && content.size() + 1 > max_objects_per_node)
            split();
        if(is_leaf())
            content.push_back(&data);
        else
            for(auto& children : childrens)
                children.insert(data);
    }

    void QuadTreeNode::remove(QuadTreeData& data)
    {
        if(is_leaf()) {
            int remove_index = -1;
            for(size_t i = 0; i < content.size(); ++i) {
                if(content[i]->object == data.object) {
                    remove_index = i;
                    break;
                }
            }
            if(remove_index != -1)
                content.erase(content.begin() + 1);
        } else {
            for(auto& child : childrens)
                child.remove(data);
        }
        snake();
    }

    void QuadTreeNode::update(QuadTreeData& data)
    {
        remove(data);
        insert(data);
    }

    void QuadTreeNode::snake()
    {
        if(!is_leaf()) {
            size_t num_objs = size();
            if(num_objs == 0)
                childrens.clear();
            else if(num_objs < max_objects_per_node) {
                std::vector<QuadTreeNode*> process;
                process.emplace_back(this);
                while(process.size() > 0) {
                    QuadTreeNode* processing = process.back();
                    if(!processing->is_leaf()) {
                        for(size_t i = 0; i < childrens.size(); ++i) {
                            process.emplace_back(&processing->childrens[i]);
                        }
                    } else {
                        content.insert(content.end(), processing->content.begin(),
                                       processing->content.end());
                    }
                    process.erase(process.begin());
                }
                childrens.clear();
            }
        }
    }

    void QuadTreeNode::split()
    {
        if(current_depth + 1 >= max_depth)
            return;

        vec2 min = rect2d::get_min(node_bounds);
        vec2 max = rect2d::get_max(node_bounds);
        vec2 center = min + ((max - min) * 0.5f);

        rect2d child_areas[] {rect2d::from_min_max({min.x, min.y}, {center.x, center.y}),
                              rect2d::from_min_max({center.x, min.y}, {max.x, center.y}),
                              rect2d::from_min_max({center.x, center.y}, {max.x, max.y}),
                              rect2d::from_min_max({min.x, center.y}, {center.x, max.y})};

        childrens.emplace_back(QuadTreeNode(child_areas[0]));
        childrens[0].current_depth =  current_depth + 1;
        childrens.emplace_back(QuadTreeNode(child_areas[1]));
        childrens[1].current_depth =  current_depth + 1;
        childrens.emplace_back(QuadTreeNode(child_areas[2]));
        childrens[2].current_depth =  current_depth + 1;
        childrens.emplace_back(QuadTreeNode(child_areas[3]));
        childrens[3].current_depth =  current_depth + 1;

        for(size_t i = 0; i < content.size(); ++i) {
            childrens[i].insert(*content[i]);
        }

        content.clear();
    };

    void QuadTreeNode::reset()
    {
        if(is_leaf()) {
            for(auto& c : content)
                c->flag = false;
        } else {
            for(auto& c : childrens)
                c.reset();
        }
    }

    std::vector<QuadTreeData*> QuadTreeNode::query(const rect2d& area)
    {
        if(!physics::collision2d::rectangle_rectangle(area, node_bounds))
            return {};

        std::vector<QuadTreeData*> result;
        if(is_leaf())
        {
            for(auto& c : content)
                if(physics::collision2d::rectangle_rectangle(c->bounds, area))
                    result.emplace_back(c);
        } else {
            for(auto& c : childrens) {
                auto recurse = c.query(area);
                if(!recurse.empty()) {
                    result.insert(result.end(), recurse.begin(), recurse.end());
                }
            }
        }
        return  result;
    }
}
