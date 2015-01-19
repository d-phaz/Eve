
#version 420

#define FRAG_COLOR	0
#define UNI_DIFFUSE	1

layout(binding = UNI_DIFFUSE) uniform sampler2D UniDiffuse;

in block
{
	vec2 Texcoord;
} In;

layout(location = FRAG_COLOR, index = 0) out vec4 FragColor;

void main()
{
	FragColor = texture(UniDiffuse, In.Texcoord);
}
