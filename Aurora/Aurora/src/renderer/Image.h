#ifndef IMAGE_H_
#define IMAGE_H_

#include "AuroraDef.h"

#include <string>

namespace aurora
{
	class Image
	{
	public:
		// 暂时只支持这些像素格式
		enum class PixelFormat
		{
			UNKNOWN,
			RED,
			RGB888,
			RGBA8888,
		};

		// 暂时只支持这些图片格式,后面增加DXT格式和ETC格式的支持
		enum ImageType
		{
			kJpg,
			kPng,
			kTag,
		};

		Image(const std::string& file);
		~Image();

		void Load(const std::string& file);
		void UnLoad();
		
		bool IsNull() const;

		const std::string& file() const { return file_; }
		ImageType image_type() const { return image_type_; }
		PixelFormat pixel_format() const { return pixel_format_; }
		int width() const { return width_; }
		int height() const { return height_; }
		const uint8_t* data() const { return data_; }
	private:
		std::string file_;
		ImageType image_type_;
		PixelFormat pixel_format_;
		int width_;
		int height_;
		uint8_t* data_;
	};
}

#endif
