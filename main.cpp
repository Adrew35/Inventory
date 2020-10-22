#include <iostream>
#include <string>

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "display.h"
#include "rendering.h"

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

/*
TODO:: Rewrite shader system.

A ShaderProgram is a class that has two 'int's as handles (vert & frag),
and another as a 'program_id'. When you create a shader program, you pass
it the paths to the vertex and fragment shaders separately.
These are read and compiled into the vertex and fragment shaders.
The 'program_id' is linked after attaching the shaders, and deleting them afterwards.
During the render loop, for every entity in the scene (which will have a grouped shader 
that more that one entity uses at once), that entities variables are set as uniforms
in the program, and the program is 'glUseProgram'ed.

After the rendering for everything in that shader is done, reset to no program being used, and continue with the game logic.

All this will aim to be done on October 21st. I am too tired, and frustrated.
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

  new_shader_program flatshader;
  flatshader.compile("flatshade");
  glLinkProgram(flatshader.get_id());

  float position[3] = {0.0f, 0.0f, 0.0f};
  float rgba[4]     = {0.5f, 0.2f, 0.7f, 1.0f};
  flatshader.set_uniform_1f("testValue", 4);
  flatshader.set_uniform_3fv("position", position);
  flatshader.set_uniform_4fv("pixelColor", rgba);
  
  while(!glfwWindowShouldClose(win.handle))
    {
      // Ambient & background
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

      //TODO: Add this line to render loop.
      flatshader.bind();
      
      // Rendering and UI
      renderer.render_center_square();
      
      glUseProgram(0);

      // Input
      if(glfwGetKey(win.handle, GLFW_KEY_ESCAPE) && glfwGetKey(win.handle, GLFW_KEY_BACKSPACE))
	{ glfwSetWindowShouldClose(win.handle, true); }

      // Cleanup and/or glfw.
      glfwSwapBuffers(win.handle);
      glfwPollEvents();
    }

  glfwTerminate();
  return 0;
}
