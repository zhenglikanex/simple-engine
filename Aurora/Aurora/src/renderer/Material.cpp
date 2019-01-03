#include "Material.h"
#include "Shader.h"
#include "Texture.h"

namespace aurora
{
	const std::string& GetUniformName(Material::TexChannel tex_channel)
	{
		if (tex_channel >= Material::TexChannel::kMaxChannel)
		{
			return "";
		}

		/*enum TexChannel
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
		};*/

		static std::string UniformNames[Material::TexChannel::kMaxChannel] = 
		{
			"tex_normal",
			"tex_diffuse",
			"tex_specular",
			"tex_detail",
			"tex_custom1",
			"tex_custom2",
			"tex_custom3",
			"tex_custom4",
			"tex_custom5",
			"tex_custom6",
			"tex_custom7",
			"tex_custom8",
			"tex_custom9",
			"tex_custom10",
			"tex_custom11",
			"tex_custom12",
		};

		return UniformNames[tex_channel];
	}

	Material::Material()
	{

	}

	Material::~Material()
	{

	}

	uint64_t Material::GetMaterialId() const
	{
		return 0;
	}

	void Material::AttachTexture(TexChannel tex_channel, TexturePtr tex_ptr)
	{
		if (tex_channel >= TexChannel::kMaxChannel)
		{
			return;
		}

		if (tex_ptr)
		{
			channel_by_tex_map_.insert(std::make_pair(tex_channel, tex_ptr));
		}
	}

	TexturePtr Material::GetTexture(TexChannel tex_channel)
	{
		auto iter = channel_by_tex_map_.find(tex_channel);
		if (iter != channel_by_tex_map_.end())
		{
			return iter->second;
		}

		return TexturePtr();
	}

	void Material::Bind()
	{
		if (shader_ptr_)
		{
			shader_ptr_->Bind();
		}
		
		// 提交当前material包含的纹理
		for (auto iter = channel_by_tex_map_.begin(); iter != channel_by_tex_map_.end(); ++iter)
		{
			auto tex_uniform_name = GetUniformName(iter->first);
			if (tex_uniform_name.size() > 0)
			{
				// 激活纹理单元
				glActiveTexture(GL_TEXTURE0 + iter->first);
				
				// 绑定纹理对象到纹理单元
				iter->second->Bind();

				// 提交纹理单元到对应的uniform变量
				if (shader_ptr_)
				{
					shader_ptr_->CommitInt(tex_uniform_name, iter->first);
				}
			}
		}
	}

	void Material::UnBind()
	{
		if (shader_ptr_)
		{
			shader_ptr_->UnBind();
		}
	}
}
