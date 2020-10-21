#pragma once

#ifndef SHADER_H
#define SHADER_H
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "glad/glad.h"

class new_shader_program
{
public:
  new_shader_program();  // Calls gl creation for program and shaders.
  ~new_shader_program();

  bool compile(const std::string& name);
  void dump_source();
  
private:
  std::string source[2];
  int program_id, vert, frag;
};

struct shader_handle
{
  shader_handle()
  { handle = 0; source_code = ""; }
  
  uint32_t handle;

  std::string source_code;
};

class shader_program
{
 public: 
  shader_program();
  ~shader_program();

  // Call twice, once for 'GL_VERTEX_SHADER' and once for 'GL_FRAGMENT_SHADER'
  int create_from_file(const std::string& path);

  void bind();
  void unbind();

  int get_uniform_location(const std::string& _name);
  void set_uniform3fv(const std::string& _name, float values[3]);
  void set_uniform4fv(const std::string& _name, float values[4]);

  void set_uniform1f(const std::string& _name, float value);
  
  uint32_t program_id;
  
 private: 
  shader_handle vert, frag;
}; 
