#ifndef FLAKE_GL_MESH_HPP
#define FLAKE_GL_MESH_HPP
#include "program.h"
#include <vector>
#include <map>
namespace flake
{
// 	class OldMesh
// 	{
// 	public:
// 		OldMesh(std::string dataf,std::string vsf,std::string fsf);//File names
// 		OldMesh(std::string dataf,Program* prog_);
// 		void draw();
// 		Program* getProgram()
// 		{
// 			return prog;
// 		}
// 		~OldMesh(){delete prog;};
// 	private:
// 		Program* prog;
// 		GLuint vao;
// 		std::map<std::string,GLuint> vbomap;
// 		GLenum drawmode;
// 		int isize;
// 	};
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
				 std::string vsf,std::string fsf,GLenum dm)
				:/*buffers(bufs),index(idx),*/drawmode(dm)
			{
				prog=new Program
				(
					{
						Shader(GL_VERTEX_SHADER,vsf),
						Shader(GL_FRAGMENT_SHADER,fsf)
					}
				);
				
				glUseProgram(prog->getHandle());
				glGenVertexArrays(1,&vao);
				glBindVertexArray(vao);
				
				
				isize=idx.size();
				GLuint ibo;
				GLuint* index = idx.data();
				glGenBuffers(1,&ibo);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER,isize*sizeof(GLuint),index,GL_STATIC_DRAW);
				vbomap["index"]=ibo;
				
				for(auto& buffer:bufs)
				{
					int m,n;
					n=buffer.dimension;
					m=buffer.data.size()/n;
					GLuint vbo;
					GLfloat* data=buffer.data.data();
					
					glGenBuffers(1,&vbo);
					glBindBuffer(GL_ARRAY_BUFFER,vbo);
					glBufferData(GL_ARRAY_BUFFER,buffer.data.size()*sizeof(GLfloat),data,GL_STATIC_DRAW);
					GLint loc = glGetAttribLocation(prog->getHandle(),buffer.name.c_str());
					glVertexAttribPointer(loc,n,GL_FLOAT,GL_FALSE,0,0);
					glEnableVertexAttribArray(loc);
					
					vbomap[buffer.name]=vbo;
				}
			}
			void draw()
			{
				glUseProgram(prog->getHandle());
				glBindVertexArray(vao);
				glDrawElements(drawmode,isize,GL_UNSIGNED_INT,0);
				glBindVertexArray(0);
				glUseProgram(0);
			}
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