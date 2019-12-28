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
    color = vec4(83.0/255.0f, 182.0/255.0f, 144.0/255.0f, 0.5f);
}
