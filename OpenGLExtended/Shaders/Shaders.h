#pragma once
#include <string>
#include <GL\glew.h>
#include <GL\freeglut.h>


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
			return _Vertex;
		}

	private:
		unsigned int _Vertex;
		GLuint _Fragment;
	};
}


