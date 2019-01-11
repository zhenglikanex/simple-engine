#ifndef SHADER_TYPE_H_
#define SHADER_TYPE_H_

#include <cstdint>
#include "glm/glm.hpp"

namespace aurora
{
	enum class UniformType
	{
		kUniformTypeUnkown,
		kUniformTypeBool,
		kUniformTypeInt,
		kUniformTypeUInt,
		kUniformTypeFloat,
		kUniformTypeVec3,
		kUniformTypeVec4,
		kUniformTypeMat3,
		kUniformTypeMat4,
	};

	struct UniformValue
	{
		UniformType type;
		union
		{
			bool		Bool;
			int			Int;
			uint32_t	UInt;
			float		Float;
			glm::vec3	Vec3;
			glm::vec4	Vec4;
			glm::mat3	Mat3;
			glm::mat4	Mat4;
		};
	};
}

#endif
