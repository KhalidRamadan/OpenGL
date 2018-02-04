#include "Shader.h"
#include "Renderer.h"


namespace core
{


	Shader::Shader(const std::string& vertexpath, const std::string& fragmentpath)
	{
		std::string vertexShader = read_file(vertexpath.c_str());
		std::string fragmentShader = read_file(fragmentpath.c_str());
		m_RendererID = CreateShader(vertexShader, fragmentShader);
		GLCall(glUseProgram(m_RendererID));
	}

	Shader::~Shader()
	{
		GLCall(glDeleteProgram(m_RendererID));
	}

	void Shader::Bind() const
	{
		GLCall(glUseProgram(m_RendererID));
	}


	void Shader::Unbind() const
	{
		GLCall(glUseProgram(0));
	}


	void Shader::SetUniform4f(const std::string& name, glm::vec4 value)
	{
		int location = GetUniformLocation(name);
		GLCall(glUniform4f(location, value.x, value.y, value.z, value.w));
	}

	void Shader::SetUniform1f(const std::string& name, float value)
	{
		int location = GetUniformLocation(name);
		GLCall(glUniform1f(location, value));
	}

	void Shader::SetUniform1i(const std::string& name, int value)
	{
		int location = GetUniformLocation(name);
		GLCall(glUniform1i(location, value));
	}

	void Shader::SetUniformMatrix4fv(const std::string& name, glm::mat4 value)
	{
		int location = GetUniformLocation(name);
		GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		if (Cache.find(name) != Cache.end())
			return Cache[name];
		GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
		if (location == -1)
			std::cout << "uniform doesn't exist" << std::endl;
		else Cache[name] = location;
		return location;
	}



	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
	{
		GLCall(unsigned int id = glCreateShader(type));
		const char* src = source.c_str();
		GLCall(glShaderSource(id, 1, &src, nullptr));
		GLCall(glCompileShader(id));

		int result;
		GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

		if (result == GL_FALSE)
		{
			int length;
			GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
			char * msg = (char*)alloca(length * sizeof(char));
			GLCall(glGetShaderInfoLog(id, length, &length, msg));
			std::cout << "FAILED!!" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
			std::cout << msg << std::endl;
		}

		return id;

	}


	unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		GLCall(unsigned int program = glCreateProgram());
		GLCall(unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader));
		GLCall(unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader));

		GLCall(glAttachShader(program, vs));
		GLCall(glAttachShader(program, fs));
		GLCall(glLinkProgram(program));
		GLCall(glValidateProgram(program));

		GLCall(glDeleteShader(vs));
		GLCall(glDeleteShader(fs));

		return program;
	}

	std::string Shader::read_file(const char* filepath)
	{
		FILE* file = fopen(filepath, "rt");
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char * data = new char[length + 1];
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;
		return result;
	}

}