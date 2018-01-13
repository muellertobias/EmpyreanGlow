#pragma once
#include "../Shaders/Shaders.h"
#include <GL/glew.h>

namespace OpenGLExt
{
	namespace Texture
	{
		class Texture2D
		{
		public:
			Texture2D(Shaders::Shaders shaders, size_t width, size_t height, void* data = 0);
			~Texture2D();

			unsigned int getNative()
			{
				return native;
			}

			void render();

		private:
			GLuint createBuffer(int size, const float* data, GLenum usage);

			GLuint program;
			GLuint native;

			GLuint vao;
			GLuint vbo;
			GLuint tbo;
			GLuint ibo;

			const float vertices[12] =
			{
				-1.0f,-1.0f, 0.0,
				1.0f,-1.0f, 0.0,
				1.0f, 1.0f, 0.0,
				-1.0f, 1.0f, 0.0
			};

			const float texcords[8] =
			{
				0.0, 1.0,
				1.0, 1.0,
				1.0, 0.0,
				0.0, 0.0
			};

			const float matrix[16] =
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			const unsigned int indices[6] = { 0, 1, 2, 0, 2, 3 }; // änderungen an diesem Parameter sorgen lediglich für das Abschneiden bestimmter areale
		};

	}
}