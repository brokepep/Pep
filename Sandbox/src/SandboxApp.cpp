#include <Pep.h>

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

		std::shared_ptr<Pep::VertexBuffer> vertexBuffer;
		vertexBuffer.reset( Pep::VertexBuffer::Create( vertices, sizeof( vertices ) ) );

		Pep::BufferLayout layout = {
					{ Pep::ShaderDataType::Float3, "a_Position" },
					{ Pep::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout( layout );

		m_VertexArray->AddVertexBuffer( vertexBuffer );

		uint32_t indices[3] = { 0, 1, 2 };

		std::shared_ptr<Pep::IndexBuffer> indexBuffer;
		indexBuffer.reset( Pep::IndexBuffer::Create( indices, sizeof( indices ) / sizeof( uint ) ) );
		m_VertexArray->SetIndexBuffer( indexBuffer );

		m_SquareVA.reset( Pep::VertexArray::Create() );

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};
		std::shared_ptr<Pep::VertexBuffer> squareVB;
		squareVB.reset( Pep::VertexBuffer::Create( squareVertices, sizeof( squareVertices ) ) );

		squareVB->SetLayout( {
			{ Pep::ShaderDataType::Float3, "a_Position" }
							 } );
		m_SquareVA->AddVertexBuffer( squareVB );

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Pep::IndexBuffer> squareIB;
		squareIB.reset( Pep::IndexBuffer::Create( squareIndices, sizeof( squareIndices ) / sizeof( uint32_t ) ) );
		m_SquareVA->SetIndexBuffer( squareIB );


		std::string vertexSrc = R"(
				#version 330 core
				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				uniform mat4 u_ViewProjection;
				
				out vec3 v_Position;
				out vec4 v_Color;

				void main(){
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
				}
			)";

		std::string fragmentSrc = R"(
				#version 330 core
				layout(location = 0) out vec4 color;
				
				in vec3 v_Position;
				in vec4 v_Color;
				void main(){
					color = v_Color;
				}
			)";

		m_Shader.reset( new Pep::Shader( vertexSrc, fragmentSrc ) );

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_Shader2.reset( new Pep::Shader( blueShaderVertexSrc, blueShaderFragmentSrc ) );


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

		Pep::Renderer::Submit( m_Shader2, m_SquareVA );

		Pep::Renderer::Submit( m_Shader, m_VertexArray );

		Pep::Renderer::EndScene();
	}
	void OnEvent( Pep::Event& event ) override {
	}

private:
	Pep::OrthographicCamera m_Camera;
	std::shared_ptr<Pep::Shader> m_Shader;
	std::shared_ptr<Pep::VertexArray> m_VertexArray;
	std::shared_ptr<Pep::Shader> m_Shader2;
	std::shared_ptr<Pep::VertexArray> m_SquareVA;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.f;
	float m_CameraRotationSpeed = 90.f;
	float m_CameraRotation = 0;
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