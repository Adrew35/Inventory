#version 330 core

#extension GL_ARB_explicit_uniform_location : enable

out vec4 FragColour;

layout(location = 1) uniform vec4 _pixelColor;

void main()
{
  FragColour = _pixelColor;
};
