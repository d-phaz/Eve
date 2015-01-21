
#version 420

#define ATTRIBUTE_POSITION	0
#define ATTRIBUTE_DIFFUSE	4
#define ATTRIBUTE_NORMAL	7

#define TRANSFORM_CAMERA	1
#define TRANSFORM_MODEL		2
#define TRANSFORM_SKELETON	3	
	

// Camera matrix.
layout(binding = TRANSFORM_CAMERA) uniform camera
{
	mat4 mat_model_view;
	mat4 mat_projection;
} tran_camera;
// Model matrix.
layout(binding = TRANSFORM_MODEL) uniform model
{
	mat4 matrix;
} tran_model;


// Mesh data.
layout(location = ATTRIBUTE_POSITION) 	in vec3 attr_position;
layout(location = ATTRIBUTE_DIFFUSE)  	in vec2 attr_texcoord;
layout(location = ATTRIBUTE_NORMAL)		in vec3 attr_normal;


// Intrinsic output.
out gl_PerVertex
{
	vec4 gl_Position;
};
// Declared output.
out block
{
	vec3 position;
	vec2 texcoord;
	vec3 normal;
} out_block;


// Entry point.
void main()
{	
	mat4 modelMatrix 	= tran_camera.mat_model_view * tran_model.matrix;

	out_block.position	= (modelMatrix * vec4(attr_position, 1.0) ).xyz;
	out_block.texcoord 	= attr_texcoord;
	out_block.normal 	= (modelMatrix * vec4(attr_normal, 0.0) ).xyz;
	
	gl_Position = tran_camera.mat_projection * vec4(out_block.position, 1.0);
}







