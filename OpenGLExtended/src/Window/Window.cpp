#include "Window.h"
#include <iostream>

namespace OpenGLExt
{
	namespace Windows
	{
		std::list<Window*> Window::openedWindows;

		Window::Window(std::shared_ptr<GLFWwindow> window, intptr_t glContext, intptr_t windowContext)
			: window(window), glContext(glContext), windowContext(windowContext)
		{
			init();
			Window::openedWindows.push_back(this);
		}

		void Window::init()
		{
			glfwSetFramebufferSizeCallback(this->window.get(), [](GLFWwindow* wind, int width, int height)
			{
				glViewport(0, 0, width, height);
			});

			glfwSetMouseButtonCallback(this->window.get(), [](GLFWwindow* window, int button, int action, int mods)
			{
				double xpos, ypos;
				if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
				{
					glfwGetCursorPos(window, &xpos, &ypos);
					Window::_OnCursorPositionChanged(window, xpos, ypos);
				}
			});

			glfwSetScrollCallback(this->window.get(), [](GLFWwindow* wind, double xoffset, double yoffset)
			{
				std::cout << "xoffset=" << xoffset << "; yoffset=" << yoffset << std::endl;
			});
		}

		void Window::_OnCursorPositionChanged(GLFWwindow* nativeWindow, double xpos, double ypos)
		{
			for (std::list<Window*>::iterator it = Window::openedWindows.begin(); it != Window::openedWindows.end(); it++)
			{
				if ((*it)->window.get() == nativeWindow)
				{
					std::cout << "x=" << xpos << "; y=" << ypos << std::endl;
					(*it)->clickCallback(xpos, ypos);
				}
			}
		}

		Window::~Window()
		{
			Window::openedWindows.remove(this);
			close();
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