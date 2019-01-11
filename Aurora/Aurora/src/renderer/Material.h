#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <string>
#include <unordered_map>

#include "AuroraDef.h"
#include "ShaderType.h"

#include "glm/glm.hpp"

namespace aurora
{
	class Material
	{
	public:
		using UniformValueMap = std::unordered_map<std::string, UniformValue>;
		using TextureMap = std::unordered_map<std::string, TexturePtr>;

	public:
		Material(const ShaderPtr& shader);
		~Material();

		MaterialPtr Clone() const;

		uint64_t GetMaterialId() const;

		void AttachTexture(const std::string& name, TexturePtr texture);
		TexturePtr GetTexture(const std::string& name);

		void CommitBool(const std::string& name, bool value);
		void CommitInt(const std::string& name, int value);
		void CommitUInt(const std::string& name, uint32_t value);
		void CommitFloat(const std::string& name, float value);
		void CommitVec3(const std::string& name, const glm::vec3& value);
		void CommitVec4(const std::string& name, const glm::vec4& value);
		void CommitMat3(const std::string& name, const glm::mat3& value);
		void CommitMat4(const std::string& name, const glm::mat4& value);

		void Bind();
		void UnBind();

		void set_shader_ptr(const ShaderPtr& shader_ptr) { shader_ptr_ = shader_ptr; }
		const ShaderPtr& shader_ptr() const { return shader_ptr_; }

		const UniformValueMap& uniform_value_map() const { return uniform_value_map_; }
		const TextureMap& texture_map() const { return texture_map_; }
	private:
		ShaderPtr shader_ptr_;
		UniformValueMap uniform_value_map_;
		TextureMap texture_map_;
	};
}

#endif
