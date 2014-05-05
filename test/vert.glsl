#version 130
uniform mat4 camera;
in vec2 pos;
in vec4 col;
out vec4 interpol;

void main()
{
	gl_Position=camera*vec4(pos,0.0f,1.0f);
	interpol = col;
}