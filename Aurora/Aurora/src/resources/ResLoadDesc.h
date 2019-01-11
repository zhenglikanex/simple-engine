#ifndef RES_LOAD_DESC_H_
#define RES_LOAD_DESC_H_

#include <string>
#include <memory>

namespace aurora
{
	class ResLoadDesc
	{
	public:
		ResLoadDesc();
		virtual ~ResLoadDesc() = 0;

		// ͨ������������������Դ
		virtual std::shared_ptr<void> Create() = 0;

		const std::string& name() const { return name_; }
	protected:
		std::string name_;
	};
}

#endif
