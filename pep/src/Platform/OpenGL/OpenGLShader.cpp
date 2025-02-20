#include "peppch.h"

#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Pep {

	static GLenum ShaderTypeFromString( const std::string& type ) {
		if( type == "vertex" )
			return GL_VERTEX_SHADER;
		if( type == "fragment" || type == "pixel" )
			return GL_FRAGMENT_SHADER;
		PEP_CORE_ASSERT( false, "Unknown shader type!" );
		return 0;
	}

	void OpenGLShader::Compile( const std::unordered_map<GLenum, std::string> shaderSources ) {

		GLuint program = glCreateProgram();
		PEP_CORE_ASSERT( shaderSources.size() <= 2, "We only support 2 shaders for now" );
		std::array<GLuint, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for( auto& kv : shaderSources )
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader( type );

			const GLchar* sourceCStr = source.c_str();
			glShaderSource( shader, 1, &sourceCStr, 0 );

			glCompileShader( shader );

			GLint isCompiled = 0;
			glGetShaderiv( shader, GL_COMPILE_STATUS, &isCompiled );
			if( isCompiled == GL_FALSE )
			{
				GLint maxLength = 0;
				glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );

				std::vector<GLchar> infoLog( maxLength );
				glGetShaderInfoLog( shader, maxLength, &maxLength, &infoLog[0] );

				// We don't need the shader anymore.
				glDeleteShader( shader );

				PEP_CORE_ERROR( "Shader Error:{0}", infoLog.data() );
				PEP_CORE_ASSERT( false, "Shader Compilation Error!" );
				break;
			}

			glAttachShader( program, shader );
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		glLinkProgram( program );

		GLint isLinked = 0;
		glGetProgramiv( program, GL_LINK_STATUS, ( int* )&isLinked );
		if( isLinked == GL_FALSE )
		{
			GLint maxLength = 0;
			glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );

			std::vector<GLchar> infoLog( maxLength );
			glGetProgramInfoLog( program, maxLength, &maxLength, &infoLog[0] );

			glDeleteProgram( program );
			for( auto id : glShaderIDs )
			{
				glDeleteShader( id );
			}

			PEP_CORE_ERROR( "{0}", infoLog.data() );
			PEP_CORE_ASSERT( false, "Shader Linking Error!" );
			return;
		}

		for( auto id : glShaderIDs )
		{
			glDetachShader( program, id );
			glDeleteShader( id );
		}
		m_RendererID = program;

	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess( const std::string& source ) {
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen( typeToken );
		size_t pos = source.find( typeToken, 0 );
		while( pos != std::string::npos )
		{
			size_t eol = source.find_first_of( "\r\n", pos );
			PEP_CORE_ASSERT( eol != std::string::npos, "Syntax error" );
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr( begin, eol - begin );
			PEP_CORE_ASSERT( ShaderTypeFromString( type ), "Invalid shader type specified" );

			size_t nextLinePos = source.find_first_not_of( "\r\n", eol );
			PEP_CORE_ASSERT( nextLinePos != std::string::npos, "Syntax error" );
			pos = source.find( typeToken, nextLinePos );
			shaderSources[ShaderTypeFromString( type )] = ( pos == std::string::npos ) ? source.substr( nextLinePos ) : source.substr( nextLinePos, pos - nextLinePos );
		}

		return shaderSources;
	}

	OpenGLShader::OpenGLShader( const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc ):m_Name( name ) {
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;

		Compile( shaderSources );
	}

	OpenGLShader::OpenGLShader( const std::string& filepath ) {
		std::string shaderSource = ReadFile( filepath );
		auto shaderSources = PreProcess( shaderSource );
		Compile( shaderSources );

		auto lastSlash = filepath.find_last_of( "/\\" );
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind( '.' );
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr( lastSlash, count );
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram( m_RendererID );
	}

	std::string OpenGLShader::ReadFile( const std::string& filepath ) {
		std::ifstream in( filepath, std::ios::in | std::ios::binary );

		std::string result;
		if( in )
		{
			in.seekg( 0, std::ios::end );
			result.resize( in.tellg() );
			in.seekg( 0, std::ios::beg );
			in.read( &result[0], result.size() );
			in.close();
		} else
		{
			PEP_CORE_ERROR( "Could not open file '{0}'", filepath );
		}
		return result;
	}

	void OpenGLShader::UploadUniformMat3( const std::string& name, const glm::mat3 matrix ) {
		GLint location = glGetUniformLocation( m_RendererID, name.c_str() );
		glUniformMatrix3fv( location, 1, GL_FALSE, glm::value_ptr( matrix ) );
	}

	void OpenGLShader::UploadUniformFloat( const std::string& name, float value ) {
		GLint location = glGetUniformLocation( m_RendererID, name.c_str() );
		glUniform1f( location, value );
	}

	void OpenGLShader::UploadUniformFloat2( const std::string& name, const glm::vec2 vector ) {
		GLint location = glGetUniformLocation( m_RendererID, name.c_str() );
		glUniform2f( location, vector.x, vector.y );
	}

	void OpenGLShader::UploadUniformFloat3( const std::string& name, const glm::vec3 vector ) {
		GLint location = glGetUniformLocation( m_RendererID, name.c_str() );
		glUniform3f( location, vector.x, vector.y, vector.z );
	}

	void OpenGLShader::UploadUniformInt( const std::string& name, int value ) {
		GLint location = glGetUniformLocation( m_RendererID, name.c_str() );
		glUniform1i( location, value );
	}

	void OpenGLShader::
		Bind() const {
		glUseProgram( m_RendererID );
	}

	void OpenGLShader::
		Unbind() const {
		glUseProgram( 0 );
	}

	void OpenGLShader::
		UploadUniformMat4( const std::string& name, const glm::mat4 matrix ) {
		GLint location = glGetUniformLocation( m_RendererID, name.c_str() );
		glUniformMatrix4fv( location, 1, GL_FALSE, glm::value_ptr( matrix ) );
	}

	void OpenGLShader::
		UploadUniformFloat4( const std::string& name, const glm::vec4 vector ) {
		GLint location = glGetUniformLocation( m_RendererID, name.c_str() );
		glUniform4f( location, vector.x, vector.y, vector.z, vector.w );
	}

}