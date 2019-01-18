#ifndef VERTEX_TYPE_H
#define VERTEX_TYPE_H

#include "OGLSupport.h"

#include <memory>
#include <vector>

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

namespace aurora
{
	// 顶点布局类型
	enum VertexLayout
	{
		kP3FN3FT2F,
		kP3FN3FT2FT3FB3F,
	};

	// 简单定点格式
	struct Vertex_P3FN3FT2F
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoords;
	};

	// 完整的定点格式
	struct Vertex_P3FN3FT2FT3FB3F {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoords;
		glm::vec3 tangent;
		glm::vec3 bitangent;
	};

	inline uint32_t VertexSize(VertexLayout vertex_layout)
	{
		switch (vertex_layout)
		{
		case aurora::kP3FN3FT2F:
			return sizeof(Vertex_P3FN3FT2F);
		case aurora::kP3FN3FT2FT3FB3F:
			return sizeof(Vertex_P3FN3FT2FT3FB3F);
		default:
			break;
		}
		return 0;
	}

	class VertexBuffer
	{
	public:
		//VertexBuffer(VertexLayout vertex_layout, uint32_t vertex_count);
		VertexBuffer(VertexLayout vertex_layout, uint32_t vertex_count,const uint8_t* data);
		VertexBuffer(VertexBuffer&& rhs);
		const VertexBuffer& operator=(VertexBuffer&& rhs);

		VertexBuffer(const VertexBuffer& rhs);
		const VertexBuffer& operator=(const VertexBuffer& rhs);

		~VertexBuffer();

		
		VertexLayout vertex_layout() const { return vertex_layout_; }
		uint32_t vertex_count() const { return vertex_count_; }
		uint32_t size() const { return size_; }
		const std::shared_ptr<uint8_t>& data() const
		{
			return data_;
		}
		GLuint id() const { return id_; }

		const uint8_t* GetRawData() const
		{
			return data_.get();
		}
	private:
		VertexLayout vertex_layout_;
		uint32_t vertex_count_;
		uint32_t size_;
		std::shared_ptr<uint8_t> data_;
		GLuint id_;
	};

	enum IndexLayout
	{
		k16Bit,
		k32Bit,
	};

	inline uint32_t IndexSize(IndexLayout index_layout)
	{
		switch (index_layout)
		{
		case aurora::k16Bit:
			return sizeof(uint16_t);
		case aurora::k32Bit:
			return sizeof(uint32_t);
		default:
			break;
		}

		return 0;
	}

	class IndexBuffer
	{
	public:
		IndexBuffer(IndexLayout index_layout_, uint32_t index_count_,const uint8_t* data);
		IndexBuffer(IndexBuffer&& rhs);
		const IndexBuffer& operator=(IndexBuffer&& rhs);

		IndexBuffer(const IndexBuffer& rhs);
		const IndexBuffer& operator=(const IndexBuffer& rhs);

		~IndexBuffer();
		
		IndexLayout index_layout() const { return index_layout_; }
		uint32_t index_count() const { return index_count_; }
		uint32_t size() const { return size_; }
		GLuint id() const { return id_; }
		const uint8_t* GetRawData() const
		{
			return data_.get();
		}

		const std::shared_ptr<uint8_t>& data()
		{
			return data_;
		}
	private:
		IndexLayout index_layout_;
		uint32_t index_count_;
		uint32_t size_;
		std::shared_ptr<uint8_t> data_;
		GLuint id_;
	};

	class VertexArrayObject
	{
	public:
		VertexArrayObject(const VertexBuffer& vertex_buffer,const IndexBuffer& index_buffer);
		VertexArrayObject(const VertexArrayObject& rhs);
		const VertexArrayObject& operator=(const VertexArrayObject& rhs);

		~VertexArrayObject();

		GLuint id() const { return id_; }
		const VertexBuffer& vertex_buffer() const { return vertex_buffer_; }
		const IndexBuffer& index_buffer() const { return index_buffer_; }
	private:
		GLuint id_;
		VertexBuffer vertex_buffer_;
		IndexBuffer index_buffer_;
	};
}

#endif
