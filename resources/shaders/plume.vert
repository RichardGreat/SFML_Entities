#version 150 compatibility 

out vec4 v_color;          

void main()
{
	v_color = gl_Color;      
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
