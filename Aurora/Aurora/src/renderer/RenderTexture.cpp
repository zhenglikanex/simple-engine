#include "RenderTexture.h"

#include "FrameBufferObject.h"
#include "Texture.h"

namespace aurora
{
	BaseRenderTexture::BaseRenderTexture(TextureFormatType type, uint32_t width, uint32_t height)
		: type_(type)
		, width_(width)
		, height_(height)
		, fbo_(MakeFrameBufferObjectPtr())
	{
		
	}

	BaseRenderTexture::~BaseRenderTexture()
	{

	}

	/*--------------------------------------------------------------------------------------------*/
	RenderTexture::RenderTexture(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count, bool enable_depth_stencil)
		: BaseRenderTexture(type,width,height)
	{
		for (uint32_t i = 0; i < color_texture_count; ++i)
		{
			
		}
	}

	RenderTexture::RenderTexture(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count, bool enable_depth, bool enable_stencil)
		: BaseRenderTexture(type, width, height)
	{

	}

	/*--------------------------------------------------------------------------------------------*/
}