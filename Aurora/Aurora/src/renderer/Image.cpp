#include "Image.h"

#include "FileHelper.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

namespace aurora
{
	Image::Image(const std::string& file)
		:width_(0)
		,height_(0)
		,data_(nullptr)
	{
		Load(file);
	}

	Image::~Image()
	{
		UnLoad();
	}

	void Image::Load(const std::string& file)
	{
		/*
		stb_image.h用于解析图片格式:
		JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC
		stb_image_write.h用于保存图片格式:
		PNG, TGA, BMP, HDR
		*/

		if (file_ == file)
		{
			return;
		}

		file_ = file;

		if (data_)
		{
			UnLoad();
		}

		auto file_type = file.substr(file.find_last_of(".") + 1, file.size());
		if (file_type == "png")
		{
			image_type_ = ImageType::kPng;
		}
		else if(file_type == "jpg") 
		{
			image_type_ = ImageType::kJpg;
		}
		else if (file_type == "tga")
		{
			image_type_ = ImageType::kTag;
		}

		if(image_type_ == ImageType::kPng || image_type_ == ImageType::kJpg || image_type_ == ImageType::kTag)
		{
			auto full_path = FileHelper::GetInstance()->GetFullPath(file_);

			int components;
			data_ = stbi_load(full_path.string().c_str(), &width_, &height_, &components,0);
			
			if (data_)
			{
				// 判断图片像素格式
				if (components == 1) 
				{
					pixel_format_ = PixelFormat::RED;
				}
				else if (components == 3)
				{
					pixel_format_ = PixelFormat::RGB888;
				}
				else if (components == 4)
				{
					pixel_format_ = PixelFormat::RGBA8888;
				}
				else 
				{
					LOG_ERROR() << "不支持当前图片的像素格式: " + file;

					stbi_image_free(data_);
					data_ = nullptr;
					
					return;
				}
			}
			else
			{
				LOG_ERROR() << "图片加载出错: " + file;

				stbi_image_free(data_);
				data_ = nullptr;

				return;
			}
		}
		else
		{
			LOG_ERROR() << "不支持当前类型图片格式: " + file;
		}
	}

	void Image::UnLoad()
	{
		if (IsNull())
		{
			return;
		}

		stbi_image_free(data_);
		data_ = nullptr;
	}

	bool Image::IsNull() const
	{
		return data_ == nullptr;
	}
}