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

  bool compile(const std::string& name); // Compile from files.
  // Filepaths are generated using the given name.

  void bind()
  { glUseProgram(program_id); }

  int get_id()
  { return program_id; }

  int get_uniform_location(int program_id, const std::string& _name)
  {
    int location = glGetUniformLocation(program_id, _name.c_str());
    if(location < 0)
      {
	std::cout << "[ERR] : Failed to locate uniform <" << _name << ">\n";
	return -1;
      }
    return location;
  }

  void set_uniform_1f(int program_id, const std::string& _name, float value)
  {
    int location = get_uniform_location(program_id, _name);
    glUniform1f(location, value);
  }
  
  void set_uniform_4fv(int program_id, const std::string& _name, float value[4])
  {
    int location = get_uniform_location(program_id, _name);
    glUniform4fv(location, 1, value);
  }
  
private:
  int program_id, vert, frag;
};


