#include "Texture.h"

#include "stb_image.h"

namespace aurora
{
	Texture::Texture(GLenum type,uint32_t width,uint32_t height,OGLTexFormatInfo format_info)
		: type_(type)
		, format_info_(format_info)
		, width_(width)
		, height_(height)
		, is_linear_filter_(false)
		, is_nearest_filter_(false)
		, is_mimap_(false)
	{
		glGenTextures(1, &id_);
		Bind();
		/*glTexParameteri(type_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(type_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);*/
		ApplyNearestFilter();
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &id_);
	}

	void Texture::Bind(int32_t unit /* = -1 */)
	{
		if (!id_)
		{
			return;
		}

		if (unit >= 0)
		{
			glActiveTexture(GL_TEXTURE0 + unit);
		}

		glBindTexture(type_, id_);
	}

	void Texture::UnBind()
	{
		glBindTexture(type_, 0);
	}

	void Texture::GenerateMimap()
	{
		if (!id_)
		{
			return;
		}

		glGenerateMipmap(id_);
		is_mimap_ = true;

		if (is_nearest_filter_)
		{
			is_nearest_filter_ = false;
			ApplyNearestFilter();
		}
		else if (is_linear_filter_)
		{
			is_linear_filter_ = false;
			ApplyLinearFilter();
		}
	}

	void Texture::ApplyNearestFilter()
	{
		if (!id_)
		{
			return;
		}

		if (is_nearest_filter_)
		{
			return;
		}

		is_nearest_filter_ = true;
		is_linear_filter_ = false;

		Bind();

		if (is_mimap_)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void Texture::ApplyLinearFilter()
	{
		if (!id_)
		{
			return;
		}

		if (is_linear_filter_)
		{
			return;
		}

		is_linear_filter_ = true;
		is_nearest_filter_ = false;

		Bind();

		if (is_mimap_)
		{
			glTexParameteri(type_, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else
		{
			glTexParameteri(type_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}

		glTexParameteri(type_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	Texture2D::Texture2D(uint32_t width, uint32_t height, OGLTexFormatInfo format_info, const void* data /* = nullptr */)
		:Texture(GL_TEXTURE_2D,width,height,format_info)
	{
		glTexImage2D(type_, 0, format_info_.internal_format_, width_, height_, 0, format_info_.format_, format_info_.type_, data);
	}

	void Texture2D::UpdateData(const void* data, GLint mimap_level, GLint offset_x, GLint offset_y, GLsizei width, GLsizei height)
	{
		Bind();
		glTexSubImage2D(type_, mimap_level, offset_x, offset_y, width, height, format_info_.format_, format_info_.type_, data);
	}

	/*---------------------------------------------------------------------------------------------------*/
	TextureCube::TextureCube(uint32_t width, uint32_t height, OGLTexFormatInfo format_info, const std::array<const void *, 6>& datas /* = */ )
		: Texture(GL_TEXTURE_CUBE_MAP,width,height,format_info)
	{
		for (uint32_t i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format_info.internal_format_, width_, height_, 0, format_info_.format_, format_info_.type_,datas[i]);
		}

		CHECK_GL_ERROR_DEBUG();
	}

	void TextureCube::UpdateData(GLenum face, const void* data, GLint mimap_level, GLint offset_x, GLint offset_y, GLsizei width, GLsizei height)
	{
		Bind();

		glTexSubImage2D(face, mimap_level, offset_x, offset_y, width, height, format_info_.format_, format_info_.type_, data);
	}
}