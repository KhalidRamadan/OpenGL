#include "Texture.h"
#include "GL/glew.h"
#include "stb_image.h"
#include "ErrorHandler.h"
#include<iostream>
namespace core
{
	Texture::Texture(const std::string& image)
	{
		GLCall(glGenTextures(1, &m_RendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));


		// set the texture wrapping/filtering options (on the currently bound texture object)
		// todo:: add to the class 
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		stbi_set_flip_vertically_on_load(true);

		unsigned char *data = stbi_load(image.c_str(), &m_Width, &m_Height, &m_NrChannels, 0);
		unsigned int format = 0;

		if (m_NrChannels == 3) format = GL_RGB;
		else  if(m_NrChannels == 4) format = GL_RGBA;
		if (data)
		{
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data));
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		}
		else std::cout << "Failed to load texture" << std::endl;
		stbi_image_free(data);
	}


	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &m_RendererID));
	}

	void Texture::Bind(unsigned int TextureUnit) const
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + TextureUnit));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	}

	void Texture::Unbind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}



}

