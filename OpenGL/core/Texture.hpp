#pragma once

#include<string>

namespace core
{
	class Texture
	{
	private:
		unsigned int m_RendererID;
		int m_Width, m_Height, m_NrChannels;
	public:
		Texture(const std::string& image);
		~Texture();
		void Bind(unsigned int TextureUnit) const;
		void Unbind() const;

	};
}