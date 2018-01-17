#pragma once
#include <iostream>
#include <list>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace OpenGLExt
{
	namespace Windows
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
			static std::list<Window*> storage;

			std::shared_ptr<GLFWwindow> window;
			intptr_t glContext;
			intptr_t windowContext;
			void init();
			// TODO callback definieren und mit diesem kernel parametrieren und starten

		protected:
			static void _OnCursorPositionChanged(GLFWwindow* nativeWindow, double xpos, double ypos);
		};

		
	}
}