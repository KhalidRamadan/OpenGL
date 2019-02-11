#include "Renderer.hpp"


namespace core
{

	void Renderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::DrawElements(const VertexArray& va, const core::IndexBuffer& ib, const Shader& shader) const
	{
		shader.Bind();
		va.Bind();
		ib.Bind();
		unsigned int count = ib.GetCount();
		//std::cout << count << std::endl;
		GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
	}


	void Renderer::DrawArrays(const VertexArray& va, const core::VertexBuffer& vb, const VertexBufferLayout& layout,const Shader& shader) const
	{
		shader.Bind();
		va.Bind();
		vb.Bind();
		unsigned int count = (4 * vb.GetCount()) / layout.GetStride();
		//std::cout << vb.GetCount() << "  " << layout.GetStride() << std::endl;
		//std::cout << count << std::endl;
		GLCall(glDrawArrays(GL_TRIANGLES, 0, count));
	}

}