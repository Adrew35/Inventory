#version 330

uniform vec3 position;
uniform float testValue;

void main()
{
  position = vec3(0, 0, 0);
  gl_Position = vec4(position, 1);
}
