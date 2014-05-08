#include "flake/framework/display.hpp"
#include "flake/framework/camera.hpp"
#include "oldmesh.h"
#include<iostream>
int main()
{
    int x=1000,y=600;
    flake::Display f("triangle",x,y);
    flake::CenteredOrtho2D cam(x,y,0,0);
    
    mm::OldMesh* mesh=new mm::OldMesh("righttri","vert.glsl","frag.glsl");
    

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