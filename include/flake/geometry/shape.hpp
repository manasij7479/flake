#ifndef FLAKE_GEOMETRY_SHAPE_HPP
#define FLAKE_GEOMETRY_SHAPE_HPP
#include "drawable.hpp"
#include <vector>
#include <array>
#include <glm/glm.hpp>
#include <flake/gl/mesh.hpp>
#include <flake/gl/buffer.hpp>
#include <sstream>
namespace flake
{
	class Shape:public Drawable
	{
	public:
		virtual void draw()=0;
		virtual bool isWithin(float x,float y)=0;
	};
	
	class Triangle:public Shape
	{
	public:
		Triangle(std::vector<float> pts,glm::vec4 col)
		{
			gl::Buffer<float> buf(std::string("pos"),pts,2);
			std::string vss=
"#version 130\n\
in vec2 pos;\n\
\n\
void main()\n\
{\n\
	gl_Position=vec4(pos,0.0f,1.0f);\n\
\n\
}\n\
";
			std::string fss=
"#version 130\n\
uniform vec4 col;\n\
out vec4 outcol;\n\
void main()\n\
{outcol=col;}\n\
";
			gl::Shader vs(GL_VERTEX_SHADER,std::istringstream(vss));
			gl::Shader fs(GL_FRAGMENT_SHADER,std::istringstream(fss));
			mesh =new gl::Mesh({buf},{0,1,2},vs,fs,GL_TRIANGLES);
			mesh->getProgram()->uniformVec4(col,"col");
		}
		void draw(){mesh->draw();};
		bool isWithin(float x,float y){return true;}
	private:
		gl::Mesh* mesh;
	};
}
#endif