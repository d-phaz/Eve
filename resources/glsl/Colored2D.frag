
#version 420

#define FRAG_COLOR	0

in block
{
	vec4 Color;
} In;

layout(location = FRAG_COLOR, index = 0) out vec4 FragColor;

void main()
{
	FragColor = In.Color;
}
