#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
out vec2 TexCoord;
uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
    color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
