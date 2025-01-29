#include "peppch.h"
#include "Application.h"

#include "Pep/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Pep {
	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToGLBaseType( ShaderDataType type ) {
		switch( type )
		{
			case Pep::ShaderDataType::Float:	return GL_FLOAT;
				break;
			case Pep::ShaderDataType::Float2:	return GL_FLOAT;
				break;
			case Pep::ShaderDataType::Float3:	return GL_FLOAT;
				break;
			case Pep::ShaderDataType::Float4:	return GL_FLOAT;
				break;
			case Pep::ShaderDataType::Mat3:		return GL_FLOAT;
				break;
			case Pep::ShaderDataType::Mat4:		return GL_FLOAT;
				break;
			case Pep::ShaderDataType::Int:		return GL_INT;
				break;
			case Pep::ShaderDataType::Int2:		return GL_INT;
				break;
			case Pep::ShaderDataType::Int3:		return GL_INT;
				break;
			case Pep::ShaderDataType::Int4:		return GL_INT;
				break;
			case Pep::ShaderDataType::Bool:		return GL_BOOL;
				break;
			default:
				{
					PEP_CORE_ASSERT( false, "Unknown ShaderDataType!" );
					return 0;
				}
				break;
		}
	}

	Application::Application() {
		PEP_ASSERT( !s_Instance, "Application already exists!" );
		s_Instance = this;

		m_Window = std::unique_ptr<Window>( Window::Create() );
		m_Window->SetEventCallback( PEP_BIND_EVENT_FN( Application::OnEvent ) );

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay( m_ImGuiLayer );

		glGenVertexArrays( 1, &m_VertexArray );
		glBindVertexArray( m_VertexArray );

		float vertices[7 * 3] = {
			-.5f, -.5f, .0f, .8f, 0.2f, .8f, 1.f,
			 .5f, -.5f, .0f, .8f, .2f, .2f, 1.f,
			 .0f,  .5f, .0f, .2f, .8f, .2f, 1.f
		};

		m_VertexBuffer.reset( VertexBuffer::Create( vertices, sizeof( vertices ) ) );

		{
			BufferLayout layout = {
						{ ShaderDataType::Float3, "a_Position" },
						{ ShaderDataType::Float4, "a_Color" }
			};

			m_VertexBuffer->SetLayout( layout );
		}

		uint32_t index = 0;
		for( const auto& element : m_VertexBuffer->GetLayout() )
		{
			glEnableVertexAttribArray( index );
			glVertexAttribPointer( index,
								   element.GetComponentCount(),
								   ShaderDataTypeToGLBaseType( element.Type ),
								   element.Normalized ? GL_TRUE : GL_FALSE,
								   m_VertexBuffer->GetLayout().GetStride(),
								   ( const void* )element.Offset );
			index++;
		}

		uint32_t indices[3] = { 0, 1, 2 };

		m_IndexBuffer.reset( IndexBuffer::Create( indices, sizeof( indices ) / sizeof( uint ) ) );


		std::string vertexSrc = R"(
				#version 330 core
				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;
				
				out vec3 v_Position;
				out vec4 v_Color;

				void main(){
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = vec4(a_Position, 1.0);
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

		m_Shader.reset( new Shader( vertexSrc, fragmentSrc ) );

	}

	Application::~Application() {
	}

	void Application::Run() {
		while( m_Running )
		{
			glClearColor( 0.1f, 0.1f, 0.1f, 1 );
			glClear( GL_COLOR_BUFFER_BIT );

			glBindVertexArray( m_VertexArray );
			m_Shader->Bind();
			glDrawElements( GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr );

			for( Layer* layer : m_LayerStack )
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for( Layer* layer : m_LayerStack )
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent( Event& e ) {
		EventDispatcher dispatcher( e );
		dispatcher.Dispatch<WindowCloseEvent>( PEP_BIND_EVENT_FN( Application::OnWindowClose ) );
		//PEP_TRACE( "{0}", e.ToString() );

		for( auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			( *--it )->OnEvent( e );
			if( e.Handled )
				break;
		}
	}

	void Application::PushLayer( Layer* layer ) {
		m_LayerStack.PushLayer( layer );
		layer->OnAttach();
	}

	void Application::PushOverlay( Layer* overlay ) {
		m_LayerStack.PushOverlay( overlay );
		overlay->OnAttach();
	}

	bool Application::OnWindowClose( WindowCloseEvent& e ) {
		m_Running = false;
		return true;
	}


}
