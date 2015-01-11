
#version 420

#define ATTR_POSITION	0
#define ATTR_DIFFUSE	4

#define UNI_TRANSFORM	1

layout(binding = UNI_TRANSFORM) uniform transform
{
	mat4 MVP;
} Transform;

layout(location = ATTR_POSITION) in vec2 AttrPosition;
layout(location = ATTR_DIFFUSE)  in vec4 AttrColor;

out gl_PerVertex
{
	vec4 gl_Position;
};

out block
{
	vec4 Color;
} Out;

void main()
{	
	Out.Color   = AttrColor;
	gl_Position = Transform.MVP * vec4(AttrPosition, 0.0, 1.0);
}
