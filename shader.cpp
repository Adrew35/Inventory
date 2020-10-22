#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "glad/glad.h"

#include "shader.h"

new_shader_program::new_shader_program()
{
  program_id = glCreateProgram();
  vert = glCreateShader(GL_VERTEX_SHADER);
  frag = glCreateShader(GL_FRAGMENT_SHADER);

  std::cout << "Created Program: (handle)" << program_id << std::endl;
  std::cout << "Created Shader: (handle)" << vert << std::endl;
  std::cout << "Created Shader: (handle)" << frag << std::endl << std::endl;
}

new_shader_program::~new_shader_program()
{}

bool new_shader_program::compile(const std::string& name)
{
  std::string vertFilePath = "data/shaders/v_" + name + ".glsl";
  std::string fragFilePath = "data/shaders/f_" + name + ".glsl";
  std::fstream vertFile(vertFilePath);
  std::fstream fragFile(fragFilePath);

  if(!vertFile)
    { std::cout << "[ERR] : Failed to open vertex shader." << std::endl; return false; }
  if(!fragFile)
    { std::cout << "[ERR] : failed to open fragment shader." << std::endl; return false; }

  std::stringstream rawSource;
  const char* source;
  std::string sourceBuffer;
  vertFile >> rawSource.rdbuf();
  sourceBuffer = {rawSource.str()};
  source = sourceBuffer.c_str();
  
  glShaderSource(1, vert, &source, 0);
  glCompileShader(vert);

  int comp;
  glGetShaderiv(vert, GL_COMPILE_STATUS, &comp);
  if (comp == GL_FALSE)
    {
      std::cout << "[Compile Error] : Vertex Shader." << std::endl;
      int maxLength = 0;
      glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &maxLength);
      
      std::vector<char> errorLog(maxLength);
      glGetShaderInfoLog(vert, maxLength, &maxLength, &errorLog[0]);
      
      std::cout << &errorLog[0] << std::endl;
      
      glDeleteShader(vert);
      return false;
    }

  rawSource = std::stringstream();
  source = "";
  fragFile >> rawSource.rdbuf();
  sourceBuffer = {rawSource.str()};
  source = sourceBuffer.c_str();
  
  glShaderSource(1, frag, &source, 0);
  glCompileShader(frag);

  glGetShaderiv(frag, GL_COMPILE_STATUS, &comp);
  if (comp == GL_FALSE)
    {
      std::cout << "[Compile Error] : Fragment Shader." << std::endl;
      int maxLength = 0;
      glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &maxLength);
      
      std::vector<char> errorLog(maxLength);
      glGetShaderInfoLog(frag, maxLength, &maxLength, &errorLog[0]);
      
      std::cout << &errorLog[0] << std::endl;
      
      glDeleteShader(frag);
      return -1;
    }

  glAttachShader(program_id, vert); glAttachShader(program_id, frag);
  glLinkProgram(program_id);
  glDeleteShader(vert); glDeleteShader(frag);
  
  return true;
}

