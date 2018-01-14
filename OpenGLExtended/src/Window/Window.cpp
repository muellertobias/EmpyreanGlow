#include "Window.h"
#include <iostream>


namespace OpenGLExt
{
	namespace Window
	{
		Window::Window(std::shared_ptr<GLFWwindow> window, intptr_t glContext, intptr_t windowContext)
			: window(window), glContext(glContext), windowContext(windowContext)
		{
			glfwSetFramebufferSizeCallback(window.get(), [](GLFWwindow* wind, int width, int height) 
			{ 
				glViewport(0, 0, width, height); 
			});

			glfwSetMouseButtonCallback(window.get(), [](GLFWwindow* window, int button, int action, int mods) 
			{ 					
				double xpos, ypos;
				if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
				{
					glfwGetCursorPos(window, &xpos, &ypos);
					std::cout << "x=" << xpos << "; y=" << ypos << std::endl;
				}
			});

			glfwSetScrollCallback(window.get(), [](GLFWwindow* wind, double xoffset, double yoffset)
			{
				std::cout << "xoffset=" << xoffset << "; yoffset=" << yoffset << std::endl;
			});
		}

		Window::~Window()
		{
		}

		void Window::refresh()
		{
			glfwSwapBuffers(window.get());
			glfwPollEvents();
		}

		void Window::close()
		{
			glfwDestroyWindow(window.get());
			glfwTerminate();
		}
		bool Window::isClosed()
		{
			int flag = glfwWindowShouldClose(window.get());
			return flag != 0;
		}
	}
}