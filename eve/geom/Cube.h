
/*
 Copyright (c) 2014, The eve Project
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 * Neither the name of the {organization} nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once
#ifndef __EVE_GEOMETRY_CUBE_H__
#define __EVE_GEOMETRY_CUBE_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MATH_INCLUDES_H__
#include "eve/math/Includes.h"
#endif

#ifndef __EVE_OPENGL_CORE_VAO_H__
#include "eve/ogl/core/Vao.h"
#endif


namespace eve
{
	namespace geom
	{
		/** \brief Create cube indices data. */
		GLuint * create_cube_indices(void);


		/** \brief Create textured cube vertices data. */
		float * create_cube_textured_vertices(const eve::vec3f & p_position, const eve::vec3f & p_size);
		/** \brief Create colored cube vertices data. */
		float * create_cube_colored_vertices(const eve::vec3f & p_position, const eve::vec3f & p_size, const eve::color4f & p_color);


		/** \brief Create a textured cube. */
		eve::ogl::FormatVao create_cube_textured(const eve::vec3f & p_position, const eve::vec3f & p_size);
		/** \brief Create a colored cube. */
		eve::ogl::FormatVao create_cube_colored(const eve::vec3f & p_position, const eve::vec3f & p_size, const eve::color4f & p_color);

	} // namespace geom

} // namespace eve

#endif  // __EVE_GEOMETRY_CUBE_H__ 
