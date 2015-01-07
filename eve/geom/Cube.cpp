
// Main class
#include "eve/geom/Cube.h"


//=================================================================================================
GLuint * eve::geom::create_cube_indices(void)
{
	GLuint * indices = (GLuint*)malloc(36 * sizeof(GLuint));
	GLuint * ind = indices - 1;
	// Front
	*++ind = 0;
	*++ind = 1;
	*++ind = 2;
	*++ind = 0;
	*++ind = 2;
	*++ind = 3;
	// Right
	*++ind = 4;
	*++ind = 5;
	*++ind = 6;
	*++ind = 4;
	*++ind = 6;
	*++ind = 7;
	// Back
	*++ind = 8;
	*++ind = 9;
	*++ind = 10;
	*++ind = 8;
	*++ind = 10;
	*++ind = 11;
	// Left
	*++ind = 12;
	*++ind = 13;
	*++ind = 14;
	*++ind = 12;
	*++ind = 14;
	*++ind = 15;
	// Bottom
	*++ind = 16;
	*++ind = 17;
	*++ind = 18;
	*++ind = 16;
	*++ind = 18;
	*++ind = 19;
	// Top
	*++ind = 20;
	*++ind = 21;
	*++ind = 22;
	*++ind = 20;
	*++ind = 22;
	*++ind = 23;

	return indices;
}



