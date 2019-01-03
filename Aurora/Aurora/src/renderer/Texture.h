#ifndef TEXTURE2D_H_
#define TEXTURE2D_H_

#include <unordered_map>

#include "OGLSupport.h"
#include "Image.h"

namespace aurora
{
	class Texture
	{
	public:
		// OGL的纹理格式封装
		struct OGLTexFormatInfo
		{
			OGLTexFormatInfo(GLenum internal_format,GLenum format,GLenum type,int bpp,bool compressed,bool alpha)
				: internal_format_(internal_format)
				, format_(format)
				, type_(type)
				, bpp_(bpp)
				, compressed_(compressed)
				, alpha_(alpha)
			{

			}

			GLenum internal_format_;	//内部格式(即上传到显存中的格式)
			GLenum format_;				//图片data的像素格式
			GLenum type_;				//像素的字节格式
			int bpp_;					//像素位数
			bool compressed_;			//是否压缩
			bool alpha_;				//是否支持透明
		};

		using PixelFormatByOGLTexInfoMap = std::unordered_map<Image::PixelFormat, OGLTexFormatInfo>;

		const static PixelFormatByOGLTexInfoMap s_kPixelFormatByOGLTexInfoMap;
	public:
		Texture();
		~Texture();

		bool InitWithImage(const Image& image);

		void Bind();
		void GenerateMimap();
		void ApplyNearestFilter();
		void ApplyLinearFilter();
		void UpdateTexData(const void* data,GLint offset_x,GLint offset_y,GLsizei width,GLsizei height);

		GLuint tex_id() const { return tex_id_; }
		GLenum tex_type() const { return tex_type_; }
		OGLTexFormatInfo tex_format() const { return tex_format_; }
		
		bool IsLinearFilter() const { return is_linear_filter_; }
		bool IsNearestFilter() const { return is_nearest_filter_; }
		bool IsMimap() const { return is_mimap_; }
	private:
		GLuint tex_id_;
		GLenum tex_type_;
		OGLTexFormatInfo tex_format_;
		bool is_linear_filter_;
		bool is_nearest_filter_;
		bool is_mimap_;
	};
}

#endif
