#include <Pep.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui/imgui.h"


class ExampleLayer : public Pep::Layer
{
public:
	ExampleLayer()
		: Layer( "Example" ), m_Camera( { -1.6f, 1.6f, -0.9f, .9f } ), m_CameraPosition( 0 ) {
		m_VertexArray.reset( Pep::VertexArray::Create() );

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Pep::Ref<Pep::VertexBuffer> vertexBuffer;
		vertexBuffer.reset( Pep::VertexBuffer::Create( vertices, sizeof( vertices ) ) );

		Pep::BufferLayout layout = {
					{ Pep::ShaderDataType::Float3, "a_Position" },
					{ Pep::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout( layout );

		m_VertexArray->AddVertexBuffer( vertexBuffer );

		uint32_t indices[3] = { 0, 1, 2 };

		Pep::Ref<Pep::IndexBuffer> indexBuffer;
		indexBuffer.reset( Pep::IndexBuffer::Create( indices, sizeof( indices ) / sizeof( uint ) ) );
		m_VertexArray->SetIndexBuffer( indexBuffer );

		m_SquareVA.reset( Pep::VertexArray::Create() );

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		Pep::Ref<Pep::VertexBuffer> squareVB;
		squareVB.reset( Pep::VertexBuffer::Create( squareVertices, sizeof( squareVertices ) ) );

		squareVB->SetLayout( {
			{ Pep::ShaderDataType::Float3, "a_Position" }
							 } );
		m_SquareVA->AddVertexBuffer( squareVB );

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Pep::Ref<Pep::IndexBuffer> squareIB;
		squareIB.reset( Pep::IndexBuffer::Create( squareIndices, sizeof( squareIndices ) / sizeof( uint32_t ) ) );
		m_SquareVA->SetIndexBuffer( squareIB );


		std::string vertexSrc = R"(
				#version 330 core
				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;
				
				out vec3 v_Position;

				void main(){
					v_Position = a_Position;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				}
			)";

		std::string fragmentSrc = R"(
				#version 330 core
				layout(location = 0) out vec4 color;

				uniform vec3 u_Color;
				
				in vec3 v_Position;
				void main(){
					color = vec4(u_Color, 1.0);
				}
			)";

		m_Shader.reset( Pep::Shader::Create( vertexSrc, fragmentSrc ) );

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			in vec3 v_Position;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset( Pep::Shader::Create( flatColorShaderVertexSrc, flatColorShaderFragmentSrc ) );


	}
	void OnUpdate( Pep::Timestep ts ) override {

		PEP_TRACE( "Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds() );
		float dt = ts;

		if( Pep::Input::IsKeyPressed( PEP_KEY_A ) )
			m_CameraPosition.x -= m_CameraMoveSpeed * dt;
		else if( Pep::Input::IsKeyPressed( PEP_KEY_D ) )
			m_CameraPosition.x += m_CameraMoveSpeed * dt;

		if( Pep::Input::IsKeyPressed( PEP_KEY_W ) )
			m_CameraPosition.y += m_CameraMoveSpeed * dt;
		else if( Pep::Input::IsKeyPressed( PEP_KEY_S ) )
			m_CameraPosition.y -= m_CameraMoveSpeed * dt;

		if( Pep::Input::IsKeyPressed( PEP_KEY_Q ) )
			m_CameraRotation += m_CameraRotationSpeed * dt;
		if( Pep::Input::IsKeyPressed( PEP_KEY_E ) )
			m_CameraRotation -= m_CameraRotationSpeed * dt;

		Pep::RenderCommand::SetClearColor( { 1.f, 1.f, 0.1f, 1 } );
		Pep::RenderCommand::Clear();

		m_Camera.SetRotation( m_CameraRotation );
		m_Camera.SetPosition( m_CameraPosition );

		Pep::Renderer::BeginScene( m_Camera );

		static glm::mat4 scale = glm::scale( glm::mat4( 1.f ), glm::vec3( 0.1f ) );


		std::dynamic_pointer_cast< Pep::OpenGLShader > ( m_FlatColorShader )->Bind();
		std::dynamic_pointer_cast< Pep::OpenGLShader > ( m_FlatColorShader )->UploadUniformFloat3( "u_Color", m_SquareColor );

		for( int y = 0; y < 5; y++ )
		{
			for( int x = 0; x < 5; x++ )
			{
				glm::vec3 pos( x * 0.11f, y * 0.11f, 0 );
				glm::mat4 transform = glm::translate( glm::mat4( 1.f ), pos ) * scale;
				Pep::Renderer::Submit( m_FlatColorShader, m_SquareVA, transform );
			}
		}


		Pep::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin( "Settings" );
		ImGui::ColorEdit3( "Square Color", glm::value_ptr( m_SquareColor ) );
		ImGui::End();
	}

	void OnEvent( Pep::Event& event ) override {
	}

private:
	Pep::OrthographicCamera m_Camera;

	Pep::Ref<Pep::Shader> m_Shader;
	Pep::Ref<Pep::VertexArray> m_VertexArray;

	Pep::Ref<Pep::Shader> m_FlatColorShader;
	Pep::Ref<Pep::VertexArray> m_SquareVA;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.f;
	float m_CameraRotationSpeed = 90.f;
	float m_CameraRotation = 0;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Pep::Application
{
public:
	Sandbox() {


		PushLayer( new ExampleLayer() );
	}
	~Sandbox() {
	}

};

Pep::Application* Pep::CreateApplication() {
	return new Sandbox();
}