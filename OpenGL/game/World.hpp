
//todo::

#pragma once
#include "../core/graphics.h"
#include<iostream>
#include<memory>
namespace game
{
	class World
	{
	private:
		core::VertexArray *m_VertexArray;
		core::VertexBuffer *m_VertexBuffer;
		core::IndexBuffer *m_IndexBuffer;
		core::VertexBufferLayout *m_Layout;
		core::Renderer *m_Renderer;
		core::Shader *m_Shader;
		core::Window *m_Window;
		std::vector<core::Texture> Textures;
		Camera *m_camera;
	public:
		World();
		~World();
		// set
		void SetVertexArray(core::VertexArray VA);
		void SetVertexBuffer(core::VertexBuffer VB);
		void SetIndexBuffer(core::IndexBuffer IB);
		void SetVertexBufferLayout(core::VertexBufferLayout Layout);
		void SetRenderer(core::Renderer R);
		void SetShader(core::Shader S);
		void AddTexture(core::Texture T);
		void ApplyUniforms(); // todo:: array of functions 
		void RenderWorld();
	private:
		void Init();

		

	};



}

