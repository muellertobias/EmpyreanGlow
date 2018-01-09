#include "Texture2D.h"

namespace OpenGLExt
{
	namespace Texture
	{
		Texture2D::Texture2D(size_t width, size_t height, void* data)
		{
			glGenTextures(1, &native);
			glBindTexture(GL_TEXTURE_2D, native);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		Texture2D::~Texture2D()
		{
		}

	}
}
