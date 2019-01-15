#include "RenderTexture.h"

#include "FrameBufferObject.h"
#include "Texture.h"

namespace aurora
{
	BaseRenderTexture::BaseRenderTexture(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count, bool enable_depth_stencil,const std::function<TexturePtr(uint32_t, uint32_t, Texture::OGLTexFormatInfo)>& creator)
		: type_(type)
		, width_(width)
		, height_(height)
		, fbo_(MakeFrameBufferObjectPtr())
	{
		fbo_->Bind();

		Init(type, width, height, color_texture_count, creator);

		if (enable_depth_stencil)
		{
			Texture::OGLTexFormatInfo format_info;
			format_info.internal_format_ = GL_DEPTH24_STENCIL8;
			format_info.format_ = GL_UNSIGNED_INT_24_8;
			format_info.compressed_ = false;
			depth_stencil_texture_ = creator(width_, height_, format_info);
			auto attachment = MakeTextureBufferAttachmentPtr(FrameBufferAttachment::AttachmentType::kDepthStencil, depth_stencil_texture_);
			fbo_->AttachAttachment(attachment);
		}

		fbo_->UnBind();
	}

	BaseRenderTexture::BaseRenderTexture(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count, bool enable_depth, bool enable_stencil, const std::function<TexturePtr(uint32_t, uint32_t, Texture::OGLTexFormatInfo)>& creator)
		: type_(type)
		, width_(width)
		, height_(height)
		, fbo_(MakeFrameBufferObjectPtr())
	{
		fbo_->Bind();

		Init(type, width, height, color_texture_count, creator);

		if (enable_depth)
		{
			Texture::OGLTexFormatInfo format_info;
			format_info.internal_format_ = GL_DEPTH_COMPONENT;
			format_info.format_ = GL_DEPTH_COMPONENT;
			format_info.compressed_ = false;
			depth_texture_ = creator(width_, height_, format_info);
			auto attachment = MakeTextureBufferAttachmentPtr(FrameBufferAttachment::AttachmentType::kDepth, depth_texture_);
			fbo_->AttachAttachment(attachment);
		}
		if (enable_stencil)
		{
			Texture::OGLTexFormatInfo format_info;
			format_info.internal_format_ = GL_STENCIL_INDEX;
			format_info.format_ = GL_STENCIL_INDEX;
			format_info.compressed_ = false;
			stencil_textrue_ = creator(width_, height_, format_info);
			auto attachment = MakeTextureBufferAttachmentPtr(FrameBufferAttachment::AttachmentType::kStencil, stencil_textrue_);
			fbo_->AttachAttachment(attachment);
		}

		fbo_->UnBind();
	}

	TexturePtr BaseRenderTexture::GetColorTexture(uint32_t index) const
	{
		assert(index >= 0 && index < color_textures_.size()); 
		return color_textures_[index];
	}

	void BaseRenderTexture::Init(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count, const std::function<TexturePtr(uint32_t, uint32_t, Texture::OGLTexFormatInfo)>& creator)
	{
		Texture::OGLTexFormatInfo format_info;

		if (type_ == TextureFormatType::kRGBA)
		{
			format_info.internal_format_ = GL_RGBA;
		}
		else if (type_ == TextureFormatType::kFloat)
		{
			format_info.internal_format_ = GL_RGBA32F;
		}
		else if (type_ == TextureFormatType::kHalfFloat)
		{
			format_info.internal_format_ = GL_RGBA16F;
		}

		format_info.format_ = GL_RGBA;
		format_info.bpp_ = 32;
		format_info.compressed_ = false;
		format_info.alpha_ = true;

		for (uint32_t i = 0; i < color_texture_count; ++i)
		{
			auto texture = creator(width_, height_, format_info);
			color_textures_.push_back(texture);

			auto attachment = MakeTextureBufferAttachmentPtr(FrameBufferAttachment::AttachmentType::kColor, texture);
			fbo_->AttachAttachment(attachment);
		}

		if (color_texture_count <= 0)
		{
			glReadBuffer(GL_NONE);
			glDrawBuffer(GL_NONE);
		}
	}

	BaseRenderTexture::~BaseRenderTexture()
	{

	}

	/*--------------------------------------------------------------------------------------------*/
	RenderTexture::RenderTexture(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count, bool enable_depth_stencil)
		: BaseRenderTexture(type,width,height,color_texture_count,enable_depth_stencil,std::bind(&RenderTexture::CreateTexture,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3))
	{
	}

	RenderTexture::RenderTexture(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count, bool enable_depth, bool enable_stencil)
		: BaseRenderTexture(type, width, height, color_texture_count,enable_depth,enable_stencil, std::bind(&RenderTexture::CreateTexture, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
	{
	}
	TexturePtr RenderTexture::CreateTexture(uint32_t width, uint32_t height, Texture::OGLTexFormatInfo format_info)
	{
		return MakeTexture2DPtr(width, height, format_info, nullptr);
	}

	/*--------------------------------------------------------------------------------------------*/

	RenderTextureCube::RenderTextureCube(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count, bool enable_depth_stencil)
		: BaseRenderTexture(type, width, height, color_texture_count,enable_depth_stencil, std::bind(&RenderTextureCube::CreateTexture, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
	{

		
	}

	RenderTextureCube::RenderTextureCube(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count, bool enable_depth, bool enable_stencil)
		: BaseRenderTexture(type, width, height, color_texture_count,enable_depth,enable_stencil, std::bind(&RenderTextureCube::CreateTexture, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
	{
	}

	TexturePtr RenderTextureCube::CreateTexture(uint32_t width, uint32_t height, Texture::OGLTexFormatInfo format_info)
	{
		std::array<const void*, 6> datas = { nullptr };
		return MakeTextureCubePtr(width, height, format_info, datas);
	}
}