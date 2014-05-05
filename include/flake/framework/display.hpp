#ifndef FLAKE_FRAMEWORK_HPP
#define FLAKE_FRAMEWORK_HPP

#include <SFML/Window.hpp>
#include "flake/gl/context.hpp"
#include <functional>
namespace flake
{
    class Display
    {
    public:
        Display(std::string n,int x=1000,int y=600);
//         int operator()();
        int update();
        void placeHolderEventHandler(std::function<void(sf::Event)> f);
        
//         void setupFunction(std::function<void()> f){setup=f;}
//         void drawFunction(std::function<void()> f){draw = f;}
//         void mouseAnyFunction(std::function<void(int,int)> f){mousePressAny=f;}
//         void keyAnyFunction(std::function<void()> f){keyPressAny=f;}
//         void resizeFunction(std::function<void(int,int)> f){resize=f;}
        
        int getX(){return winSizeX;};
        int getY(){return winSizeY;};
        void close(){win.close();}
    private:
//         std::function<void()> setup;
//         std::function<void()> draw;
//         std::function<void()> keyPressAny;
//         std::function<void(int,int)> resize;
//         std::function<void(int,int)> mousePressAny;
        
        std::string winName;
        int winSizeX,winSizeY;
        sf::Window& win;
        gl::Context* glc;
    };
}

#endif