#ifndef TEXTURE_LOAD_DESC_H_
#define TEXTURE_LOAD_DESC_H_

#include <array>

#include "ResLoadDesc.h"

namespace aurora
{
	class Texture2DLoadDesc : public ResLoadDesc
	{
	public:
		Texture2DLoadDesc(const std::string& name);
		virtual ~Texture2DLoadDesc();

		std::shared_ptr<void> Create() override;
	private:
	};

	class TextureCubeLoadDesc : public ResLoadDesc
	{
	public:
		TextureCubeLoadDesc(
			const std::string& top,
			const std::string& bottom,
			const std::string& left,
			const std::string& right,
			const std::string& front,
			const std::string& back);
		TextureCubeLoadDesc(const std::string& floder,const std::string& ext);

		virtual ~TextureCubeLoadDesc();

		std::shared_ptr<void> Create() override;
	private:
		std::array<std::string, 6> files_;
	};
}

#endif

