#include "flake/gl/glewcontext.hpp"
#include <stdexcept>
#include <sstream>
#include <string>
namespace flake
{
    namespace gl
    {
        void GlewContext::init()
        {
            GLenum err = glewInit();
            if (GLEW_OK != err)
            {
                std::ostringstream os;
                os<<"Error: "<<glewGetErrorString(err)<<"\n";
                throw std::runtime_error(os.str());
            }
        }
    }
}