#ifndef TEXTURE2D_H_
#define TEXTURE2D_H_

#include <unordered_map>
#include <array>

#include "OGLSupport.h"
#include "Image.h"

namespace aurora
{

	class Texture
	{
	public:
		// OGL�������ʽ��װ
		struct OGLTexFormatInfo
		{
			OGLTexFormatInfo(){}
			OGLTexFormatInfo(GLenum internal_format, GLenum format, GLenum type, int bpp, bool compressed, bool alpha)
				: internal_format_(internal_format)
				, format_(format)
				, type_(type)
				, bpp_(bpp)
				, compressed_(compressed)
				, alpha_(alpha)
			{

			}

			GLenum internal_format_;	//�ڲ���ʽ(���ϴ����Դ��еĸ�ʽ,����ͼƬ��ʽ�������е����ݸ�ʽ����())
			GLenum format_;				//�����ʽ
			GLenum type_;				//���ص��ֽڸ�ʽ
			int bpp_;					//����λ��
			bool compressed_;			//�Ƿ�ѹ��
			bool alpha_;				//�Ƿ�֧��͸��
		};

		using PixelFormatByOGLTexInfoMap = std::unordered_map<Image::PixelFormat, OGLTexFormatInfo>;
		const static PixelFormatByOGLTexInfoMap s_kPixelFormatByOGLTexInfoMap;
	public:
		Texture(GLenum type,uint32_t width,uint32_t height,OGLTexFormatInfo format_info);
		virtual ~Texture() = 0;

		void Bind(int32_t unit = -1);
		void UnBind();
		void GenerateMimap();
		void ApplyNearestFilter();
		void ApplyLinearFilter();

		GLuint id() const { return id_; }
		GLenum type() const { return type_; }
		OGLTexFormatInfo format_info() const { return format_info_; }
		uint32_t width() const { return width_; }
		uint32_t height() const { return height_; }

		bool IsLinearFilter() const { return is_linear_filter_; }
		bool IsNearestFilter() const { return is_nearest_filter_; }
		bool IsMimap() const { return is_mimap_; }
	protected:
		GLuint id_;
		GLenum type_;
		OGLTexFormatInfo format_info_;
		uint32_t width_;
		uint32_t height_;
		bool is_linear_filter_;
		bool is_nearest_filter_;
		bool is_mimap_;
	};

	class Texture2D : public Texture
	{
	public:
		Texture2D(uint32_t width, uint32_t height, OGLTexFormatInfo format_info, const void* data = nullptr);

		void UpdateData(const void* data,GLint mimap_level,GLint offset_x,GLint offset_y,GLsizei width,GLsizei height);
	};

	class TextureCube : public Texture
	{
	public:
		TextureCube(uint32_t width, uint32_t height, OGLTexFormatInfo format_info, const std::array<const void*, 6>& datas = { nullptr });

		void UpdateData(GLenum face, const void* data, GLint mimap_level,GLint offset_x, GLint offset_y, GLsizei width, GLsizei height);
	};
}

#endif
