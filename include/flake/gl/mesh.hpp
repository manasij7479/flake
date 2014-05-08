#ifndef FLAKE_GL_MESH_HPP
#define FLAKE_GL_MESH_HPP
#include "program.hpp"
#include <vector>
#include <map>
namespace flake
{
	namespace gl
	{
		template<typename T>
		class Buffer
		{
		public:
			Buffer(const std::string n,const std::vector<T>& dat,int dim)
				:name(n),data(dat),dimension(dim){};
			std::string name;
			std::vector<T> data;
			int dimension;
		};
		
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