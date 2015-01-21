
#version 420

#define FRAG_COLOR	0

// GLSL texture sampler2D indices.
#define  SAMPLER_DIFFUSE		1
#define  SAMPLER_NORMAL			2
#define  SAMPLER_EMISSIVE		3
#define  SAMPLER_OPACITY		4

// Texture samplers.
layout(binding = SAMPLER_DIFFUSE) 	uniform sampler2D uni_diffuse;
layout(binding = SAMPLER_NORMAL) 	uniform sampler2D uni_normal;
layout(binding = SAMPLER_EMISSIVE) 	uniform sampler2D uni_emissive;
layout(binding = SAMPLER_OPACITY) 	uniform sampler2D uni_opacity;

// Declared input.
in block
{
	vec3 position;
	vec2 texcoord;
	vec3 normal;
} in_block;

// Shader output.
layout(location = FRAG_COLOR, index = 0) out vec4 FragColor;

// Entry point.
void main()
{
	// Textures.
	vec4 diffuse	= texture(uni_diffuse, in_block.texcoord);
	vec4 emissive 	= texture(uni_emissive, in_block.texcoord);
	vec4 opacity 	= texture(uni_opacity, in_block.texcoord);

	// Compute color.
	vec4 color = (diffuse * opacity) + emissive;
	
	// Output fragment.
	FragColour = vec4(clamp(color.r, 0.0, 1.0)
					, clamp(color.g, 0.0, 1.0)
					, clamp(color.b, 0.0, 1.0)
					, clamp(color.a, 0.0, 1.0));
}
