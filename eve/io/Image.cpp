
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

// Main header
#include "eve/io/Image.h"


#ifndef __EVE_OPENGL_CORE_TEXTURE_H__
#include "eve/ogl/core/Texture.h"
#endif

#include <FreeImage/FreeImage.h>


//=================================================================================================
bool eve::io::load_image(const std::string & p_path, eve::ogl::FormatTex * p_pFormat)
{
	bool bret = false;

	// Check the file signature and deduce its format.
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(p_path.c_str(), 0);
	// If still unknown, try to guess the file format from the file extension.
	if (fif == FIF_UNKNOWN) 
	{
		fif = FreeImage_GetFIFFromFilename(p_path.c_str());
	}

	// Format found.
	if (fif != FIF_UNKNOWN)
	{
		// Check that the plugin has reading capabilities and load the file.
		if (FreeImage_FIFSupportsReading(fif))
		{
			// Pointer to the image.
			FIBITMAP * dib = FreeImage_Load(fif, p_path.c_str());
			dib = FreeImage_ConvertTo32Bits(dib);

			if (dib)
			{
				// Grab image format.
				uint32_t channels(0);
				switch (FreeImage_GetBPP(dib))
				{
				case 8:
					p_pFormat->internalFormat = GL_LUMINANCE;
					p_pFormat->format = GL_LUMINANCE;
					channels = 1;
					break;

				case 32:
					p_pFormat->internalFormat = GL_RGBA;
#if (FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB)
					p_pFormat->format = GL_RGBA;
#else
					p_pFormat->format = GL_BGRA;
#endif
					channels = 4;
					break;

				case 24:
				default:
					p_pFormat->internalFormat = GL_RGB;
#if (FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB)
					p_pFormat->format = GL_RGB;
#else
					p_pFormat->format = GL_BGR;
#endif
					channels = 3;
					break;
				}

				// FreeImage loads unsigned bytes.
				p_pFormat->type   = GL_UNSIGNED_BYTE;
				p_pFormat->width  = static_cast<GLsizei>(FreeImage_GetWidth(dib));
				p_pFormat->height = static_cast<GLsizei>(FreeImage_GetHeight(dib));

				// Allocate and copy pixels.
				size_t size = channels * p_pFormat->width * p_pFormat->height * sizeof(GLubyte);
				GLubyte * pixels = (GLubyte*)malloc(size);
				GLubyte * fiPix  = FreeImage_GetBits(dib);
				memcpy(pixels, fiPix, size);

				p_pFormat->pixels.reset(pixels);

				// Free FreeImage's copy of the data.
				FreeImage_Unload(dib);

				bret = true;
			}
		}
	}

	return bret;
}

