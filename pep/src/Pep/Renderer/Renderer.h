#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Pep {
	class Renderer
	{
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;

			SceneData() = default;
		};

		static SceneData* m_SceneData;
	public:
		static void BeginScene( OrthographicCamera& camera );

		static void EndScene();

		static void Submit( const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray );
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}