#include "Shader.h"

#include <memory>

#include "FileHelper.h"


namespace aurora
{
	Shader::Shader(const std::string& vs_file, const std::string& fs_file)
		: vs_file_(vs_file)
		, ps_file_(fs_file)
	{
		Load(vs_file, fs_file);
	}

	Shader::Shader(const std::string& vs_file, const std::string gs_file, const std::string& fs_file)
		:vs_file_(vs_file)
		,gs_file_(gs_file)
		,ps_file_(fs_file)
	{
		Load(vs_file_, gs_file_, ps_file_);
	}

	Shader::~Shader()
	{
		glDeleteProgram(id_);

		for (auto& iter : name_by_uniform_map_)
		{
			free(iter.second.ptr);
		}
	}

	GLint Shader::GetUniformLocation(const std::string& name) const
	{
		return glGetUniformLocation(id_, name.c_str());
	}

	void Shader::CommitBool(const std::string& name, bool value)
	{
		// 判断是否需要更新
		if (!UpdateLocalValue(name, &value, sizeof(value)))
		{
			return;
		}

		auto location = GetUniformLocation(name);
		if (location > 0)
		{
			glUniform1i(location, (int)value);
		}
	}

	void Shader::CommitInt(const std::string& name, int value)
	{
		// 判断是否需要更新
		if (!UpdateLocalValue(name, &value, sizeof(value)))
		{
			return;
		}

		auto location = GetUniformLocation(name);
		if (location >= 0)
		{
			glUniform1i(location, value);
		}
	}

	void Shader::CommitUInt(const std::string& name, uint32_t value)
	{
		// 判断是否需要更新
		if (!UpdateLocalValue(name, &value, sizeof(value)))
		{
			return;
		}

		auto location = GetUniformLocation(name);
		if (location > 0)
		{
			glUniform1ui(location, value);
		}
	}

	void Shader::CommitFloat(const std::string& name, float value)
	{
		// 判断是否需要更新
		if (!UpdateLocalValue(name, &value, sizeof(value)))
		{
			return;
		}

		auto location = GetUniformLocation(name);
		if (location > 0)
		{
			glUniform1f(location, value);
		}
	}

	void Shader::CommitVec3(const std::string& name, float x, float y, float z)
	{
		auto vec3 = glm::vec3(x, y, z);
		CommitVec3(name,vec3);
	}

	void Shader::CommitVec3(const std::string& name, const float* value)
	{
		auto vec3 = glm::vec3(value[0], value[1], value[2]);
		CommitVec3(name, vec3);
	}

	void Shader::CommitVec3(const std::string& name, const glm::vec3& value)
	{
		// 判断是否需要更新
		if (!UpdateLocalValue(name, &value, sizeof(value)))
		{
			return;
		}
		
		auto location = GetUniformLocation(name);
		if (location > 0)
		{
			glUniform3fv(location, 1, glm::value_ptr(value));
		}
	}

	void Shader::CommitVec4(const std::string& name, float x, float y, float z, float w)
	{
		auto vec4 = glm::vec4(x, y, z, w);
		CommitVec4(name, vec4);
	}

	void Shader::CommitVec4(const std::string& name, const float* value)
	{
		auto vec4 = glm::vec4(value[0],value[1],value[2],value[3]);
		CommitVec4(name, vec4);
	}

	void Shader::CommitVec4(const std::string& name, const glm::vec4& value)
	{
		// 判断是否需要更新
		if (!UpdateLocalValue(name, &value, sizeof(value)))
		{
			return;
		}

		auto location = GetUniformLocation(name);
		if (location > 0)
		{
			glUniform4fv(location, 1, glm::value_ptr(value));
		}
	}

