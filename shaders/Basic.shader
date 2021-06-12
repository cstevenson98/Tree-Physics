#shader vertex 
#version 410 core

layout(location = 0) in vec2 position;
void main()
{
	gl_Position = vec4(position, 1.,1.);
};

#shader fragment
#version 410 core

layout(location = 0) out vec4 colour;
uniform vec4 u_Colour;
void main()
{
	gl_FragColor = vec4(1., 1., 1., 1.);
};
