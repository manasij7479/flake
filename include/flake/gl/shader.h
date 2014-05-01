#ifndef MM_SHADER
#define MM_SHADER
#include <string>
#include <GL/glew.h>
namespace flake
{
    namespace gl
    {
        class Shader
        {
        public:
            Shader(GLenum Type,std::string filename);
            ~Shader();
            GLuint getHandle() const;
        private:
            GLuint handle;
            GLenum shader_type;
        };
    }
}
#endif