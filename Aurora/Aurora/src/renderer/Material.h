#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <unordered_map>

#include "AuroraDef.h"

namespace aurora
{
	// TODO:考虑material之间的共享和clone

	class Material
	{
	public:
		enum TexChannel
		{
			kNoraml,
			kDiffuse,
			kSpecular,
			kDetail,
			kCustom1,
			kCustom2,
			kCustom3,
			kCustom4,
			kCustom5,
			kCustom6,
			kCustom7,
			kCustom8,
			kCustom9,
			kCustom10,
			kCustom11,
			kCustom12,
			kMaxChannel,
		};

		Material();
		~Material();
		
		uint64_t GetMaterialId() const;

		void AttachTexture(TexChannel tex_channel, TexturePtr tex_ptr);
		TexturePtr GetTexture(TexChannel tex_channel);

		void set_shader_ptr(const ShaderPtr& shader_ptr) { shader_ptr_ = shader_ptr; }
		ShaderPtr shader_ptr() { return shader_ptr_; }

		// 应用材质
		void Bind();

		// 结束应用
		void UnBind();
	private:
		std::unordered_map<TexChannel, TexturePtr> channel_by_tex_map_;
		ShaderPtr shader_ptr_;
	};
}

#endif
