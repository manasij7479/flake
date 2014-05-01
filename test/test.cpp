#include "flake/framework/display.hpp"

int main()
{
    flake::Display display("Manasij",800,600);
    while(display.update())
        display.placeHolderEventHandler();
    return 0;
}