#pragma once

#ifndef MATH_H
#define MATH_H
#endif

struct vec2f
{
  vec2f()
  { x = 0; y = 0; }
  vec2f(float newX, float newY)
  {
    x = newX;
    y = newY;
  }

  float x, y;
};

struct transform2d
{
  transform2d()
  {}

  transform2d(vec2f newPos, vec2f newRot, vec2f newScale)
  {
    position.x = newPos.x; position.y = newPos.y;
    rotation.x = newRot.x; rotation.y = newRot.y;
    scale.x = newScale.x; scale.y = newScale.y;
  }

  vec2f position;
  vec2f rotation;
  vec2f scale;
};
