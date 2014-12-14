
#version 420

#define ATTR_POSITION	0
#define ATTR_DIFFUSE	4

#define UNI_TRANSFORM	1

layout(binding = UNI_TRANSFORM) uniform transform
{
	mat4 MVP;
} Transform;

layout(location = ATTR_POSITION) in vec2 AttrPosition;
layout(location = ATTR_DIFFUSE)  in vec2 AttrTexcoord;

out block
{
	vec2 Texcoord;
} Out;

void main()
{	
	Out.Texcoord = AttrTexcoord;
	gl_Position  = Transform.MVP * vec4(AttrPosition, 0.0, 1.0);
}
