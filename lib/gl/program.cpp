#include "flake/gl/program.hpp"
#include <string>
#include <stdexcept>
namespace flake
{
    namespace gl
    {
        Program::Program(std::string vsfname, std::string fsfname)
        :Program
        (
            {
                    Shader(GL_VERTEX_SHADER,vsfname),
                    Shader(GL_FRAGMENT_SHADER,fsfname)
            }
        )
        {}
        Program::Program(const std::vector<Shader>& input):shader_list(input)
        {
            handle = glCreateProgram();
            for(auto shader:input)
                glAttachShader(handle,shader.getHandle());
            
            glLinkProgram(handle);
            
            int status;
            glGetProgramiv(handle, GL_LINK_STATUS, &status);
            if(status == GL_FALSE)
            {
                int loglength;
                glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &loglength);
                
                auto data = new char[loglength];
                
                glGetProgramInfoLog(handle, loglength, &loglength, data);
                
                std::string strdata(data);
                delete [] data;
                throw(std::runtime_error(strdata));
            }
            
        }
        
        Program::~Program()
        {
            for(auto& shader:shader_list)
            {
                glDetachShader(handle,shader.getHandle());
            }
            glDeleteProgram(handle);
        }
        GLuint Program::getHandle()const
        {
            return handle;
        }
        
        void Program::uniformMat4(glm::mat4 m, std::string name)
        {
            auto u = Use(handle);
            auto loc = glGetUniformLocation(handle,name.c_str());
            glUniformMatrix4fv(loc,1,GL_FALSE,&m[0][0]);
        }
        void Program::uniformVec4(glm::vec4 v, std::string name)
        {
            auto u = Use(handle);
            auto loc = glGetUniformLocation(handle,name.c_str());
            glUniform4fv(loc,1,&v[0]);
        }


        
        
        
    }
}