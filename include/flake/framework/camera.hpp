#ifndef FLAKE_FRAMEWORK_CAMERA_HPP
#define FLAKE_FRAMEWORK_CAMERA_HPP
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace flake
{
    //TODO:Needs a policy based design
    
    class Camera
    {
    public:
        virtual glm::mat4 getMatrix(){return glm::mat4(1.0f);};//returns p*v
//         virtual glm::mat4 getView(){return glm::mat4(1.0f);}; 
//         virtual glm::mat4 getProjection(){return glm::mat4(1.0f);}; 
    };
    
    
    class CenteredOrtho2D:public Camera
    {
    public:
        CenteredOrtho2D(int sx,int sy,int tx=0,int ty=0):sizex(sx),sizey(sy),transx(tx),transy(ty){}
        glm::mat4 getMatrix()
        {
			return generateProj(sizex,sizey)*generateView(transx,transy);
        }
        void setView(int x,int y)
        {
			transx=x;
			transy=y;
        }
        void shiftView(int x,int y)
        {
			transx+=x;
			transy+=y;
        }
        void setSize(int x,int y)
        {
			sizex=x;
			sizey=y;
        }
        void fix_input(int &x,int& y)
        {
            y= sizey-y;
            x-=sizex/2;
            y-=sizey/2;
        }
        void zoom(int factor)//10 = 10% zoom in ; -10 = 10% zoom out
		{
			sizex=sizex-sizex*factor/100;
			sizey=sizey-sizey*factor/100;
		}
    private:
        glm::mat4 generateProj(float x,float y)
        {
            return glm::ortho(-x/2,x/2,-y/2,y/2);
        }
        glm::mat4 generateView(float x,float y)
        {
            return glm::translate(glm::mat4(1.0f), glm::vec3(x, y,0));
        }
        int sizex;
        int sizey;
        int transx;
        int transy;
    };
}
#endif