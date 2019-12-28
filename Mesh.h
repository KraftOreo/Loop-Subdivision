//
// Created by 姜糖 on 12/23/19.
//

#pragma once

#include "src/vender/glm/glm.hpp"
#include "src/vender/glm/gtc/matrix_transform.hpp"
#include <vector>
#include <set>
#include <algorithm>
#include "ObjLoader.h"
#include "VertexInfo.h"
#include <map>
#include <iostream>

class Mesh
{
public:
    Mesh(std::vector<glm::vec3> &out_vertices, std::vector<Vertex_Indices> &out_indices) : triangles(out_indices)
    {
        for (int i = 0; i < out_vertices.size(); i++)
        {
            Vertex temp;
            temp.coord = out_vertices[i];
            vertices.push_back(temp);
            Mapping.insert(std::pair<Vertex, unsigned int>(temp, i));
        }

        match_edges();
    }

    void match_edges()
    {
        previous_edges = edges;
        std::cout << "edge size " << edges.size() << std::endl;
        std::vector<Edge> newEdge;
        for (const auto &vid : triangles)
        {
            Edge temp_edge[3];
            temp_edge[0].SetEdge(std::set<unsigned int>{vid.one, vid.two});
            temp_edge[1].SetEdge(std::set<unsigned int>{vid.two, vid.three});
            temp_edge[2].SetEdge(std::set<unsigned int>{vid.one, vid.three});
            for (auto &te : temp_edge)
            {
                if (map_edge.find(te) == map_edge.end())
                {
                    newEdge.push_back(te);
                    map_edge[te] = newEdge.size() - 1;
                }
            }
        }
        this->edges = newEdge;
        std::cout << "edge size " << edges.size() << std::endl;
    }


    void Split()
    {
        std::vector<Vertex_Indices> new_triangles;
        previous_triangles = triangles;
        this->previous_vertices = vertices;
        for (const auto &triangle : triangles)
        {
            Vertex newVertex4, newVertex5, newVertex6;
            unsigned int one, two, three, four, five, six;
            one = triangle.one;
            two = triangle.two;
            three = triangle.three;
            newVertex4.is_new_vertex = true;
            newVertex4.coord = (vertices[one].coord + vertices[two].coord) / 2.0f;
            if (Mapping.find(newVertex4) == Mapping.end())
            {
                vertices.push_back(newVertex4);
                Mapping[newVertex4] = vertices.size() - 1;
                four = vertices.size() - 1;
            } else
            {
                four = Mapping[newVertex4];
            }


            newVertex5.is_new_vertex = true;
            newVertex5.coord = (vertices[two].coord + vertices[three].coord) / 2.0f;
            if (Mapping.find(newVertex5) == Mapping.end())
            {
                vertices.push_back(newVertex5);
                Mapping[newVertex5] = vertices.size() - 1;
                five = vertices.size() - 1;
            } else
            {
                five = Mapping[newVertex5];
            }

            newVertex6.is_new_vertex = true;
            newVertex6.coord = (vertices[one].coord + vertices[three].coord) / 2.0f;
            if (Mapping.find(newVertex6) == Mapping.end())
            {
                vertices.push_back(newVertex6);
                Mapping[newVertex6] = vertices.size() - 1;
                six = vertices.size() - 1;
            } else
            {
                six = Mapping[newVertex6];
            }

            Vertex_Indices newTri1, newTri2, newTri3, newTri4;
            newTri1.one = one;
            newTri1.two = four;
            newTri1.three = six;
            newTri1.match_edges();


            newTri2.one = four;
            newTri2.two = two;
            newTri2.three = five;
            newTri2.match_edges();

            newTri3.one = four;
            newTri3.two = five;
            newTri3.three = six;
            newTri3.match_edges();

            newTri4.one = five;
            newTri4.two = three;
            newTri4.three = six;
            newTri4.match_edges();

            new_triangles.push_back(newTri1);
            new_triangles.push_back(newTri2);
            new_triangles.push_back(newTri3);
            new_triangles.push_back(newTri4);
        }
        this->triangles = new_triangles;
    }

