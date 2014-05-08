#ifndef FLAKE_GL_MESH_HPP
#define FLAKE_GL_MESH_HPP
#include "program.hpp"
#include "buffer.hpp"
#include <vector>
#include <map>
namespace flake
{
	namespace gl
	{
		class Mesh
		{
		public:
			Mesh(std::vector<Buffer<GLfloat>> bufs,std::vector<GLuint> idx,
				 std::string vsf,std::string fsf,GLenum dm);
			void draw();
			Program* getProgram(){return prog;}
		private:
// 			std::vector<Buffer<GLfloat>> buffers;
// 			std::vector<GLuint> index;
			Program* prog;
			GLuint vao;
			std::map<std::string,GLuint> vbomap;
			GLenum drawmode;
			int isize;
		};
	}
}
#endif