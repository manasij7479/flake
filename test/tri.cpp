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
//     int lastx=0,lasty=0;
    while(f.update())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        mesh->getProgram()->uniformMat4(cam.getMatrix(),"camera");
        mesh->draw();
        auto callback=[&](sf::Event eve)
        {
            if(eve.type==sf::Event::Closed)
                f.close();
            if (eve.type == sf::Event::MouseButtonPressed)
            {
                if (eve.mouseButton.button == sf::Mouse::Left)
                {
                    int mx=eve.mouseButton.x;
                    int my=eve.mouseButton.y;
                    cam.fix_input(mx,my);
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " <<mx<< std::endl;
                    std::cout << "mouse y: " <<my<< std::endl;
                    
                }
            }
        };
        
        f.placeHolderEventHandler(callback);
    }
}