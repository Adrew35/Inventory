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
}

new_shader_program::~new_shader_program()
{}

bool new_shader_program::compile(const std::string& name)
{
  std::string vertFilePath = "v_" + name + ".glsl";
  std::string fragFilePath = "f_" + name + ".glsl";
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
  
}

void new_shader_program::dump_source()
{
  std::cout << "V_Shader Code:\n" << source[0];
  std::cout << "F_Shader Code:\n" << source[1];
}

shader_program::shader_program()
{ program_id = glCreateProgram(); }

shader_program::~shader_program()
{}

int shader_program::create_from_file(const std::string& shader_name)
{
  std::string vertPath = "data/shaders/v_" + shader_name + ".glsl";
  std::string fragPath = "data/shaders/f_" + shader_name + ".glsl";
  std::fstream vertFile(vertPath);
  std::fstream fragFile(fragPath);
  
  if(!vertFile)
    {
      std::cout << "[ERR] : Failed to load vertex shader file." << std::endl;
      return -1;
    }
  if(!fragFile)
    {
      std::cout << "[ERR] : Failed to load fragment shader file." << std::endl;
      return -1;
    }

  vert.handle = glCreateShader(GL_VERTEX_SHADER);
  frag.handle = glCreateShader(GL_FRAGMENT_SHADER);

  const char* source;               // Usable source.
  std::string newSource;            // Readable source.
  std::stringstream raw_source;     // Source straight from file.
  vertFile >> raw_source.rdbuf();   // Read file.
  newSource = { raw_source.str() }; // Put source in readable format.
  source = newSource.c_str();       // Put readable source into usable format.
  vert.source_code = source;        // backup/legacy.

  glShaderSource(vert.handle, 1, &source, 0); // Add source to shader.
  glCompileShader(vert.handle);               // Compile the shader.

  int comp;
  glGetShaderiv(vert.handle, GL_COMPILE_STATUS, &comp);
  if (comp == GL_FALSE)
    {
      std::cout << "[Compile Error] : Vertex Shader." << std::endl;
      int maxLength = 0;
      glGetShaderiv(vert.handle, GL_INFO_LOG_LENGTH, &maxLength);
      
      std::vector<char> errorLog(maxLength);
      glGetShaderInfoLog(vert.handle, maxLength, &maxLength, &errorLog[0]);
      
      std::cout << &errorLog[0] << std::endl;
      
      glDeleteShader(vert.handle);
      return -1;
    }

  const char* fragSource;
  std::string newFragSource;
  std::stringstream rawFragSource;
  fragFile >> rawFragSource.rdbuf();
  newFragSource = { rawFragSource.str() };
  fragSource = newFragSource.c_str();
  frag.source_code = fragSource;

  glShaderSource(frag.handle, 1, &fragSource, 0);
  glCompileShader(frag.handle);

  glGetShaderiv(frag.handle, GL_COMPILE_STATUS, &comp);
  if (comp == GL_FALSE)
    {
      std::cout << "[Compile Error] : Vertex Shader." << std::endl;
      int maxLength = 0;
      glGetShaderiv(frag.handle, GL_INFO_LOG_LENGTH, &maxLength);
      
      std::vector<char> errorLog(maxLength);
      glGetShaderInfoLog(frag.handle, maxLength, &maxLength, &errorLog[0]);
      
      std::cout << &errorLog[0] << std::endl;
      
      glDeleteShader(frag.handle);
      return -1;
    }

  glAttachShader(program_id, vert.handle);
  glAttachShader(program_id, frag.handle);
  glLinkProgram(program_id);
  glDetachShader(program_id, vert.handle);
  glDetachShader(program_id, frag.handle);
  glDeleteShader(vert.handle);
  glDeleteShader(frag.handle);
  
  return 0;
}

void shader_program::bind()
{ glUseProgram(program_id); }

void shader_program::unbind()
{ glUseProgram(0); }

// TODO: Not able to find unifor "_vPos" in vertex shader.
int shader_program::get_uniform_location(const std::string& _name)
{
  std::cout << "[Update] : Searching for uniform <" << _name.c_str() << ">\n";
  int location = glGetUniformLocation(program_id, _name.c_str());
  if(location < 0)
    {
      std::cout << "[ERR] : Failed to locate shader uniform (" << _name << ")." << std::endl;
      return -1;
    }

  std::cout << "Found uniform <" << _name << "> at location " << location << "." << std::endl;
  return location;
}

void shader_program::set_uniform3fv(const std::string& _name, float values[3])
{
  int location = get_uniform_location(_name);
  glUniform3fv(location, 1, values);
}

void shader_program::set_uniform4fv(const std::string& _name, float values[4])
{
  int location = get_uniform_location(_name);
  glUniform4fv(location, 1, values);
}

void shader_program::set_uniform1f(const std::string& _name, float value)
{
  int location = get_uniform_location(_name);
  glUniform1f(location, value);
}
