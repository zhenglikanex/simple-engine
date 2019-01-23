#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <unordered_map>

#include "OGLSupport.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace aurora
{
	class Shader
	{
	public:
		struct UnkownValue
		{
			void* ptr;
			size_t size;
		};

		using NameByUniformMap = std::unordered_map<std::string,UnkownValue>;

		Shader(const std::string& vs_file,const std::string& fs_file);
		Shader(const std::string& vs_file, const std::string gs_file, const std::string& fs_file);
		~Shader();

		const GLuint id() { return id_; }
	public:
		GLint GetUniformLocation(const std::string& name) const;

		// 提交uniform变量
		void CommitBool(const std::string& name, bool value);
		void CommitInt(const std::string& name, int value);
		void CommitUInt(const std::string& name, uint32_t value);
		void CommitFloat(const std::string& name, float value);
		void CommitVec3(const std::string& name, float x, float y, float z);
		void CommitVec3(const std::string& name, const float* value);
		void CommitVec3(const std::string& name, const glm::vec3& value);
		void CommitVec4(const std::string& name, float x, float y, float z, float w);
		void CommitVec4(const std::string& name, const float* value);
		void CommitVec4(const std::string& name, const glm::vec4& value);
		void CommitMat3(const std::string& name, const glm::mat3& value);
		void CommitMat4(const std::string& name, const glm::mat4& value);

		void Bind();
		void UnBind();
	private:
		void Load(const std::string& vs_file, const std::string& fs_file);
		void Load(const std::string& vs_file, const std::string& gs_file, const std::string& fs_file);
		
		GLuint CreateShader(GLenum type,const std::string& file);

		void CreateProgram(GLint vs_shader,GLint fs_shader);
		void CreateProgram(GLint vs_shader, GLint gs_shader, GLint fs_shader);
		
		bool UpdateLocalValue(const std::string& name, const void* memory, size_t size);
	private:
		GLuint id_;
		std::string vs_file_;
		std::string gs_file_;
		std::string ps_file_;
		NameByUniformMap name_by_uniform_map_;
	};
}

#endif
