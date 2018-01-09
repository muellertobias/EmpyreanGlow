#include "Shaders.h"
#include <fstream>

namespace OpenGLExt
{
	namespace Shaders
	{
		Shaders::Shaders(std::string vertexFilename, std::string fragmentFilename)
		{
			ShadersImpl shaders = loadShaders(vertexFilename, fragmentFilename);
			_Program = glCreateProgram();

			glAttachShader(_Program, shaders.Vertex);
			glAttachShader(_Program, shaders.Fragment);
			glLinkProgram(_Program);
			GLint linked;

			glGetProgramiv(_Program, GL_LINK_STATUS, &linked);
			if (!linked)
			{
				throw new std::exception("Program did not link.");
			}
		}

		Shaders::~Shaders()
		{
		}

		ShadersImpl Shaders::loadShaders(std::string vertexFilename, std::string fragmentFilename)
		{
			GLint fragment = fragment = glCreateShader(GL_FRAGMENT_SHADER);
			GLint vertex = glCreateShader(GL_VERTEX_SHADER);

			GLint vLength, fLength;
			std::string vertexFileContent = loadFile(vertexFilename);
			std::string fragmentFileContent = loadFile(fragmentFilename);

			const char* v = vertexFileContent.c_str();
			const char* f = fragmentFileContent.c_str();

			glShaderSource(vertex, 1, &v, &vertexFileContent.length);
			glShaderSource(fragment, 1, &f, &fragmentFileContent.length);

			GLint compiled;

			glCompileShader(vertex);
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &compiled);
			if (!compiled)
			{
				throw new std::exception("Vertex shader not compiled.");
			}

			glCompileShader(fragment);
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &compiled);
			if (!compiled)
			{
				throw new std::exception("Fragment shader not compiled.");
			}

			ShadersImpl shaders;
			shaders.Vertex = vertex;
			shaders.Fragment = fragment;

			return shaders;
		}

		std::string Shaders::loadFile(std::string filename) 
		{
			std::ifstream sourceFile(filename);
			std::string sourceCode(std::istreambuf_iterator<char>(sourceFile), (std::istreambuf_iterator<char>()));
			return sourceCode;
		}
	}
}