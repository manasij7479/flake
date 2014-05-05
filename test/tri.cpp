#include "flake/framework/display.hpp"
#include "flake/framework/camera.hpp"
#include "oldmesh.h"
#include<iostream>
int main()
{
    int x=1000,y=600;
    flake::Display f("triangle",x,y);
    flake::CenteredOrtho2D c(x,y,0,0);
    
    mm::OldMesh* mesh=new mm::OldMesh("righttri","vert.glsl","frag.glsl");
    

    glClearColor(1,1,1,1);
    
//     mesh->getProgram()->uniformMat4(c.getMatrix(),"camera");
//     int lastx=0,lasty=0;
    while(f.update())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        mesh->getProgram()->uniformMat4(c.getMatrix(),"camera");
        mesh->draw();
        auto callback=[&](sf::Event eve)
        {
            if(eve.type==sf::Event::Closed)
                f.close();
        };
        
        f.placeHolderEventHandler(callback);
    }
}