#include "Renderer.h"


void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] " << error << std::endl << "function Name : " << function
			<< std::endl << "File : " << file << std::endl << "Line : " << line << std::endl;
		return false;
	}
	return true;
}


void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	unsigned int count = ib.GetCount();
	//std::cout << count << std::endl;
	GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
}