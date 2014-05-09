#include "flake/gl/mesh.hpp"
#include<fstream>
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
				GLint loc = prog->attribLocation(buffer.name);
				glEnableVertexAttribArray(loc);
				glVertexAttribPointer(loc,n,GL_FLOAT,GL_FALSE,0,0);
				
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				
				
				vbomap[buffer.name]=vbo;
			}
			glBindVertexArray(0);
		}
		void Mesh::draw()
		{
			glUseProgram(prog->getHandle());
			glBindVertexArray(vao);
			glDrawElements(drawmode,isize,GL_UNSIGNED_INT,0);
			glBindVertexArray(0);
			glUseProgram(0);
		}
		Mesh* getMeshFromFile(std::string dataf,std::string v,std::string f)
		{
			std::map<std::string,GLenum> modeTable=
			{
				{"GL_QUADS",GL_QUADS},
				{"GL_LINE_LOOP",GL_LINE_LOOP},
				{"GL_LINES",GL_LINES},
				{"GL_POINTS",GL_POINTS},
				{"GL_LINE_STRIP",GL_LINE_STRIP},
				{"GL_TRIANGLE_STRIP",GL_TRIANGLE_STRIP},
				{"GL_TRIANGLE_FAN",GL_TRIANGLE_FAN},
				{"GL_TRIANGLES",GL_TRIANGLES},
				{"GL_QUAD_STRIP",GL_QUAD_STRIP},
				{"GL_POLYGON",GL_POLYGON}
			};
			
			std::ifstream dat(dataf);
			if(!dat)
				throw(std::runtime_error("File: "+dataf+" not found."));


			std::vector<GLuint> idx;
			std::vector<flake::gl::Buffer<GLfloat>> buffers;
			GLenum drawmode;
			std::string name;
			while(dat>>name)
			{
				if(name=="index")
				{
					int x;
					dat>>x;
					for(int i=0;i<x;++i)
					{
						int temp;
						dat>>temp;
						idx.push_back(static_cast<GLuint>(temp));
					}
				}
				else if(name=="draw")
				{
					std::string mode;
					dat>>mode;
					drawmode=modeTable[mode];
				}
				else
				{
					int m,n;
					dat>>m>>n;
					std::vector<GLfloat> data;
					for(int i=0;i<m*n;++i)
					{
						GLfloat f;
						dat>>f;
						data.push_back(f);
					}
					flake::gl::Buffer<GLfloat> buf(name,data,n);
					buffers.push_back(buf);
				}
			}
			
			return new Mesh(buffers,idx,v,f,drawmode);
		}
	}
	
}