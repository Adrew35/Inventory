#include <iostream>
#include <string>

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "display.h"
#include "rendering.h"
#include "shader.h"

static bool debug = false;

/*
  
  Map of program:

  -- Display
  -- Input callbacks
  -- Rendering (2d game, will only have one mesh, a square)
  -- entities in a scene
  -- Input affects entities in scene
  -- UI components
  -- Gameplay loop / logic.

 */

void parse_commands(int count, char* args[])
{
  std::string command;
  for(int i = 0; i != count; ++i)
    {
      command = args[i];
      if(command == "-debug" || command == "-d")
	{
	  std::cout << "[Launch] : Starting in _Debug." << std::endl;
	  debug = true;
	}
      else
	{
	  debug = false;
	}
    }
}

int main(int argc, char* argv[])
{
  parse_commands(argc, argv);
  
  gameWindow win(1280, 720, 0, false, "Project");
  win.open();
  win.loadGL();

  render_manager renderer;
  renderer.setup_backend();

  shader_program flatShader;
  flatShader.create_from_file("flatshade");

  std::string uniform_name = "test";
  int location = glGetUniformLocation(flatShader.program_id, uniform_name.c_str());
  glUniform1f(location, 4);

  std::string uniform_positionName = "position";
  std::string uniform_pixelColorName = "_pixelColor";
  std::string testName = "test";
  int pixelLocation = glGetUniformLocation(flatShader.program_id, uniform_pixelColorName.c_str());
  int positionLocation = glGetUniformLocation(flatShader.program_id, uniform_positionName.c_str());
  int testLocation = glGetUniformLocation(flatShader.program_id, testName.c_str());
  if(testLocation < 0)
    { std::cout << "Test returned negative." << std::endl; return -1; }

  if(pixelLocation < 0)
    { std::cout << "PixelColor return negative." << std::endl; return -1; }
  if(positionLocation < 0)
    { std::cout << "Position returned negative." << std::endl; return -1; }

  float pixelColour[4] = { 0.2f, 0.1f, 0.5f, 1.0f };
  float position[4]    = { 0.0f, 0.0f, 0.0f, 1.0f };

  glUniform4fv(pixelLocation, 1, pixelColour);
  glUniform4fv(positionLocation, 1, position);

  flatShader.bind();
  while(!glfwWindowShouldClose(win.handle))
    {
      // Ambient & background
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

      flatShader.bind();
      // Rendering and UI
      renderer.render_center_square();
      
      // Input
      if(glfwGetKey(win.handle, GLFW_KEY_ESCAPE) && glfwGetKey(win.handle, GLFW_KEY_BACKSPACE))
	{ glfwSetWindowShouldClose(win.handle, true); }

      flatShader.unbind();
      // Cleanup and/or glfw.
      glfwSwapBuffers(win.handle);
      glfwPollEvents();
    }

  glfwTerminate();
  return 0;
}
