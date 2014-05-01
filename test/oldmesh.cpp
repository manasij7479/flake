/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  Manasij Mukherjee <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "oldmesh.h"
#include<fstream>
#include<sstream>
#include<stdexcept>
#include<iostream>
namespace mm
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
	OldMesh::OldMesh(std::string dataf, flake::gl::Program* prog_)
	{
		prog = prog_;
		glUseProgram(prog->getHandle());
		std::ifstream dat(dataf);
		if(!dat)
			throw(std::runtime_error("File: "+dataf+" not found."));
		
		glGenVertexArrays(1,&vao);
		glBindVertexArray(vao);
		
		std::string name;
		while(dat>>name)
		{
			if(name=="index")
			{
				int &x=isize;
				dat>>x;
				GLuint ibo;
				GLubyte* index = new GLubyte[x];
				for(int i=0;i<x;++i)
				{
					int temp;
					dat>>temp;
					index[i]=static_cast<GLubyte>(temp);
				}
				glGenBuffers(1,&ibo);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER,x*sizeof(GLubyte),index,GL_STATIC_DRAW);
				
				vbomap["index"]=ibo;
			}
			if(name=="draw")
			{
				std::string mode;
				dat>>mode;
				drawmode=modeTable[mode];
			}
			else
			{
				int m,n;
				dat>>m>>n;
				GLuint vbo;
				GLfloat* data=new GLfloat[m*n];
				for(int i=0;i<m*n;++i)
				{
					dat>>data[i];
				}
				glGenBuffers(1,&vbo);
				glBindBuffer(GL_ARRAY_BUFFER,vbo);
				glBufferData(GL_ARRAY_BUFFER,m*n*sizeof(GLfloat),data,GL_STATIC_DRAW);
				GLint loc = glGetAttribLocation(prog->getHandle(),name.c_str());
				glVertexAttribPointer(loc,n,GL_FLOAT,GL_FALSE,0,0);
				glEnableVertexAttribArray(loc);
				
				vbomap[name]=vbo;
			}
		}
	}

	OldMesh::OldMesh(std::string dataf, std::string vsf, std::string fsf):
	OldMesh //Delegated constructor 
	(
		dataf,
		new flake::gl::Program
		(
			{
				flake::gl::Shader(GL_VERTEX_SHADER,vsf),
				flake::gl::Shader(GL_FRAGMENT_SHADER,fsf)
			}
		)
	)
	{
	}
	void OldMesh::draw()
	{
		glUseProgram(prog->getHandle());
		glBindVertexArray(vao);
		glDrawElements(drawmode,isize,GL_UNSIGNED_BYTE,0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}

