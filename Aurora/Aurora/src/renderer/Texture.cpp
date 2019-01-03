#include "Texture.h"

#include "stb_image.h"

namespace aurora
{
	const Texture::PixelFormatByOGLTexInfoMap Texture::s_kPixelFormatByOGLTexInfoMap
	{
		{ Image::PixelFormat::UNKNOWN,Texture::OGLTexFormatInfo(0,0,0,0,false,false) },
		{ Image::PixelFormat::RED,Texture::OGLTexFormatInfo(GL_RED,GL_RED,GL_UNSIGNED_BYTE,8,false,false) },
		{ Image::PixelFormat::RGB888,Texture::OGLTexFormatInfo(GL_RGB8,GL_RGB8,GL_UNSIGNED_BYTE,24,false,false) },
		{ Image::PixelFormat::RGBA8888,Texture::OGLTexFormatInfo(GL_RGBA,GL_RGBA,GL_UNSIGNED_BYTE,32,false,true) }
	};

	Texture::Texture()
		:tex_format_(s_kPixelFormatByOGLTexInfoMap.at(Image::PixelFormat::UNKNOWN))
		,is_linear_filter_(false)
		,is_nearest_filter_(false)
		,is_mimap_(false)
	{
		glGenTextures(1, &tex_id_);
		tex_type_ = GL_TEXTURE_2D;
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &tex_id_);
	}

	bool Texture::InitWithImage(const Image& image)
	{
		if (image.IsNull())
		{
			return false;
		}

		auto iter = s_kPixelFormatByOGLTexInfoMap.find(image.pixel_format());
		if (iter == s_kPixelFormatByOGLTexInfoMap.end())
		{
			return false;
		}

		auto tex_info = iter->second;

		Bind();

		if (tex_info.compressed_)
		{

		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, tex_info.format_, tex_info.type_, image.data());
		}

		ApplyNearestFilter();

		return true;
	}

	void Texture::Bind()
	{
		if (!tex_id_)
		{
			return;
		}

		glBindTexture(GL_TEXTURE_2D, tex_id_);
	}

	void Texture::GenerateMimap()
	{
		if (!tex_id_)
		{
			return;
		}

		glGenerateMipmap(tex_id_);
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
		if (!tex_id_)
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
		if (!tex_id_)
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
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	
	void Texture::UpdateTexData(const void* data,GLint offset_x,GLint offset_y,GLsizei width,GLsizei height)
	{
		if (tex_id_)
		{
			glTexSubImage2D(GL_TEXTURE_2D, 0, offset_x, offset_y, width, height, tex_format_.format_, tex_format_.type_, data);
		}
	}
}