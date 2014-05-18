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
			Mesh(std::vector< flake::gl::Buffer< GLfloat > > bufs, std::vector< GLuint > idx, flake::gl::Shader vs, flake::gl::Shader fsf, GLenum dm);
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
		
		Mesh* getMeshFromFile(std::string dataf,std::string v,std::string f);
		//Adapter for old mesh file from the old framework
	}
}
#endif