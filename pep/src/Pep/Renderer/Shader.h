#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Pep {
	class Shader
	{
	private:
		uint32_t m_RendererID;
	public:
		Shader( const std::string& vertexSrc, const std::string& fragmentSrc );
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4( const std::string& name, const glm::mat4 matrix );
	};
}


//namespace Pep {
//	class Shader
//	{
//	protected:
//		uint32_t m_RendererID;
//	public:
//		virtual void Bind() const = 0;
//		virtual void Unbind() const = 0;
//	};
//}
