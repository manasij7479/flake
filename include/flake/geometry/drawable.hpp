#ifndef FLAKE_GEOMETRY_DRAWABLE_HPP
#define FLAKE_GEOMETRY_DRAWABLE_HPP
#include <flake/gl/mesh.hpp>
namespace flake
{
	class Drawable
	{
	public:
		virtual void draw()=0;
		virtual bool isWithin(float x,float y)=0;
	};
}
#endif
