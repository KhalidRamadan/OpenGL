#pragma once

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

namespace core
{

	class Renderer
	{
	public:
		void Clear() const;
		void DrawElements(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void DrawArrays(const VertexArray& va, const core::VertexBuffer& vb, const VertexBufferLayout& layout, const Shader& shader) const;
	};

}