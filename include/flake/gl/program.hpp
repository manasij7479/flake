#ifndef MM_PROGRAM
#define MM_PROGRAM
#include "shader.hpp"
#include <vector>
#include <type_traits>
#include <stdexcept>
#include <glm/glm.hpp>  
namespace flake
{
    namespace gl
    {
        class Program
        {
        public:
            Program(const std::vector<Shader>& input);
            Program(std::string vsfname,std::string fsfname);
            ~Program();
            GLuint getHandle() const;
            
            
            template <typename Function>
            typename  std::result_of<Function()>::type
            useFor(Function foo) const 
            {
                Use use(handle);
                return foo();
            }
            
            void uniformMat4(glm::mat4 m,std::string name);
            void uniformVec4(glm::vec4 v,std::string name);
            void uniformVec4(float x,float y,float z,float w,std::string name)
            {
                glm::vec4 v(x,y,z,w);
                uniformVec4(v,name);
            };
			
			GLint attribLocation(std::string name)
			{
				if(name=="")
					throw std::runtime_error("Null attrib name.");
				Use use(handle);
				GLint result = glGetAttribLocation(handle,name.c_str());
				if(result==-1)
					throw std::runtime_error(name+":Attrib name not found in program.");
				return result;
			}
			
        private:
            GLuint handle;
            const std::vector<Shader>& shader_list;
            
            class Use
            {
            public:
                Use(GLuint p){glUseProgram(p);};
                ~Use(){glUseProgram(0);};
            };
        };
        
        
    }
}
#endif
