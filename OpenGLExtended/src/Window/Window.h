#pragma once
#include <iostream>
#include <functional>
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
			
			void SetScrollCallback(std::function<void(short scrollDirection, double positionX, double positionY)>& callback)
			{
				this->scrollCallback = callback;
			}

			void SetClickCallback(std::function<void(double positionX, double positionY)>& callback)
			{
				this->clickCallback = callback;
			}

			void SetWindowSizeChangedCallback(std::function<void(int width, int height)>& callback)
			{
				this->clickCallback = callback;
			}

		private:
			static std::list<Window*> openedWindows;

			std::shared_ptr<GLFWwindow> window;
			intptr_t glContext;
			intptr_t windowContext;
			void init();

			std::function<void(short scrollDirection, double positionX, double positionY)> scrollCallback;
			std::function<void(double positionX, double positionY)> clickCallback;
			std::function<void(int width, int height)> windowSizeChangedallback;
			// TODO callback definieren und mit diesem kernel parametrieren und starten

		protected:
			static void _OnClick(GLFWwindow* nativeWindow, double positionX, double positionY);
			static void _OnWindowSizeChanged(GLFWwindow* nativeWindow, int width, int height);
			static void _OnScroll(GLFWwindow* nativeWindow, short scrollDir);
		};

		
	}
}