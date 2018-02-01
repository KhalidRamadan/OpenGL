#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace core
{
	class VertexArray
	{
	private:
		unsigned int m_RendererID;
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const core::VertexBuffer& vb, const core::VertexBufferLayout& layout);

		void Bind() const;
		void Unbind() const;
	};

}