#pragma once

#include <string>

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