//=================================================================================================
float * eve::geom::create_cube_textured_vertices(const eve::vec3f & p_position, const eve::vec3f & p_size)
{
	float * vertices = (float*)malloc((24 * 8) * sizeof(float));

	float posX = p_position.x;
	float posY = p_position.y;
	float posZ = p_position.z;

	float sizeX = p_size.x * 0.5f;
	float sizeY = p_size.y * 0.5f;
	float sizeZ = p_size.z * 0.5f;

	float * vert = vertices - 1;

	// 1
	*++vert = posX + sizeX;		*++vert = posY + sizeY;		*++vert = posZ + sizeZ;
	*++vert = 0.0f;				*++vert = 1.0f;
	*++vert = 1.0f;				*++vert = 0.0f;				*++vert = 0.0f;
	// 2
	*++vert = posX + sizeX;		*++vert = posY - sizeY;		*++vert = posZ + sizeZ;
	*++vert = 1.0f;				*++vert = 1.0f;
	*++vert = 1.0f;				*++vert = 0.0f;				*++vert = 0.0f;
	// 3
	*++vert = posX + sizeX;		*++vert = posY - sizeY;		*++vert = posZ - sizeZ;
	*++vert = 1.0f;				*++vert = 0.0f;
	*++vert = 1.0f;				*++vert = 0.0f;				*++vert = 0.0f;
	// 4
	*++vert = posX + sizeX;		*++vert = posY + sizeY;		*++vert = posZ - sizeZ;
	*++vert = 0.0f;				*++vert = 0.0f;
	*++vert = 1.0f;				*++vert = 0.0f;				*++vert = 0.0f;

	// 1
	*++vert = posX + sizeX;		*++vert = posY + sizeY;		*++vert = posZ + sizeZ;
	*++vert = 1.0f;				*++vert = 1.0f;
	*++vert = 0.0f;				*++vert = 1.0f;				*++vert = 0.0f;
	// 2
	*++vert = posX + sizeX;		*++vert = posY + sizeY;		*++vert = posZ - sizeZ;
	*++vert = 1.0f;				*++vert = 0.0f;
	*++vert = 0.0f;				*++vert = 1.0f;				*++vert = 0.0f;
	// 3
	*++vert = posX - sizeX;		*++vert = posY + sizeY;		*++vert = posZ - sizeZ;
	*++vert = 0.0f;				*++vert = 0.0f;
	*++vert = 0.0f;				*++vert = 1.0f;				*++vert = 0.0f;
	// 4
	*++vert = posX - sizeX;		*++vert = posY + sizeY;		*++vert = posZ + sizeZ;
	*++vert = 0.0f;				*++vert = 1.0f;
	*++vert = 0.0f;				*++vert = 1.0f;				*++vert = 0.0f;

	// 1
	*++vert = posX + sizeX;		*++vert = posY + sizeY;		*++vert = posZ + sizeZ;
	*++vert = 0.0f;				*++vert = 1.0f;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = 1.0f;
	// 2
	*++vert = posX - sizeX;		*++vert = posY + sizeY;		*++vert = posZ + sizeZ;
	*++vert = 1.0f;				*++vert = 1.0f;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = 1.0f;
	// 3
	*++vert = posX - sizeX;		*++vert = posY - sizeY;		*++vert = posZ + sizeZ;
	*++vert = 1.0f;				*++vert = 0.0f;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = 1.0f;
	// 4
	*++vert = posX + sizeX;		*++vert = posY - sizeY;		*++vert = posZ + sizeZ;
	*++vert = 0.0f;				*++vert = 0.0f;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = 1.0f;

	// 1
	*++vert = posX - sizeX;		*++vert = posY + sizeY;		*++vert = posZ + sizeZ;
	*++vert = 1.0f;				*++vert = 1.0f;
	*++vert = -1.0f;				*++vert = 0.0f;				*++vert = 0.0f;
	// 2
	*++vert = posX - sizeX;		*++vert = posY + sizeY;		*++vert = posZ - sizeZ;
	*++vert = 1.0f;				*++vert = 0.0f;
	*++vert = -1.0f;				*++vert = 0.0f;				*++vert = 0.0f;
	// 3
	*++vert = posX - sizeX;		*++vert = posY - sizeY;		*++vert = posZ - sizeZ;
	*++vert = 0.0f;				*++vert = 0.0f;
	*++vert = -1.0f;				*++vert = 0.0f;				*++vert = 0.0f;
	// 4
	*++vert = posX - sizeX;		*++vert = posY - sizeY;		*++vert = posZ + sizeZ;
	*++vert = 0.0f;				*++vert = 1.0f;
	*++vert = -1.0f;				*++vert = 0.0f;				*++vert = 0.0f;

	// 1
	*++vert = posX - sizeX;		*++vert = posY - sizeY;		*++vert = posZ - sizeZ;
	*++vert = 1.0f;				*++vert = 0.0f;
	*++vert = 0.0f;				*++vert = -1.0f;				*++vert = 0.0f;
	// 2
	*++vert = posX + sizeX;		*++vert = posY - sizeY;		*++vert = posZ - sizeZ;
	*++vert = 0.0f;				*++vert = 0.0f;
	*++vert = 0.0f;				*++vert = -1.0f;				*++vert = 0.0f;
	// 3
	*++vert = posX + sizeX;		*++vert = posY - sizeY;		*++vert = posZ + sizeZ;
	*++vert = 0.0f;				*++vert = 1.0f;
	*++vert = 0.0f;				*++vert = -1.0f;				*++vert = 0.0f;
	// 4
	*++vert = posX - sizeX;		*++vert = posY - sizeY;		*++vert = posZ + sizeZ;
	*++vert = 1.0f;				*++vert = 1.0f;
	*++vert = 0.0f;				*++vert = -1.0f;				*++vert = 0.0f;

	// 1
	*++vert = posX + sizeX;		*++vert = posY - sizeY;		*++vert = posZ - sizeZ;
	*++vert = 1.0f;				*++vert = 0.0f;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = -1.0f;
	// 2
	*++vert = posX - sizeX;		*++vert = posY - sizeY;		*++vert = posZ - sizeZ;
	*++vert = 0.0f;				*++vert = 0.0f;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = -1.0f;
	// 3
	*++vert = posX - sizeX;		*++vert = posY + sizeY;		*++vert = posZ - sizeZ;
	*++vert = 0.0f;				*++vert = 1.0f;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = -1.0f;
	// 4
	*++vert = posX + sizeX;		*++vert = posY + sizeY;		*++vert = posZ - sizeZ;
	*++vert = 1.0f;				*++vert = 1.0f;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = -1.0f;

	return vertices;
}

