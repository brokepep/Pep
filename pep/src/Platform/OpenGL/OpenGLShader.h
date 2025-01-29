#pragma once

#include "Pep/Renderer/Shader.h"

namespace Pep {
	class OpenGLShader : public Shader
	{
	private:
		uint32_t m_RendererID;
	public:
		OpenGLShader( const std::string& vertexSrc, const std::string& fragmentSrc );
		~OpenGLShader();

		void Bind() const;
		void Unbind() const;
	};
}
