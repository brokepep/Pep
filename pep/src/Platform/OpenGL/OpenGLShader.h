#pragma once

#include "Pep/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Pep {
	class OpenGLShader : public Shader
	{
	private:
		uint32_t m_RendererID;
	public:
		OpenGLShader( const std::string& vertexSrc, const std::string& fragmentSrc );
		virtual ~OpenGLShader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformInt( const std::string& name, int value );

		void UploadUniformFloat( const std::string& name, float value );
		void UploadUniformFloat2( const std::string& name, const glm::vec2 vector );
		void UploadUniformFloat3( const std::string& name, const glm::vec3 vector );
		void UploadUniformFloat4( const std::string& name, const glm::vec4 vector );

		void UploadUniformMat3( const std::string& name, const glm::mat3 matrix );
		void UploadUniformMat4( const std::string& name, const glm::mat4 matrix );

	};
}
