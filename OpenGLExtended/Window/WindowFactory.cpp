#include "WindowFactory.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <GL/freeglut.h>

namespace OpenGLExt 
{
	namespace Window
	{
		Window WindowFactory::create(const WindowConfig& config)
		{
			int nMonitors = 0;
			GLFWmonitor** monitors = glfwGetMonitors(&nMonitors);
			if (nMonitors == 0 || nMonitors < config.Monitor)
				throw new std::exception("monitors can not be found.");

			const GLFWvidmode* mode = glfwGetVideoMode(monitors[config.Monitor]);
			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

			glfwSetErrorCallback(error_callback);
			GLFWwindow* window = glfwCreateWindow(config.Width, config.Height, "Test", monitors[config.Monitor], NULL);

			if (window == nullptr)
			{
				glfwTerminate();
				throw new std::exception("window could not created.");
			}

			glfwMakeContextCurrent(window);
			GLenum res = glewInit();
			if (res != GLEW_OK)
			{
				throw new std::exception("Initial GLEW failed");
			}

			intptr_t glContext = (intptr_t)glfwGetWGLContext(window);
			intptr_t windowContext = (intptr_t)GetDC(glfwGetWin32Window(window));

			return Window(window, glContext, windowContext);
		}
	}
}
