#version 330 core

uniform mat4 MVP;

layout(location = 0) in vec3 vertexPosition_modelspace;

void main()
{
    //gl_Position.xyz = vertexPosition_modelspace;
    //gl_Position.w = 1.0;

    // Output position of the vertex, in clip space
    gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
    //gl_Position =  MVP * vertexPosition_modelspace;
}

