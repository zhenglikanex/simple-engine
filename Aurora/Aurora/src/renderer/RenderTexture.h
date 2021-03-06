#ifndef RENDER_TEXTURE_H_
#define RENDER_TEXTURE_H_

#include <assert.h>
#include <functional>

#include "AuroraDef.h"
#include "OGLSupport.h"
#include "Texture.h"

namespace aurora
{
	class BaseRenderTexture
	{
	public:
		enum class TextureFormatType
		{
			kRGBA,
			kFloat,
			kHalfFloat,
		};

		BaseRenderTexture(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count, bool enable_depth_stencil,const std::function<TexturePtr(uint32_t,uint32_t, Texture::OGLTexFormatInfo)>& creator);
		BaseRenderTexture(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count, bool enable_depth, bool enable_stencil, const std::function<TexturePtr(uint32_t, uint32_t, Texture::OGLTexFormatInfo)>& creator);

		virtual ~BaseRenderTexture() = 0;

		TexturePtr GetColorTexture(uint32_t index) const;

		uint32_t width() const { return width_; }
		uint32_t height() const { return height_; }
		const TexturePtr& depth_texture() const { return depth_texture_; }
		const TexturePtr& stencil_texture() const { return stencil_textrue_; }
		const TexturePtr& depth_stencil_texture() const { return depth_stencil_texture_; }
		const FrameBufferObjectPtr& fbo() const { return fbo_; }
	private:
		BaseRenderTexture(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count,const std::function<TexturePtr(uint32_t, uint32_t, Texture::OGLTexFormatInfo)>& creator);

		void Init(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count, const std::function<TexturePtr(uint32_t, uint32_t, Texture::OGLTexFormatInfo)>& creator);

		TextureFormatType type_;
		uint32_t width_;
		uint32_t height_;
		std::vector<TexturePtr> color_textures_;
		TexturePtr depth_texture_;
		TexturePtr stencil_textrue_;
		TexturePtr depth_stencil_texture_;

		FrameBufferObjectPtr fbo_;
	};

	class RenderTexture : public BaseRenderTexture
	{
	public:
		RenderTexture(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count, bool enable_depth_stencil);
		RenderTexture(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count, bool enable_depth, bool enable_stencil);	
	private:
		TexturePtr CreateTexture(uint32_t width, uint32_t height, Texture::OGLTexFormatInfo format_info);
	};

	class RenderTextureCube : public BaseRenderTexture
	{
	public:
		RenderTextureCube(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count, bool enable_depth_stencil);
		RenderTextureCube(TextureFormatType type, uint32_t width, uint32_t height, uint32_t color_texture_count, bool enable_depth, bool enable_stencil);
	private:
		TexturePtr CreateTexture(uint32_t width, uint32_t height, Texture::OGLTexFormatInfo format_info);
	};
}

#endif
