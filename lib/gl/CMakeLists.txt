add_library(GlewContext SHARED glewcontext.cpp)
add_library(Program SHARED program.cpp)
add_library(Shader SHARED shader.cpp)
add_library(Mesh SHARED mesh.cpp)

add_library(Gl empty.cpp)
target_link_libraries(Gl 
    GlewContext GL GLEW
    Program
    Shader
    Mesh
)