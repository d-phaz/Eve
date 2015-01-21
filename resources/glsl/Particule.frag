#version 430

in vec2 ex_TexCoor;
out vec4 outputColor;

uniform sampler2D texture;
uniform float time;

void main(void){
	vec4 bufferColor = texture2D(texture, ex_TexCoor)*8;
  
	float red, green, blue;
  
	red 	= -0.5 + cos(time*0.4+1.5)*0.5;
	green = -0.5 + cos(time*0.6)*sin(time*0.3)*0.35;
	blue 	= -0.5 + sin(time*0.2)*0.5;
	
	//if (bufferColor.w < 1) 
	//bufferColor = vec4(0,1,0,1);
	//else
	{
	bufferColor.x = bufferColor.x + red;
	bufferColor.y = bufferColor.y + green;
	bufferColor.z = bufferColor.z  + blue;
	}
  
	outputColor = bufferColor;
}