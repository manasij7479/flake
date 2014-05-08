#include "flake/gl/mesh.hpp"
namespace flake
{
	namespace gl
	{
		Mesh::Mesh(std::vector<Buffer<GLfloat>> bufs,std::vector<GLuint> idx,
				 std::string vsf,std::string fsf,GLenum dm)
		{
			drawmode=dm;
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
		void Mesh::draw()
		{
			glUseProgram(prog->getHandle());
			glBindVertexArray(vao);
			glDrawElements(drawmode,isize,GL_UNSIGNED_INT,0);
			glBindVertexArray(0);
			glUseProgram(0);
		}
	}
	
}