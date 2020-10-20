#pragma once

#ifndef RENDERING_H
#define RENDERING_H
#endif

#include <iostream>
#include <string>
#include <vector>

#include "glad/glad.h"

#include "math.h"
#include "shader.h"

struct mesh
{
  mesh()
  { vao = 0; vbo[0] = 0; vbo[1] = 0; }
  
  uint32_t vao, vbo[2];
  float vPos[8] = {
		   -0.5f, -0.5f,
		   -0.5f,  0.5f,
		    0.5f,  0.5f,
		    0.5f, -0.5f
                  };
  unsigned int indices[6] = { 0, 1, 2, 2, 0, 3 };
};

class render_manager
{
 public:
  render_manager();
  ~render_manager();

  void setup_backend();
  void render_center_square();

  // <entities>
 private:
  mesh square;
};
