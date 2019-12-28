//
// Created by 姜糖 on 12/23/19.
//
#pragma once


#include "src/vender/glm/glm.hpp"
#include "src/vender/glm/gtc/matrix_transform.hpp"
#include <vector>
#include <string>
#include "VertexInfo.h"


bool loadOBJ(const char *path, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs,
             std::vector<glm::vec3> &out_normals, std::vector<unsigned int> &out_indices,
             std::vector<unsigned int> &uv_indices, std::vector<Vertex_Indices> & triangles)
{
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;
    FILE *file = fopen(path, "r");
    if (file == nullptr)
    {
        printf("Impossib11le to open the file !\n");
        return false;
    }

    while (true)
    {

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
        {

            break; // EOF = End Of File. Quit the loop.
        }
        if (strcmp(lineHeader, "v") == 0)
        {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        } else if (strcmp(lineHeader, "vt") == 0)
        {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        } else if (strcmp(lineHeader, "vn") == 0)
        {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        } else if (strcmp(lineHeader, "f") == 0)
        {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                 &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2],
                                 &normalIndex[2]);

            if (matches != 9)
            {
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
            out_indices.push_back(vertexIndex[0] - 1);
            out_indices.push_back(vertexIndex[1] - 1);
            out_indices.push_back(vertexIndex[2] - 1);
            Vertex_Indices tri;
            tri.one = vertexIndex[0] - 1;
            tri.two = vertexIndex[1] - 1;
            tri.three = vertexIndex[2] - 1;
            tri.match_edges();
            triangles.push_back(tri);

        }
        out_vertices = temp_vertices;
        out_uvs = temp_uvs;
        uv_indices = uvIndices;
    }

    return true;
}
