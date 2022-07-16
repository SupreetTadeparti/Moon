#pragma once

#include "Core.h"

namespace Moon
{
	struct ShaderSource
	{
		String VertexSource;
		String FragmentSource;
	};

	enum class ShaderType
	{
		VertexShader=GL_VERTEX_SHADER,
		FragmentShader=GL_FRAGMENT_SHADER
	};

	class MOON_API Shader
	{
	public:
		Shader(const String& vertexPath, const String& fragmentPath);
		void SetUniformInt(const String& uniformName, Int value);
		void SetUniformFloat(const String& uniformName, Float value);
		void SetUniformVec2(const String& uniformName, Vec2 vec);
		void SetUniformVec3(const String& uniformName, Vec3 vec);
		void SetUniformVec4(const String& uniformName, Vec4 vec);
		void SetUniformMat3(const String& uniformName, Mat3 mat);
		void SetUniformMat4(const String& uniformName, Mat4 mat);

		// Recommended only for default shaders
		void SetProjection(Mat4 mat);
		void SetView(Mat4 mat);
		void SetModel(Mat4 mat);

		inline void Bind() const { glUseProgram(m_ProgramID); };
		inline void Unbind() const { glUseProgram(0); };
		static void Init();

		static inline Shader* DefaultColor() { return s_DefaultColorShader; }
		static inline Shader* DefaultText() { return s_DefaultTextShader; }
		static inline Shader* DefaultTexture() { return s_DefaultTextureShader; }
	private:
		Int GetUniformLocation(const String& uniformName);
		static ShaderSource ParseShader(const String& vertexPath, const String& fragmentPath);
		static Uint CompileShader(ShaderType shaderType,const String& shaderSource);
		Uint m_ProgramID;
		Uint m_VertexID;
		Uint m_FragmentID;
		static Shader* s_DefaultColorShader;
		static Shader* s_DefaultTextureShader;
		static Shader* s_DefaultTextShader;
	};
}
