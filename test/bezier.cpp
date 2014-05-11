#include <iostream>
#include <vector>
struct Point
{
	Point(){};
	Point(float x_,float y_):x(x_),y(y_){}
	float x,y;
};
Point interpol(Point x,Point y,float t)
{
	float a=x.x*t+y.x*(1-t);
	float b=x.y*t+y.y*(1-t);
	return Point(a,b);
}
Point bezier(std::vector<Point>& pts,int l,int r,float t)
{
	if( r-l == 1)
	{
		return interpol(pts[l],pts[r],t);
	}
	else 
		return interpol
		(bezier(pts,l,r-1,t),bezier(pts,l+1,r,t),t);
}
int main()
{
	int n;
	std::cin>>n;
	std::vector<Point> pts(n);
	for(int i=0;i<n;++i)
		std::cin>>pts[i].x>>pts[i].y;
	std::cout<<"#col1   col2\n";
	for(float f=0.0;f<1.0;f+=0.01)
	{
		auto p=bezier(pts,0,pts.size()-1,f);
		std::cout<<p.x<<' '<<p.y<<std::endl;
	}
}