#ifndef DATA_H_
#define DATA_H_

#include <vector>
#include <memory>

namespace aurora
{
	class Data
	{
	public:
		Data(size_t size)
			:cur_(0)
		{
			set_size(size);
		}

		Data(Data&& rhs)
			:size_(rhs.size_)
			,raw_(std::move(rhs.raw_))
			,cur_(rhs.cur_)
		{
			
		}

		const Data& operator=(Data&& rhs)
		{
			size_ = rhs.size_;
			raw_ = std::move(raw_);
			return *this;
		}

		Data(const Data& rsh) = delete;
		const Data& operator=(const Data& rhs) = delete;

		void set_size(size_t size) 
		{ 
			size_ = size;
			raw_.resize(size_);
		}

		size_t size() const { return size_; }

		const uint8_t* raw() const { return raw_.data(); }

		void write(uint8_t* data, size_t size)
		{
			if (raw_.size() + size > size_)
			{
				set_size(size);
			}

			//std::memcpy(raw_.
		}

		void read(uint8_t data, size_t size)
		{

		}
	private:
		size_t size_;
		// 有优化空间,用vector会有内存让费
		std::vector<uint8_t> raw_;

		size_t cur_;
	};
}

#endif
