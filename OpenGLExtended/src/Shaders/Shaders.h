#pragma once
#include <string>
#include <GL\glew.h>
#include <GL\freeglut.h>

namespace OpenGLExt
{
	namespace Shaders
	{
		typedef struct
		{
			GLuint Vertex;
			GLuint Fragment;
		} ShadersImpl;

		class Shaders
		{
		public:
			Shaders(std::string vertexFilename, std::string fragmentFilename);
			~Shaders();

			ShadersImpl getShaders()
			{
				return _Shaders;
			}

			GLuint getProgram() 
			{
				return _Program;
			}

		private:
			ShadersImpl _Shaders;
			GLuint _Program;

			ShadersImpl loadShaders(std::string vertexFilename, std::string fragmentFilename);
			std::string loadFile(std::string filename);
		};
	}
}

