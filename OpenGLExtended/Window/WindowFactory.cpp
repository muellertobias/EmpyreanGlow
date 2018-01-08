#include "WindowFactory.h"

namespace OpenGLExt 
{
	namespace Window
	{
		WindowFactory::WindowFactory()
		{
		}


		WindowFactory::~WindowFactory()
		{
		}

		Window WindowFactory::create(const WindowConfig& config)
		{
			return Window();
		}
	}
}
