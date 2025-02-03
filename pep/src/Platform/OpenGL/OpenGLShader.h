#pragma once

#include "Pep/Renderer/Shader.h"
#include <glm/glm.hpp>

//TODO: Remove
typedef unsigned int GLenum;


namespace Pep {
	class OpenGLShader : public Shader
	{
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	private:
		std::unordered_map<GLenum, std::string> PreProcess( const std::string& source );
		void Compile( std::unordered_map<GLenum, std::string> shaderSources );
		std::string ReadFile( const std::string& filepath );
	public:
		OpenGLShader( const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc );
		OpenGLShader( const std::string& filepath );
		virtual ~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		virtual const std::string& GetName() const override { return m_Name; }

		void UploadUniformInt( const std::string& name, int value );

		void UploadUniformFloat( const std::string& name, float value );
		void UploadUniformFloat2( const std::string& name, const glm::vec2 vector );
		void UploadUniformFloat3( const std::string& name, const glm::vec3 vector );
		void UploadUniformFloat4( const std::string& name, const glm::vec4 vector );

		void UploadUniformMat3( const std::string& name, const glm::mat3 matrix );
		void UploadUniformMat4( const std::string& name, const glm::mat4 matrix );

	};
}
