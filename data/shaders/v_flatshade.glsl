#version 330 core

#extension GL_ARB_explicit_uniform_location : enable

layout(location = 0) uniform vec4 _vPos;

void main()
{
  //gl_Position = vec4(vertex_position, 1.0);
}
