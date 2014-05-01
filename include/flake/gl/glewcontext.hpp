#ifndef FLAKE_GL_GLEW_CONTEXT_HPP
#define FLAKE_GL_GLEW_CONTEXT_HPP
#include "flake/gl/context.hpp"
#include <GL/glew.h>
namespace flake
{
    namespace gl
    {
        class GlewContext: public Context
        {
        public:
            void init();
        };
        
    }
}
#endif