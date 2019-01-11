#include "TextureLoadDesc.h"

#include <unordered_map>

#include "Image.h"
#include "Texture.h"

namespace aurora
{
	static const std::unordered_map<Image::PixelFormat, Texture::OGLTexFormatInfo> s_kPixelFormatByOGLTexInfoMap
	{
		{ Image::PixelFormat::UNKNOWN,Texture::OGLTexFormatInfo(0,0,0,0,false,false) },
		{ Image::PixelFormat::RED,Texture::OGLTexFormatInfo(GL_RED,GL_RED,GL_UNSIGNED_BYTE,8,false,false) },
		{ Image::PixelFormat::RGB888,Texture::OGLTexFormatInfo(GL_RGB8,GL_RGB8,GL_UNSIGNED_BYTE,24,false,false) },
		{ Image::PixelFormat::RGBA8888,Texture::OGLTexFormatInfo(GL_RGBA,GL_RGBA,GL_UNSIGNED_BYTE,32,false,true) }
	};

	Texture2DLoadDesc::Texture2DLoadDesc(const std::string& name)
	{
		name_ = name;
	}

	Texture2DLoadDesc::~Texture2DLoadDesc()
	{

	}

	std::shared_ptr<void> Texture2DLoadDesc::Create()
	{
		Image image(name());
		if (image.IsNull())
		{
			LOG_INFO() << "Texture¼ÓÔØÊ§°Ü£º" << name_ << LOG_END();
			return nullptr;
		}

		auto iter = s_kPixelFormatByOGLTexInfoMap.find(image.pixel_format());
		if (iter == s_kPixelFormatByOGLTexInfoMap.end())
		{
			return nullptr;
		}

		return MakeTexture2DPtr(image.width(), image.height(), iter->second, image.data());;
	}

	/*-------------------------------------------------------*/

	TextureCubeLoadDesc::TextureCubeLoadDesc(
		const std::string& top,
		const std::string& bottom,
		const std::string& left,
		const std::string& right,
		const std::string& front,
		const std::string& back)
		: files_({top,bottom,left,right,front,back})
	{
		name_ = top + bottom + left + right + front + back;
	}

	TextureCubeLoadDesc::TextureCubeLoadDesc(const std::string& floder, const std::string& ext)
		: TextureCubeLoadDesc(
			floder + "/top" + ext,
			floder + "/bottom" + ext,
			floder + "/left" + ext,
			floder + "/right" + ext,
			floder + "/front" + ext,
			floder + "/back" + ext
		)
	{

	}

	TextureCubeLoadDesc::~TextureCubeLoadDesc()
	{

	}

	std::shared_ptr<void> TextureCubeLoadDesc::Create()
	{
		std::array<const void*, 6> datas;
		std::array<ImagePtr, 6> images;
		
		for (int i = 0; i < files_.size(); ++i)
		{
			images[i] = MakeImagePtr(files_[i]);
			if (images[i]->IsNull())
			{
				return nullptr;
			}
			datas[i] = images[i]->data();
		}

		auto iter = s_kPixelFormatByOGLTexInfoMap.find(images[0]->pixel_format());
		if (iter == s_kPixelFormatByOGLTexInfoMap.end())
		{
			return nullptr;
		}

		return MakeTextureCubePtr(images[0]->width(), images[0]->height(), iter->second, datas);
	}
}