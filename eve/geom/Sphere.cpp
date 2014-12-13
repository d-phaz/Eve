
// Main class
#include "eve/geom/Sphere.h"


//=================================================================================================
eve::ogl::FormatVao eve::geom::create_sphere_textured(const eve::vec3f & p_position, float p_radius, int32_t p_segments)
{
	eve::ogl::FormatVao ret;

	ret.numVertices					= p_segments * p_segments;
	ret.numIndices					= ret.numVertices * 6;
	
	ret.perVertexNumPosition		= 3;
	ret.perVertexNumDiffuse			= 2;
	ret.perVertexNumNormal			= 3;


	float * vertices = (float*)malloc((ret.numVertices * 8) * sizeof(float));

	float radius	= p_radius * 0.5f;
	const float S	= 1.0f / static_cast<float>(p_segments - 1);
	const float Pi	= static_cast<float>(M_PI);
	const float Pi2	= static_cast<float>(M_PI_2);

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	float * vert = vertices - 1;
	for (int32_t r = 0; r < p_segments; r++)
	{
		for (int32_t s = 0; s < p_segments; s++)
		{
			y = eve::math::sin(-Pi2 + Pi * r * S);
			x = eve::math::cos(2.0f*Pi * s * S) * eve::math::sin(Pi * r * S);
			z = eve::math::sin(2.0f*Pi * s * S) * eve::math::sin(Pi * r * S);

			*++vert = p_position.x + (x * radius);
			*++vert = p_position.y + (y * radius);
			*++vert = p_position.z + (z * radius);

			*++vert = 1.0f - s*S;
			*++vert = 1.0f - r*S;

			*++vert = x;
			*++vert = y;
			*++vert = z;
		}
	}
	ret.vertices.reset(vertices);


	GLuint * indices = (GLuint*)malloc(ret.numIndices * sizeof(GLuint));
	GLuint * ind = indices - 1;
	for (int32_t r = 0; r < p_segments; r++)
	{
		for (int32_t s = 0; s < p_segments; s++)
		{
			*++ind = s + p_segments*r;
			*++ind = s + 1 + p_segments*r;
			*++ind = p_segments + s + p_segments*r;

			*++ind = p_segments + s + 1 + p_segments*r;
			*++ind = p_segments + s + p_segments*r;
			*++ind = s + 1 + p_segments*r;
		}
	}
	ret.indices.reset(indices);


	return ret;
}

//=================================================================================================
eve::ogl::FormatVao eve::geom::create_sphere_colored(const eve::vec3f & p_position, float p_radius, const eve::color4f & p_color, int32_t p_segments)
{
	eve::ogl::FormatVao ret;

	ret.numVertices					= p_segments * p_segments;
	ret.numIndices					= ret.numVertices * 6;
	
	ret.perVertexNumPosition		= 3;
	ret.perVertexNumDiffuse			= 4;
	ret.perVertexNumNormal			= 3;


	float * vertices = (float*)malloc((ret.numVertices * 10) * sizeof(float));

	float radius    = p_radius * 0.5f;
	const float S   = 1.0f / static_cast<float>(p_segments - 1);
	const float Pi  = static_cast<float>(M_PI);
	const float Pi2 = static_cast<float>(M_PI_2);

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	float * vert = vertices - 1;
	for (int32_t r = 0; r < p_segments; r++)
	{
		for (int32_t s = 0; s < p_segments; s++)
		{
			y = eve::math::sin(-Pi2 + Pi * r * S);
			x = eve::math::cos(2.0f*Pi * s * S) * eve::math::sin(Pi * r * S);
			z = eve::math::sin(2.0f*Pi * s * S) * eve::math::sin(Pi * r * S);

			*++vert = p_position.x + (x * radius);
			*++vert = p_position.y + (y * radius);
			*++vert = p_position.z + (z * radius);

			*++vert = p_color.x;
			*++vert = p_color.y;
			*++vert = p_color.z;
			*++vert = p_color.w;

			*++vert = x;
			*++vert = y;
			*++vert = z;
		}
	}
	ret.vertices.reset(vertices);


	GLuint * indices = (GLuint*)malloc(ret.numIndices * sizeof(GLuint));
	GLuint * ind = indices - 1;
	for (int32_t r = 0; r < p_segments; r++)
	{
		for (int32_t s = 0; s < p_segments; s++)
		{
			*++ind = s + p_segments*r;
			*++ind = s + 1 + p_segments*r;
			*++ind = p_segments + s + p_segments*r;

			*++ind = p_segments + s + 1 + p_segments*r;
			*++ind = p_segments + s + p_segments*r;
			*++ind = s + 1 + p_segments*r;
		}
	}
	ret.indices.reset(indices);


	return ret;
}
