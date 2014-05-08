#include "flake/framework/display.hpp"
#include "flake/framework/camera.hpp"
#include "oldmesh.h"
#include "flake/gl/mesh.h"
#include <iostream>
#include <fstream>
flake::gl::Mesh* getMeshFromFile(std::string dataf,std::string v,std::string f)
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
	
	return new flake::gl::Mesh(buffers,idx,v,f,drawmode);
}
int main()
{
    int x=1000,y=600;
    flake::Display f("triangle",x,y);
    flake::CenteredOrtho2D cam(x,y,0,0);
    
//     mm::OldMesh* mesh=new mm::OldMesh("righttri","vert.glsl","frag.glsl");
   auto mesh =getMeshFromFile("righttri","vert.glsl","frag.glsl"); 

    glClearColor(1,1,1,1);
    
//     mesh->getProgram()->uniformMat4(c.getMatrix(),"camera");
	int oldx=0,oldy=0;
	float scale=1;
	int percent=5;
    while(f.update())
    {
        glClear(GL_COLOR_BUFFER_BIT);
		
        mesh->getProgram()->uniformMat4(cam.getMatrix(),"camera");
        mesh->draw();
		
		
        auto callback=[&](sf::Event eve)
        {
            if(eve.type==sf::Event::Closed)
                f.close();
            else if (eve.type==sf::Event::MouseMoved)
			{
				int mx=eve.mouseMove.x;
                int my=eve.mouseMove.y;
                cam.fix_input(mx,my);
				
				if(oldx==0 && oldy==0)
				{
					oldx=mx;
					oldy=my;
					mx=0;
					my=0;
				}
				else
				{
					mx-=oldx;
					my-=oldy;
					oldx+=mx;
					oldy+=my;
				}
				
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					cam.shiftView(mx/scale,my/scale);
				}
				
			}
			else if (eve.type == sf::Event::MouseWheelMoved)
			{
				int mx=eve.mouseWheel.x;
				int my=eve.mouseWheel.y;
				int md=eve.mouseWheel.delta;
				
				cam.fix_input(mx,my);
				cam.zoom(md*percent);
				scale+=(scale*md*percent/100);
				
				
			}
        };
        
        f.placeHolderEventHandler(callback);
    }
}