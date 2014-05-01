#include "flake/framework/display.hpp"
#include "oldmesh.h"

mm::OldMesh* mesh;
void setup()
{
	glClearColor(1,1,1,1);
	mesh = new mm::OldMesh("righttri","vert.glsl","frag.glsl");
}
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	mesh->draw();
}
int main()
{
    flake::Display f("triangle");
    setup();
    while(f.update())
    {
        draw();
        f.placeHolderEventHandler();
    }
}