    void UpdateLocation()
    {
        std::vector<Vertex> new_Vertex;
        // old vertices
        for (unsigned int i = 0; i < previous_vertices.size(); ++i)
        {
            std::set<unsigned int> periphery;
            for (const auto & e : previous_edges)
            {
                for (auto & it : e.edge)
                {
                    if (e.edge.find(i) != e.edge.end())
                    {
                        periphery.insert(it);
                    }
                }
            }
            int n = periphery.size();
            float weight;
            if (n==3)
            {
                weight = (float)(3.0f / 16.0f) ;
            }
            else
            {
                weight = (float) (3.0f / (n * 8.0f));
            }
            glm::vec3 coord = vertices[i].coord * (1 - n * weight);
            for (auto &it : periphery)
            {
                coord += weight * vertices[it].coord;
            }
            new_Vertex.push_back({coord, false});
        }
        // new vertices
        for (unsigned int j = previous_vertices.size(); j < vertices.size(); ++j)
        {
            // find the two old vertices near the vertices[j]
            std::set<unsigned int> periphery;
            glm::vec3 coord = glm::vec3(0.0f, 0.0f, 0.0f);
            for (const auto & e : edges)
            {
                if (e.edge.find(j) != e.edge.end())
                {
                    for (auto & it : e.edge)
                    {
                        if (it != j)
                        {
                            if (!vertices[it].is_new_vertex)
                            {
                                periphery.insert(it);
                                coord += (float) (3.0 / 8.0) * vertices[it].coord;
                            }
                        }
                    }
                }
            }
            Edge peripheryEdge;
            peripheryEdge.SetEdge(periphery);
            // find the two old triangles which contain the edge make up by the two vertex in periphery
            std::vector<Vertex_Indices> nearTriangles;
            for (const auto &triangle : previous_triangles)
            {
                for (auto & it : triangle.triEdges)
                {
                    if (it == peripheryEdge) nearTriangles.push_back(triangle);
                }

            }
            std::set<unsigned int> pointsIndices = {nearTriangles[0].one, nearTriangles[0].two, nearTriangles[0].three,
                                                    nearTriangles[1].one, nearTriangles[1].two, nearTriangles[1].three};
            // another two vertices not near the central vertex
            std::set<unsigned int> nonAdjacent;
            std::set_difference(pointsIndices.begin(), pointsIndices.end(), periphery.begin(), periphery.end(),
                                std::inserter(nonAdjacent, nonAdjacent.end()));
            for (auto & it : nonAdjacent)
            {
                coord += (float) (1.0 / 8.0) * vertices[it].coord;
            }

            new_Vertex.push_back({coord, false});
        }
        vertices = new_Vertex;
    }

    auto GetEdges()
    { return edges; }

    float *GetVertices()
    {
        int n = vertices.size();
        auto *vert = new float[3 * n];
        for (int i = 0; i < n; ++i)
        {
            vert[3 * i] = vertices[i].coord.x;
            vert[3 * i + 1] = vertices[i].coord.y;
            vert[3 * i + 2] = vertices[i].coord.z;
        }
        return vert;
    }

    unsigned int *GetIndicies()
    {
        int count = triangles.size();


        auto *indices = new unsigned int[3 * count];

        for (int j = 0; j < count; ++j)
        {
            indices[3 * j] = triangles[j].one;
            indices[3 * j + 1] = triangles[j].two;
            indices[3 * j + 2] = triangles[j].three;
        }
        return indices;
    }

    int GetVerticesSize()
    { return vertices.size(); }

    int GetIndicesSize()
    { return triangles.size() * 3; }

    int GetMappingSize()
    {
        return Mapping.size();
    }

    void Subdivision()
    {
        Split();
        match_edges();
        UpdateLocation();
    }

private:
    std::vector<Vertex> vertices;
    std::vector<Vertex> previous_vertices;
    std::vector<Vertex_Indices> triangles;
    std::vector<Edge> edges;
    std::vector<Edge> previous_edges;
    std::vector<Vertex_Indices> previous_triangles;
    std::map<Edge, int> map_edge;
    std::map<Vertex, unsigned int> Mapping;
};

