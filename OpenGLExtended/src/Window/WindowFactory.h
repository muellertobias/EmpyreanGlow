#pragma once
#include "Window.h"
#include <string>

namespace OpenGLExt
{
	namespace Windows
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
			bool IsFullscreen;
		} WindowConfig;
	}
}

namespace OpenGLExt 
{
	namespace Windows
	{
		class WindowFactory
		{
		public:
			WindowFactory() {}
			~WindowFactory() {}

			Window create(WindowConfig& config);

		private:
			static void error_callback(int error, const char* description) 
			{
				fputs(description, stderr);
			}
		};
	}
}
