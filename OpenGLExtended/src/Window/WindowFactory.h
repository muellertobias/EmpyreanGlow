#pragma once
#include "Window.h"
#include <string>

namespace OpenGLExt
{
	namespace Window
	{
		enum Monitor
		{
			Primary,
			Secondary
		};

		typedef struct {
			Monitor Monitor;
			size_t Height;
			size_t Width;
			std::string Title;
		} WindowConfig;
	}
}

namespace OpenGLExt 
{
	namespace Window 
	{
		class WindowFactory
		{
		public:
			WindowFactory() {}
			~WindowFactory() {}

			Window create(const WindowConfig& config);

		private:
			static void error_callback(int error, const char* description) 
			{
				fputs(description, stderr);
			}


		};
	}
}
