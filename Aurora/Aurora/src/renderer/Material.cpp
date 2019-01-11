#include "Material.h"

#include "Shader.h"
#include "Texture.h"

namespace aurora
{

	Material::Material(const ShaderPtr& shader)
		:shader_ptr_(shader)
	{

	}

	Material::~Material()
	{
	}

	MaterialPtr Material::Clone() const
	{
		auto mtl = MakeMaterialPtr(this->shader_ptr_);
		mtl->texture_map_ = this->texture_map_;
		mtl->uniform_value_map_ = this->uniform_value_map_;

		return mtl;
	}

	uint64_t Material::GetMaterialId() const
	{
		return 0;
	}

	void Material::AttachTexture(const std::string& name, TexturePtr texture)
	{
		texture_map_.emplace(name, texture);
	}

	TexturePtr Material::GetTexture(const std::string& name)
	{
		auto iter = texture_map_.find(name);
		if (iter != texture_map_.end())
		{
			return iter->second;
		}

		return nullptr;
	}

	void Material::CommitBool(const std::string& name, bool value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kUniformTypeBool;
		uniform.Bool = value;
		uniform_value_map_.emplace(name, uniform);
	}

	void Material::CommitInt(const std::string& name, int value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kUniformTypeInt;
		uniform.Int = value;
		uniform_value_map_.emplace(name, uniform);
	}

	void Material::CommitUInt(const std::string& name, uint32_t value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kUniformTypeUInt;
		uniform.UInt = value;
		uniform_value_map_.emplace(name, uniform);
	}

	void Material::CommitFloat(const std::string& name, float value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kUniformTypeFloat;
		uniform.Float = value;
		uniform_value_map_.emplace(name, uniform);
	}

	void Material::CommitVec3(const std::string& name, const glm::vec3& value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kUniformTypeVec3;
		uniform.Vec3 = value;
		uniform_value_map_.emplace(name, uniform);
	}

	void Material::CommitVec4(const std::string& name, const glm::vec4& value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kUniformTypeVec4;
		uniform.Vec4 = value;
		uniform_value_map_.emplace(name, uniform);
	}

	void Material::CommitMat3(const std::string& name, const glm::mat3& value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kUniformTypeMat3;
		uniform.Mat3 = value;
		uniform_value_map_.emplace(name, uniform);
	}

	void Material::CommitMat4(const std::string& name, const glm::mat4& value)
	{
		UniformValue uniform;
		uniform.type = UniformType::kUniformTypeMat4;
		uniform.Mat4 = value;
		uniform_value_map_.emplace(name, uniform);
	}

	void Material::Bind()
	{
		if (!shader_ptr_)
		{
			return;
		}

		int texture_unit = 0;
		// 提交当前material包含的纹理
		for (auto iter = texture_map_.cbegin(); iter != texture_map_.cend(); ++iter)
		{
			auto name = iter->first;
			auto texture = iter->second;

			if (name.size() > 0)
			{	
				// 绑定纹理对象到纹理单元
				texture->Bind(texture_unit);

				// 提交纹理单元到对应的uniform变量
				shader_ptr_->CommitInt(name, texture_unit);

				texture_unit += texture_unit;
			}
		}

		// 提交材质参数
		for (auto iter = uniform_value_map_.cbegin(); iter != uniform_value_map_.cend(); ++iter)
		{
			auto name = iter->first;
			auto uniform = iter->second;

			switch (uniform.type)
			{
			case aurora::UniformType::kUniformTypeUnkown:
				break;
			case aurora::UniformType::kUniformTypeBool:
				shader_ptr_->CommitBool(name, uniform.Bool);
				break;
			case aurora::UniformType::kUniformTypeInt:
				shader_ptr_->CommitInt(name, uniform.Int);
				break;
			case aurora::UniformType::kUniformTypeUInt:
				shader_ptr_->CommitUInt(name, uniform.UInt);
				break;
			case aurora::UniformType::kUniformTypeFloat:
				shader_ptr_->CommitFloat(name, uniform.Float);
				break;
			case aurora::UniformType::kUniformTypeVec3:
				shader_ptr_->CommitVec3(name, uniform.Vec3);
				break;
			case aurora::UniformType::kUniformTypeVec4:
				shader_ptr_->CommitVec4(name, uniform.Vec4);
				break;
			case aurora::UniformType::kUniformTypeMat3:
				shader_ptr_->CommitMat3(name, uniform.Mat3);
				break;
			case aurora::UniformType::kUniformTypeMat4:
				shader_ptr_->CommitMat4(name, uniform.Mat4);
				break;
			default:
				break;
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
