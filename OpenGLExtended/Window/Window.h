#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OpenGLExt
{
	namespace Window
	{
		class Window
		{
		public:
			Window(GLFWwindow* window, intptr_t glContext, intptr_t windowContext);
			~Window();
		};
	}
}