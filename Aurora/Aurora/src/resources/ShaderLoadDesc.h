#ifndef SHADER_LOAD_DESC_H_
#define SHADER_LOAD_DESC_H_

#include "ResLoadDesc.h"

namespace aurora
{
	class ShaderLoadDesc : public ResLoadDesc
	{
	public:
		ShaderLoadDesc(const std::string& vs_file,const std::string& fs_file);
		ShaderLoadDesc(const std::string& vs_file, const std::string& gs_file, const std::string& fs_file);
		~ShaderLoadDesc();

		virtual std::shared_ptr<void> Create() override;
	private:
		std::string vs_file_;
		std::string gs_file_;
		std::string fs_file_;
	};
}

#endif
