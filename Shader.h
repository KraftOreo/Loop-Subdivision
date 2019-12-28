//
// Created by 姜糖 on 10/18/19.
//

#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glew.h>
#include <glfw3.h>
#include <unordered_map>
#include "Assert.h"
#include "src/vender/glm/glm.hpp"
struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSoruce;
    std::unordered_map<std::string, int> m_UniformLocationCache;
};


class Shader
{
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    //caching for uniforms
    std::unordered_map<std::string, int > m_UniformLocationCache;
public:
    Shader(const std::string&file_path);
    ~Shader();
    void Bind() const;
    void Unbind() const;

    //Set uniforms￿￿￿
    void SetUniform4f(const std::string&name, float v0, float v1, float v2, float v3);
    void SetUniform1f(const std::string&name, float value);
    void SetUniform1i(const std::string&name, int value);
    void SetUniformMat4f(const std::string&name, const glm::mat4& mat);

private:
    GLint GetUniformLocation(const std::string &name);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    ShaderProgramSource ParseShader(const std::string& file_path);
};

//#endif //GRAPHICS_SHADER_H
