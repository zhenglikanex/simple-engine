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
}