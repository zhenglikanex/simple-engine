#ifndef TEXTURE_LOADER_H_
#define TEXTURE_LOADER_H_

#include <string>

#include "AuroraDef.h"
#include "ResLoader.h"
#include "ResManager.h"

namespace aurora
{
	class TextureLoader : public ResLoader<TexturePtr>
	{
	public:
		~TextureLoader()
		{

		}

		TexturePtr Load(const std::string& file) override;
	private:
	};

	using TextureManager = ResManager<TextureLoader>;
}

#endif