	void Shader::CommitMat3(const std::string& name, const glm::mat3& value)
	{
		// 判断是否需要更新
		if (!UpdateLocalValue(name, &value, sizeof(value)))
		{
			return;
		}

		auto location = GetUniformLocation(name);
		if (location > 0)
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
		}
	}

	void Shader::CommitMat4(const std::string& name, const glm::mat4& value)
	{
		// 判断是否需要更新
		if (!UpdateLocalValue(name, &value, sizeof(value)))
		{
			return;
		}

		auto location = GetUniformLocation(name);
		if (location >= 0)
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
		}
	}

	void Shader::Bind()
	{
		glUseProgram(id_);
	}
	
	void Shader::UnBind()
	{
		glUseProgram(0);
	}

	void Shader::Load(const std::string& vs_file, const std::string& fs_file)
	{
		auto vs_shader = CreateShader(GL_VERTEX_SHADER, vs_file);
		auto fs_shader = CreateShader(GL_FRAGMENT_SHADER, fs_file);
		CreateProgram(vs_shader, fs_shader);
	}

	void Shader::Load(const std::string& vs_file, const std::string& gs_file, const std::string& fs_file)
	{
		auto vs_shader = CreateShader(GL_VERTEX_SHADER, vs_file);
		auto gs_shader = CreateShader(GL_GEOMETRY_SHADER, gs_file_);
		auto fs_shader = CreateShader(GL_FRAGMENT_SHADER, fs_file);
		CreateProgram(vs_shader, gs_shader, fs_shader);
	}

	GLuint Shader::CreateShader(GLenum type,const std::string& file)
	{
		auto file_identifer = FileHelper::GetInstance()->OpenFileIdentifer(file);
		if (!file_identifer)
		{
			return 0;
		}

		auto source = file_identifer.string();
		const GLchar* c_source = source.c_str();
		GLint size = source.size();

		GLuint id = glCreateShader(type);
		glShaderSource(id, 1, &(c_source), &size);
		glCompileShader(id);

		GLint status;
		glGetShaderiv(id, GL_COMPILE_STATUS, &status);

		if (!status)
		{
			std::string shader_type;
			if (type == GL_VERTEX_SHADER)
			{
				shader_type = "VertexShader";
			}
			else if (type == GL_GEOMETRY_SHADER)
			{
				shader_type = "GeometryShader";
			}
			else if (type == GL_FRAGMENT_SHADER)
			{
				shader_type = "FragmentShader";
			}

			const GLsizei kMaxCount = 256;
			GLchar error_info[kMaxCount + 1] = { 0 };
			GLsizei length;
			glGetShaderInfoLog(id, kMaxCount, &length, error_info);
			
			error_info[length + 1] = '\0';

			LOG_ERROR() << file_identifer.res_name() << shader_type << "编译错误 : \n" << error_info << LOG_END();
		}

		return id;
	}


	void Shader::CreateProgram(GLint vs_shader,GLint fs_shader)
	{
		id_ = glCreateProgram();

		if (vs_shader > 0)
		{
			glAttachShader(id_, vs_shader);
		}

		if (fs_shader > 0)
		{
			glAttachShader(id_, fs_shader);
		}

		glLinkProgram(id_);

		GLint status;
		glGetProgramiv(id_, GL_LINK_STATUS, &status);
		if (!status)
		{
			const GLsizei kMaxCount = 256;
			GLchar error_info[kMaxCount + 1] = { 0 };
			GLsizei length;

			glGetProgramInfoLog(id_, kMaxCount, &length, error_info);

			error_info[length + 1] = '\0';

			LOG_ERROR() << "编译出错 : \n"
						<< "vs_file: " << vs_file_ << "\n"
						<< "ps_file: " << ps_file_ << "\n"
						<< "error:" << error_info << LOG_END();
		}
		
		glDeleteShader(vs_shader);
		glDeleteShader(fs_shader);
	}

	void Shader::CreateProgram(GLint vs_shader, GLint gs_shader, GLint fs_shader)
	{
		id_ = glCreateProgram();

		if (vs_shader > 0)
		{
			glAttachShader(id_, vs_shader);
		}

		if (gs_shader > 0)
		{
			glAttachShader(id_, gs_shader);
		}

		if (fs_shader > 0)
		{
			glAttachShader(id_, fs_shader);
		}

		glLinkProgram(id_);

		GLint status;
		glGetProgramiv(id_, GL_LINK_STATUS, &status);
		if (!status)
		{
			const GLsizei kMaxCount = 256;
			GLchar error_info[kMaxCount + 1] = { 0 };
			GLsizei length;

			glGetProgramInfoLog(id_, kMaxCount, &length, error_info);

			error_info[length + 1] = '\0';

			LOG_ERROR() << "编译出错 : \n"
				<< "vs_file: " << vs_file_ << "\n"
				<< "gs_file: " << gs_file_ << "\n"
				<< "ps_file: " << ps_file_ << "\n"
				<< "error:" << error_info << LOG_END();
		}

		glDeleteShader(vs_shader);
		glDeleteShader(gs_shader);
		glDeleteShader(fs_shader);
	}

	bool Shader::UpdateLocalValue(const std::string& name, const void* memory, size_t size)
	{
		if (true)
		{
			return true;
		}

		auto iter = name_by_uniform_map_.find(name);
		if (iter == name_by_uniform_map_.end())
		{
			UnkownValue value;
			value.ptr = (void*)malloc(size);
			std::memcpy(value.ptr, memory, size);
			value.size = size;
			name_by_uniform_map_.insert(std::make_pair(name, value));
			
			return true;
		}

		if (size == iter->second.size && std::memcmp(iter->second.ptr, memory, size))
		{
			// todo：这里可以用内存池优化

			// 释放原来的内存
			free(iter->second.ptr);

			// 复制内存
			iter->second.ptr = (void*)malloc(size);
			std::memcpy(iter->second.ptr, memory, size);
			iter->second.size = size;
			return true;
		}
		
		return false;
	}
}