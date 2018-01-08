#pragma once
#include <string>
#include <GL\glew.h>
#include <GL\freeglut.h>

namespace OpenGLExt
{
	namespace Shaders
	{
		class Shaders
		{
		public:
			Shaders(std::string vertexFilename, std::string fragmentFilename);
			~Shaders();

			unsigned int getVertex()
			{
				return _Vertex;
			}

			unsigned int getFragment()
			{
				return _Fragment;
			}

		private:
			unsigned int _Vertex;
			GLuint _Fragment;
		};
	}
}

