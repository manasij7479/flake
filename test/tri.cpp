#include "flake/framework/display.hpp"
#include "flake/framework/camera.hpp"
#include "oldmesh.h"

int main()
{
    int x=1000,y=600;
    flake::Display f("triangle",x,y);
    flake::CenteredOrtho2D c(x,y,0,0);
    
    mm::OldMesh* mesh;
    
    mesh = new mm::OldMesh("righttri","vert.glsl","frag.glsl");
    glClearColor(1,1,1,1);
    
    mesh->getProgram()->uniformMat4(c.getMatrix(),"camera");
    
    while(f.update())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        mesh->draw();
        f.placeHolderEventHandler();
    }
}