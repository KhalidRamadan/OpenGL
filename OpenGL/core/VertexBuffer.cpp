#include "VertexBuffer.hpp"

#include "Renderer.hpp"
#include <iostream>



namespace core
{

	VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	{
		m_Count = size / sizeof(float);
		//std::cout << ((const float*)data)[2] << std::endl;
		GLCall(glGenBuffers(1, &m_RendererID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	VertexBuffer::~VertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_RendererID));
	}

	void VertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}

	void VertexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

}