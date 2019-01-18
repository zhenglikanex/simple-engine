#include "VertexLayout.h"

namespace aurora
{
	VertexBuffer::VertexBuffer(VertexLayout vertex_layout, uint32_t vertex_count, const uint8_t* data)
		:vertex_layout_(vertex_layout)
		, vertex_count_(vertex_count)
	{
		size_ = VertexSize(vertex_layout) * vertex_count;
		uint8_t* raw_data = (uint8_t*)malloc(size_);
		memcpy(raw_data, data, size_);
		data_ = std::shared_ptr<uint8_t>(raw_data, [](uint8_t* p)
		{
			free(p);
		});

		glGenBuffers(1, &id_);
		glBindBuffer(GL_ARRAY_BUFFER,id_);
		glBufferData(GL_ARRAY_BUFFER, size_, data_.get(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER,0);
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& rhs)
		:vertex_layout_(rhs.vertex_layout_)
		, vertex_count_(rhs.vertex_count_)
		, size_(rhs.size_)
		, data_(std::move(rhs.data_))
		, id_(rhs.id_)
	{
		
	}

	const VertexBuffer& VertexBuffer::operator=(VertexBuffer&& rhs)
	{
		vertex_layout_ = rhs.vertex_layout_;
		vertex_count_ = rhs.vertex_count_;
		size_ = rhs.size_;
		data_ = std::move(rhs.data_);
		id_ = rhs.id_;

		return *this;
	}

	VertexBuffer::VertexBuffer(const VertexBuffer& rhs)
		: vertex_layout_(rhs.vertex_layout_)
		, vertex_count_(rhs.vertex_count_)
		, size_(rhs.size_)
		, data_(rhs.data_)
		, id_(rhs.id_)
	{

	}

	const VertexBuffer& VertexBuffer::operator=(const VertexBuffer& rhs)
	{
		vertex_layout_ = rhs.vertex_layout_;
		vertex_count_ = rhs.vertex_count_;
		size_ = rhs.size_;
		data_ = rhs.data_;
		id_ = rhs.id_;

		return *this;
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &id_);
	}


	IndexBuffer::IndexBuffer(IndexLayout index_layout, uint32_t index_count,const uint8_t* data)
		:index_layout_(index_layout)
		,index_count_(index_count)
	{
		size_ = IndexSize(index_layout) * index_count_;
		uint8_t* raw_data = (uint8_t*)malloc(size_);
		std::memcpy(raw_data, data, size_);
		
		data_ = std::shared_ptr<uint8_t>(raw_data, [](uint8_t* p)
		{
			free(p);
		});

		glGenBuffers(1, &id_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, data_.get(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::IndexBuffer(IndexBuffer&& rhs)
		:index_layout_(rhs.index_layout_)
		, index_count_(rhs.index_count_)
		, size_(rhs.size_)
		, data_(std::move(rhs.data_))
		, id_(rhs.id_)
	{

	}

	const IndexBuffer& IndexBuffer::operator=(IndexBuffer&& rhs)
	{
		index_layout_ = rhs.index_layout_;
		index_count_ = rhs.index_count_;
		size_ = rhs.size_;
		data_ = std::move(rhs.data_);
		id_ = rhs.id_;

		return *this;
	}

	IndexBuffer::IndexBuffer(const IndexBuffer& rhs)
		: index_layout_(rhs.index_layout_)
		, index_count_(rhs.index_count_)
		, size_(rhs.size_)
		, data_(rhs.data_)
		, id_(rhs.id_)
	{
		
	}

	const IndexBuffer& IndexBuffer::operator=(const IndexBuffer& rhs)
	{
		index_layout_ = rhs.index_layout_;
		index_count_ = rhs.index_count_;
		size_ = rhs.size_;
		data_ = rhs.data_;
		id_ = rhs.id_;

		return *this;
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &id_);
	}

	VertexArrayObject::VertexArrayObject(const VertexBuffer& vertex_buffer, const IndexBuffer& index_buffer)
		:vertex_buffer_(vertex_buffer)
		,index_buffer_(index_buffer)
	{
		glGenVertexArrays(1, &id_);
		glBindVertexArray(id_);

		// 上传vertex_buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_.id());

		// 上传index_buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_.id());

		// 绑定顶点属性
		switch (vertex_buffer.vertex_layout())
		{
		case VertexLayout::kP3FN3FT2F:
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexSize(vertex_buffer_.vertex_layout()), (void*)offsetof(Vertex_P3FN3FT2F, position));
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VertexSize(vertex_buffer_.vertex_layout()), (void*)offsetof(Vertex_P3FN3FT2F, normal));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VertexSize(vertex_buffer_.vertex_layout()), (void*)offsetof(Vertex_P3FN3FT2F, texcoords));
			break;
		case VertexLayout::kP3FN3FT2FT3FB3F:
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexSize(vertex_buffer_.vertex_layout()), (void*)offsetof(Vertex_P3FN3FT2FT3FB3F, position));
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VertexSize(vertex_buffer_.vertex_layout()), (void*)offsetof(Vertex_P3FN3FT2FT3FB3F, normal));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VertexSize(vertex_buffer_.vertex_layout()), (void*)offsetof(Vertex_P3FN3FT2FT3FB3F, texcoords));
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, VertexSize(vertex_buffer_.vertex_layout()), (void*)offsetof(Vertex_P3FN3FT2FT3FB3F, tangent));
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, VertexSize(vertex_buffer_.vertex_layout()), (void*)offsetof(Vertex_P3FN3FT2FT3FB3F, bitangent));
		default:
			break;
		}

		glBindVertexArray(0);
	}

	VertexArrayObject::VertexArrayObject(const VertexArrayObject& rhs)
		: id_(rhs.id_)
		, vertex_buffer_(rhs.vertex_buffer_)
		, index_buffer_(rhs.index_buffer_)
	{

	}

	const VertexArrayObject& VertexArrayObject::operator=(const VertexArrayObject& rhs)
	{
		vertex_buffer_ = rhs.vertex_buffer_;
		index_buffer_ = rhs.index_buffer_;

		return *this;
	}

	VertexArrayObject::~VertexArrayObject()
	{
		glDeleteVertexArrays(1, &id_);
	}
}