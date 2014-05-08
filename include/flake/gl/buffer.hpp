#ifndef FLAKE_GL_BUFFER_HPP
#define FLAKE_GL_BUFFER_HPP
namespace flake
{
	namespace gl
	{
		template<typename T>
		class Buffer
		{
		public:
			Buffer(const std::string n,const std::vector<T>& dat,int dim)
				:name(n),data(dat),dimension(dim){};
			std::string name;
			std::vector<T> data;
			int dimension;
		};
		
	}
}
#endif