//=================================================================================================
float * eve::geom::create_cube_colored_vertices(const eve::vec3f & p_position, const eve::vec3f & p_size, const eve::color4f & p_color)
{
	float * vertices = (float*)malloc(240 * sizeof(float));

	float posX = p_position.x;
	float posY = p_position.y;
	float posZ = p_position.z;

	float sizeX = p_size.x * 0.5f;
	float sizeY = p_size.y * 0.5f;
	float sizeZ = p_size.z * 0.5f;

	float red	= p_color.x;
	float green = p_color.y;
	float blue	= p_color.z;
	float alpha = p_color.w;

	float * vert = vertices - 1;

	// 1
	*++vert = posX + sizeX;		*++vert = posY + sizeY;		*++vert = posZ + sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 1.0f;				*++vert = 0.0f;				*++vert = 0.0f;
	// 2
	*++vert = posX + sizeX;		*++vert = posY - sizeY;		*++vert = posZ + sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 1.0f;				*++vert = 0.0f;				*++vert = 0.0f;
	// 3
	*++vert = posX + sizeX;		*++vert = posY - sizeY;		*++vert = posZ - sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 1.0f;				*++vert = 0.0f;				*++vert = 0.0f;
	// 4
	*++vert = posX + sizeX;		*++vert = posY + sizeY;		*++vert = posZ - sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 1.0f;				*++vert = 0.0f;				*++vert = 0.0f;

	// 1
	*++vert = posX + sizeX;		*++vert = posY + sizeY;		*++vert = posZ + sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = 1.0f;				*++vert = 0.0f;
	// 2
	*++vert = posX + sizeX;		*++vert = posY + sizeY;		*++vert = posZ - sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = 1.0f;				*++vert = 0.0f;
	// 3
	*++vert = posX - sizeX;		*++vert = posY + sizeY;		*++vert = posZ - sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = 1.0f;				*++vert = 0.0f;
	// 4
	*++vert = posX - sizeX;		*++vert = posY + sizeY;		*++vert = posZ + sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = 1.0f;				*++vert = 0.0f;

	// 1
	*++vert = posX + sizeX;		*++vert = posY + sizeY;		*++vert = posZ + sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = 1.0f;
	// 2
	*++vert = posX - sizeX;		*++vert = posY + sizeY;		*++vert = posZ + sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = 1.0f;
	// 3
	*++vert = posX - sizeX;		*++vert = posY - sizeY;		*++vert = posZ + sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = 1.0f;
	// 4
	*++vert = posX + sizeX;		*++vert = posY - sizeY;		*++vert = posZ + sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = 1.0f;

	// 1
	*++vert = posX - sizeX;		*++vert = posY + sizeY;		*++vert = posZ + sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = -1.0f;				*++vert = 0.0f;				*++vert = 0.0f;
	// 2
	*++vert = posX - sizeX;		*++vert = posY + sizeY;		*++vert = posZ - sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = -1.0f;				*++vert = 0.0f;				*++vert = 0.0f;
	// 3
	*++vert = posX - sizeX;		*++vert = posY - sizeY;		*++vert = posZ - sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = -1.0f;				*++vert = 0.0f;				*++vert = 0.0f;
	// 4
	*++vert = posX - sizeX;		*++vert = posY - sizeY;		*++vert = posZ + sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = -1.0f;				*++vert = 0.0f;				*++vert = 0.0f;

	// 1
	*++vert = posX - sizeX;		*++vert = posY - sizeY;		*++vert = posZ - sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = -1.0f;				*++vert = 0.0f;
	// 2
	*++vert = posX + sizeX;		*++vert = posY - sizeY;		*++vert = posZ - sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = -1.0f;				*++vert = 0.0f;
	// 3
	*++vert = posX + sizeX;		*++vert = posY - sizeY;		*++vert = posZ + sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = -1.0f;				*++vert = 0.0f;
	// 4
	*++vert = posX - sizeX;		*++vert = posY - sizeY;		*++vert = posZ + sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = -1.0f;				*++vert = 0.0f;

	// 1
	*++vert = posX + sizeX;		*++vert = posY - sizeY;		*++vert = posZ - sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = -1.0f;
	// 2
	*++vert = posX - sizeX;		*++vert = posY - sizeY;		*++vert = posZ - sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = -1.0f;
	// 3
	*++vert = posX - sizeX;		*++vert = posY + sizeY;		*++vert = posZ - sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = -1.0f;
	// 4
	*++vert = posX + sizeX;		*++vert = posY + sizeY;		*++vert = posZ - sizeZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = -1.0f;

	return vertices;
}



//=================================================================================================
eve::ogl::FormatVao eve::geom::create_cube_textured(const eve::vec3f & p_position, const eve::vec3f & p_size)
{
	eve::ogl::FormatVao ret;

	ret.numVertices					= 24;
	ret.numIndices					= 36;
	
	ret.perVertexNumPosition		= 3;
	ret.perVertexNumDiffuse			= 2;
	ret.perVertexNumNormal			= 3;

	float * vertices = eve::geom::create_cube_textured_vertices(p_position, p_size);
	ret.vertices.reset(vertices);

	GLuint * indices = eve::geom::create_cube_indices();
	ret.indices.reset(indices);

	return ret;
}

//=================================================================================================
eve::ogl::FormatVao eve::geom::create_cube_colored(const eve::vec3f & p_position, const eve::vec3f & p_size, const eve::color4f & p_color)
{
	eve::ogl::FormatVao ret;

	ret.numVertices					= 24;
	ret.numIndices					= 36;
	
	ret.perVertexNumPosition		= 3;
	ret.perVertexNumDiffuse			= 4;
	ret.perVertexNumNormal			= 3;

	float * vertices = eve::geom::create_cube_colored_vertices(p_position, p_size, p_color);
	ret.vertices.reset(vertices);

	GLuint * indices = eve::geom::create_cube_indices();
	ret.indices.reset(indices);


	return ret;
}
