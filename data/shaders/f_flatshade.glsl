#version 330 core

out vec4 FragColour;

uniform vec4 pixelColor;

void main()
{
  FragColour = pixelColor;
};
