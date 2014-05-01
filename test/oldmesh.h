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


#ifndef OLDMESH_H
#define OLDMESH_H
#include "flake/gl/program.h"
#include <map>
namespace mm
{
	class OldMesh
	{
	public:
		OldMesh(std::string dataf,std::string vsf,std::string fsf);//File names
		OldMesh(std::string dataf,flake::gl::Program* prog_);
		void draw();
		flake::gl::Program* getProgram()
		{
			return prog;
		}
		~OldMesh(){delete prog;};
	private:
		flake::gl::Program* prog;
		GLuint vao;
		std::map<std::string,GLuint> vbomap;
		GLenum drawmode;
		int isize;
	};
	
}
#endif // OLDMESH_H
