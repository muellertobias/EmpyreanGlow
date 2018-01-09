#pragma once
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OpenGLExt
{
	namespace Window
	{
		class Window
		{
		public:
			Window(std::shared_ptr<GLFWwindow> window, intptr_t glContext, intptr_t windowContext);
			~Window();

			intptr_t getGLContext() 
			{
				return glContext;
			}

			intptr_t getWindowContext() 
			{
				return windowContext;
			}

			void refresh();
			void close();
			bool isClosed();

		private:
			std::shared_ptr<GLFWwindow> window;
			intptr_t glContext;
			intptr_t windowContext;
		};
	}
}