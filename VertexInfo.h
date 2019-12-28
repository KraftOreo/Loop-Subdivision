//
// Created by 姜糖 on 12/23/19.
//

#pragma once


#include "src/vender/glm/glm.hpp"
#include "src/vender/glm/gtc/matrix_transform.hpp"
#include <vector>
#include <set>

struct Vertex
{
    glm::vec3 coord;
    bool is_new_vertex = false;
};


struct Edge
{
    std::set<unsigned int> edge;
    void SetEdge(std::set<unsigned int> edge)
    {
        this->edge = edge;
    }
};

bool operator<(const Edge&edge1, const Edge&edge2)
{
    return edge1.edge < edge2.edge;
}

bool operator<(const glm::vec3&lhs, const glm::vec3&rhs)
{
    return std::tie(lhs.x,lhs.y,lhs.z) < std::tie(rhs.x,rhs.y,rhs.z);
}


bool operator<(const Vertex&v1, const Vertex&v2)
{
    return (v1.coord < v2.coord || (v1.coord == v2.coord && v1.is_new_vertex < v2.is_new_vertex));
}


bool operator==(const Edge &edge1, const Edge &edge2)
{
    return edge1.edge == edge2.edge;
}

struct Vertex_Indices
{
    unsigned int one;
    unsigned int two;
    unsigned int three;
    std::vector<Edge> triEdges;
    void match_edges()
    {
        Edge temp_edge [3];
        temp_edge[0].SetEdge(std::set<unsigned int>{this->one, this->two});
        temp_edge[1].SetEdge(std::set<unsigned int>{this->two, this->three});
        temp_edge[2].SetEdge(std::set<unsigned int>{this->one, this->three});
        for (const auto & i : temp_edge)
        {
            this->triEdges.push_back(i);
        }
    }
};