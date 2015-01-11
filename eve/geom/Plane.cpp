
// Main class
#include "eve/geom/Plane.h"


//=================================================================================================
GLuint * eve::geom::create_plane_indices(void)
{
	GLuint * indices = (GLuint*)malloc(6 * sizeof(GLuint));
	GLuint * ind = indices - 1;
	*++ind = 0;
	*++ind = 1;
	*++ind = 2;
	*++ind = 2;
	*++ind = 3;
	*++ind = 0;

	return indices;
}



//=================================================================================================
float * eve::geom::create_plane_textured_vertices(const eve::vec3f & p_position, const eve::vec2f & p_size)
{
	float * vertices = (float*)malloc((32) * sizeof(float));

	float posX = p_position.x;
	float posY = p_position.y;
	float posZ = p_position.z;

	float sizeX = p_size.x * 0.5f;
	float sizeY = p_size.y * 0.5f;

	float * vert = vertices - 1;

	// 1
	*++vert = posX - sizeX;		*++vert = posY + sizeY;		*++vert = posZ;
	*++vert = 0.0f;				*++vert = 1.0f;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = 1.0f;
	// 2
	*++vert = posX + sizeX;		*++vert = posY + sizeY;		*++vert = posZ;
	*++vert = 1.0f;				*++vert = 1.0f;
	*++vert = 1.0f;				*++vert = 0.0f;				*++vert = 1.0f;
	// 3
	*++vert = posX + sizeX;		*++vert = posY - sizeY;		*++vert = posZ;
	*++vert = 1.0f;				*++vert = 0.0f;
	*++vert = 1.0f;				*++vert = 0.0f;				*++vert = 1.0f;
	// 4
	*++vert = posX - sizeX;		*++vert = posY - sizeY;		*++vert = posZ;
	*++vert = 0.0f;				*++vert = 0.0f;
	*++vert = 1.0f;				*++vert = 0.0f;				*++vert = 1.0f;

	return vertices;
}

//=================================================================================================
float * eve::geom::create_plane_colored_vertices(const eve::vec3f & p_position, const eve::vec2f & p_size, const eve::color4f & p_color)
{
	float * vertices = (float*)malloc((40) * sizeof(float));

	float posX = p_position.x;
	float posY = p_position.y;
	float posZ = p_position.z;

	float sizeX = p_size.x * 0.5f;
	float sizeY = p_size.y * 0.5f;

	float red = p_color.x;
	float green = p_color.y;
	float blue = p_color.z;
	float alpha = p_color.w;

	float * vert = vertices - 1;

	// 1
	*++vert = posX - sizeX;		*++vert = posY + sizeY;		*++vert = posZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 0.0f;				*++vert = 0.0f;				*++vert = 1.0f;
	// 2
	*++vert = posX + sizeX;		*++vert = posY + sizeY;		*++vert = posZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 1.0f;				*++vert = 0.0f;				*++vert = 1.0f;
	// 3
	*++vert = posX + sizeX;		*++vert = posY - sizeY;		*++vert = posZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 1.0f;				*++vert = 0.0f;				*++vert = 1.0f;
	// 4
	*++vert = posX - sizeX;		*++vert = posY - sizeY;		*++vert = posZ;
	*++vert = red;				*++vert = green;			*++vert = blue;				*++vert = alpha;
	*++vert = 1.0f;				*++vert = 0.0f;				*++vert = 1.0f;

	return vertices;
}



//=================================================================================================
eve::ogl::FormatVao eve::geom::create_plane_textured(const eve::vec3f & p_position, const eve::vec2f & p_size)
{
	eve::ogl::FormatVao ret;

	ret.numVertices					= 4;
	ret.numIndices					= 6;
	
	ret.perVertexNumPosition		= 3;
	ret.perVertexNumDiffuse			= 2;
	ret.perVertexNumNormal			= 3;

	float * vertices = eve::geom::create_plane_textured_vertices(p_position, p_size);
	ret.vertices.reset(vertices);

	GLuint * indices = eve::geom::create_plane_indices();
	ret.indices.reset(indices);

	return ret;
}

//=================================================================================================
eve::ogl::FormatVao eve::geom::create_plane_colored(const eve::vec3f & p_position, const eve::vec2f & p_size, const eve::color4f & p_color)
{
	eve::ogl::FormatVao ret;
	
	ret.numVertices					= 4;
	ret.numIndices					= 6;
	
	ret.perVertexNumPosition		= 3;
	ret.perVertexNumDiffuse			= 4;
	ret.perVertexNumNormal			= 3;

	float * vertices = eve::geom::create_plane_colored_vertices(p_position, p_size, p_color);
	ret.vertices.reset(vertices);

	GLuint * indices = eve::geom::create_plane_indices();
	ret.indices.reset(indices);

	return ret;
}
