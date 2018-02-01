#include "Renderer.h"


namespace core
{

	void Renderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::Draw(const VertexArray& va, const core::IndexBuffer& ib, const Shader& shader) const
	{
		shader.Bind();
		va.Bind();
		ib.Bind();
		unsigned int count = ib.GetCount();
		//std::cout << count << std::endl;
		GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
	}

}