#include "flake/gl/shader.hpp"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>
#include<iostream>
namespace flake
{
    namespace gl
    {
		Shader::Shader(GLenum Type, const std::istream& input)
		{
			if(!input)
				throw std::runtime_error("Bad shader input stream");
			
			shader_type = Type;
            
            std::ostringstream stream;
            stream<<input.rdbuf();
            std::string strdata = stream.str();
            const GLchar* data = strdata.c_str();
            
            handle = glCreateShader(shader_type);
            glShaderSource(handle,1,static_cast<const GLchar**> (&data),0);
            
            glCompileShader(handle);
            
            int status;
            glGetShaderiv(handle,GL_COMPILE_STATUS,&status);
            if(status == GL_FALSE)
            {
                int loglength;
                glGetShaderiv(handle,GL_INFO_LOG_LENGTH,&loglength);
                
                auto data = new char[loglength];
                
                glGetShaderInfoLog(handle,loglength,&loglength,data);
                
                std::string strdata(data);
                delete [] data;
                
                throw(std::runtime_error(strdata));
            }
		}

        Shader::Shader(GLenum Type,std::string filename):
        Shader(Type,std::ifstream(filename))
        {
        }
        Shader::~Shader()
        {
            glDeleteShader(handle);
        }
        GLuint Shader::getHandle()const
        {
            return handle;
        }
    }
}