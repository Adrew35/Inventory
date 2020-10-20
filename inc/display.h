#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H
#endif

#include <iostream>
#include <string>

#include "glad/glad.h"
#include "glfw/glfw3.h"

struct gameWindow
{
  uint32_t width, height, samples;
  bool resize; const char* title;
  GLFWwindow* handle;

  gameWindow() {}
  gameWindow(int _width, int _height, int _samples, bool _resize, const std::string& _title)
  {
    width = _width;
    height = _height;
    samples = _samples;
    resize = _resize;
    title = _title.c_str();
  }

  int open()
  {
    if(!glfwInit())
      {
	std::cout << "[ERR] : Failed to initialize glfw." << std::endl;
	return -1;
      }

    glfwWindowHint(GLFW_SAMPLES, samples);
    glfwWindowHint(GLFW_RESIZABLE, resize);

    handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if(!handle)
      {
	std::cout << "[ERR] : Failed to open window." << std::endl;
	glfwTerminate();
	return -1;
      }
    glfwMakeContextCurrent(handle);
    return 0;
  }

  int loadGL()
  {
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
      {
	std::cout << "[ERR] : Failed to load glad." << std::endl;
	return -1;
      }
    return 0;
  }
};
