#ifndef RES_LOAD_DESC_H_
#define RES_LOAD_DESC_H_

#include <string>
#include <memory>

namespace aurora
{
	class ResLoadDesc
	{
	public:
		ResLoadDesc(const std::string& name);
		virtual ~ResLoadDesc() = 0;

		// 通过这个创建出具体的资源
		virtual std::shared_ptr<void> Create() = 0;

		const std::string& name() const { return name_; }
	private:
		std::string name_;
	};
}

#endif
