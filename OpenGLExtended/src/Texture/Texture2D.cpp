#include "Texture2D.h"

namespace OpenGLExt
{
	namespace Texture
	{
		Texture2D::Texture2D(Shaders::Shaders shaders, size_t width, size_t height, void* data)
		{
			this->program = shaders.getProgram();
			glGenTextures(1, &native);
			glBindTexture(GL_TEXTURE_2D, native);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);

			vbo = createBuffer(12, vertices, GL_STATIC_DRAW);
			tbo = createBuffer(8, texcords, GL_STATIC_DRAW);
			ibo;

			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			// bind vao
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
			// attach vbo
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(0);
			// attach tbo
			glBindBuffer(GL_ARRAY_BUFFER, tbo);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(1);
			// attach ibo
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBindVertexArray(0);
		}

		Texture2D::~Texture2D()
		{
		}

		void Texture2D::render()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.2, 0.2, 0.2, 0.0);
			glEnable(GL_DEPTH_TEST);
			// bind shader
			glUseProgram(program);
			// get uniform locations
			int mat_loc = glGetUniformLocation(program, "matrix");
			int tex_loc = glGetUniformLocation(program, "tex");
			// bind texture
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(tex_loc, 0);
			glBindTexture(GL_TEXTURE_2D, native);
			glGenerateMipmap(GL_TEXTURE_2D);
			// set project matrix
			glUniformMatrix4fv(mat_loc, 1, GL_FALSE, matrix);
			// now render stuff
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

		GLuint Texture2D::createBuffer(int size, const float* data, GLenum usage)
		{
			GLuint ret_val = 0;
			glGenBuffers(1, &ret_val);
			glBindBuffer(GL_ARRAY_BUFFER, ret_val);
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, usage);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			return ret_val;
		}
	}
}
