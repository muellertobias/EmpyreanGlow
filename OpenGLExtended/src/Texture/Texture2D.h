#pragma once
#include <GL/glew.h>

namespace OpenGLExt
{
	namespace Texture
	{
		class Texture2D
		{
		public:
			Texture2D(size_t width, size_t height, void* data = 0);
			~Texture2D();

			unsigned int getNative()
			{
				return native;
			}

		private:
			GLuint native;
		};

	}
}