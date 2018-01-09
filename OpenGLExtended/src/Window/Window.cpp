#include "Window.h"

namespace OpenGLExt
{
	namespace Window
	{
		Window::Window(std::shared_ptr<GLFWwindow> window, intptr_t glContext, intptr_t windowContext)
			: window(window), glContext(glContext), windowContext(windowContext)
		{
			glfwSetFramebufferSizeCallback(window.get(), [](GLFWwindow* wind, int width, int height) { glViewport(0, 0, width, height); });
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