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
					Window::_OnClick(window, xpos, ypos);
				}
			});

			glfwSetScrollCallback(this->window.get(), [](GLFWwindow* wind, double xoffset, double yoffset)
			{
				Window::_OnScroll(wind, yoffset);
			});
		}

		void Window::_OnClick(GLFWwindow* nativeWindow, double xpos, double ypos)
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

		void Window::_OnWindowSizeChanged(GLFWwindow * nativeWindow, int width, int height)
		{
			for (std::list<Window*>::iterator it = Window::openedWindows.begin(); it != Window::openedWindows.end(); it++)
			{
				if ((*it)->window.get() == nativeWindow)
				{
					std::cout << "width=" << width << "; height=" << height << std::endl;
					(*it)->windowSizeChangedallback(width, height);
				}
			}
		}

		void Window::_OnScroll(GLFWwindow * nativeWindow, short scrollDir)
		{
			for (std::list<Window*>::iterator it = Window::openedWindows.begin(); it != Window::openedWindows.end(); it++)
			{
				if ((*it)->window.get() == nativeWindow)
				{
					double xpos, ypos;
					glfwGetCursorPos(nativeWindow, &xpos, &ypos);

					std::cout << "scrollDir=" << scrollDir  << std::endl;
					std::cout << "x=" << xpos << "; y=" << ypos << std::endl;

					(*it)->scrollCallback(scrollDir, xpos, ypos);
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