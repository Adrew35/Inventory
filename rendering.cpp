#include <iostream>
#include <string>
#include <vector>

#include "glad/glad.h"

#include "rendering.h"

render_manager::render_manager()
{}

render_manager::~render_manager()
{}

void render_manager::setup_backend()
{
  glGenVertexArrays(1, &square.vao);
  glGenBuffers(2, square.vbo);

  glBindVertexArray(square.vao);
  glBindBuffer(GL_ARRAY_BUFFER, square.vbo[0]);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, square.vbo[1]);

  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, square.vPos, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, square.indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void render_manager::render_center_square()
{
  glBindVertexArray(square.vao);
  glBindBuffer(GL_ARRAY_BUFFER, square.vbo[1]);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, square.indices);

  glBindVertexArray(0);
}
