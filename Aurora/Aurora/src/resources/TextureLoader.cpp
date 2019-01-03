#include "TextureLoader.h"
#include "Image.h"
#include "Texture.h"

namespace aurora
{
	TexturePtr TextureLoader::Load(const std::string& file)
	{
		Image image = Image(file);

		if (!image.IsNull())
		{
			auto texture_ptr = MakeTexturePtr();

			if (texture_ptr)
			{
				texture_ptr->InitWithImage(image);

				return texture_ptr;
			}
		}
		else
		{
			LOG_ERROR() << "Texture����ʧ��: " + file;
		}

		return TexturePtr();
	}
}