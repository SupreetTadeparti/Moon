#include "Shader.hpp"
#include "Renderer.hpp"

namespace Moon
{
	Shader* Shader::s_DefaultShader = nullptr;

	Shader* Shader::GetDefault()
	{
		if (s_DefaultShader == nullptr) GenerateDefault();
		return s_DefaultShader;
	}

	void Shader::GenerateDefault()
	{
		s_DefaultShader = new Shader("DefaultVertex.glsl", "DefaultFragment.glsl");
		s_DefaultShader->Bind();
		if (Renderer::GetRenderType() == RenderType::TwoD)
		{
			s_DefaultShader->SetProjection(Math::Ortho(0.0f, (Float)Window::GetWidth(), 0.0f, (Float)Window::GetHeight(), -1.0f, 1.0f));
		}
		else if (Renderer::GetRenderType() == RenderType::ThreeD)
		{
			s_DefaultShader->SetProjection(Math::Perspective(Renderer::GetFOV(), (Double)(Window::GetWidth()) / (Double)(Window::GetHeight()), 0.01, 1000.));
		}
		s_DefaultShader->SetView(Mat4(1.0f));
		s_DefaultShader->Unbind();
	}

	void Shader::SetProjection(Mat4 mat)
	{
		SetUniformMat4("u_Projection", mat);
	}

	void Shader::SetView(Mat4 mat)
	{
		SetUniformMat4("u_View", mat);
	}

	void Shader::SetModel(Mat4 mat)
	{
		SetUniformMat4("u_Model", mat);
	}

	ShaderSource Shader::ParseShader(const String& vertexPath, const String& fragmentPath)
	{
		std::ifstream is;
		is.exceptions(std::ifstream::badbit);

		String vertexSource;
		String fragmentSource;

		is.open("./src/shaders/" + vertexPath);
		std::stringstream vertexFile;
		vertexFile << is.rdbuf();
		is.close();

		is.open("./src/shaders/" + fragmentPath);
		std::stringstream fragmentFile;
		fragmentFile << is.rdbuf();
		is.close();

		vertexSource = vertexFile.str();
		fragmentSource = fragmentFile.str();

		return { vertexSource, fragmentSource };
	}

	Uint Shader::CompileShader(ShaderType shaderType, const String& shaderSource)
	{
		Uint shaderID = glCreateShader((Uint)shaderType);

		const char* source = shaderSource.c_str();
		glShaderSource(shaderID, 1, &source, NULL);
		glCompileShader(shaderID);

		int success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
			String shaderTypeString = (shaderType == ShaderType::VertexShader ? "VERTEX SHADER" : "FRAGMENT SHADER");
			MoonLogError("Failed to Compile " + shaderTypeString);
			MoonLogInfo(infoLog);
		}

		return shaderID;
	}

	Shader::Shader(const String& vertexPath, const String& fragmentPath, Bool err) : m_DisplayErrors(err)
	{
		ShaderSource shaderSource = ParseShader(vertexPath, fragmentPath);

		m_ProgramID = glCreateProgram();
		m_VertexID = CompileShader(ShaderType::VertexShader, shaderSource.VertexSource);
		m_FragmentID = CompileShader(ShaderType::FragmentShader, shaderSource.FragmentSource);

		glAttachShader(m_ProgramID, m_VertexID);
		glAttachShader(m_ProgramID, m_FragmentID);

		glLinkProgram(m_ProgramID);
		glValidateProgram(m_ProgramID);

		glDeleteShader(m_VertexID);
		glDeleteShader(m_FragmentID);
	}

	// Uniform Handling

	Int Shader::GetUniformLocation(const String& uniformName)
	{
		GLint activeProgram = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM, &activeProgram);
		if (activeProgram == 0)
		{
			Bind();
		}
		return glGetUniformLocation(m_ProgramID, uniformName.c_str());
	}

	void Shader::SetUniformInt(const String& uniformName, Int val)
	{
		Int location = GetUniformLocation(uniformName);
		if (location == -1 && m_DisplayErrors)
		{
			MoonLogError("Uniform " + uniformName + " Not Found!");
			return;
		}
		glUniform1i(location, val);
	}

	void Shader::SetUniformFloat(const String& uniformName, Float val)
	{
		Int location = GetUniformLocation(uniformName);
		if (location == -1 && m_DisplayErrors)
		{
			MoonLogError("Uniform " + uniformName + " Not Found!");
			return;
		}
		glUniform1f(location, val);
	}

	void Shader::SetUniformVec2(const String& uniformName, Vec2 vec)
	{
		Int location = GetUniformLocation(uniformName);
		if (location == -1 && m_DisplayErrors)
		{
			MoonLogError("Uniform " + uniformName + " Not Found!");
			return;
		}
		glUniform2f(location, vec.x, vec.y);
	}

	void Shader::SetUniformVec3(const String& uniformName, Vec3 vec)
	{
		Int location = GetUniformLocation(uniformName);
		if (location == -1 && m_DisplayErrors)
		{
			MoonLogError("Uniform " + uniformName + " Not Found!");
			return;
		}
		glUniform3f(location, vec.x, vec.y, vec.z);
	}
	
	void Shader::SetUniformVec4(const String& uniformName, Vec4 vec)
	{
		Int location = GetUniformLocation(uniformName);
		if (location == -1 && m_DisplayErrors)
		{
			MoonLogError("Uniform " + uniformName + " Not Found!");
			return;
		}
		glUniform4f(location, vec.x, vec.y, vec.z, vec.a);
	}
	
	void Shader::SetUniformMat3(const String& uniformName, Mat3 mat)
	{
		Int location = GetUniformLocation(uniformName);
		if (location == -1 && m_DisplayErrors)
		{
			MoonLogError("Uniform " + uniformName + " Not Found!");
			return;
		}
		glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::SetUniformMat4(const String& uniformName, Mat4 mat)
	{
		Int location = GetUniformLocation(uniformName);
		if (location == -1 && m_DisplayErrors)
		{
			MoonLogError("Uniform " + uniformName + " Not Found!");
			return;
		}
		glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
	}
}