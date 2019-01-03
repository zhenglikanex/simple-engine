#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <memory>

namespace aurora
{

	template<class T>
	class Singleton
	{
	public:
		Singleton(){}

		~Singleton(){}

		static std::shared_ptr<T> GetInstance()
		{
			if (instance_) {
				return instance_;
			}
			instance_ = std::make_shared<T>();
			instance_->Initialize();

			return instance_;
		}

		virtual bool Initialize()
		{
			return true;
		}

	protected:
		static std::shared_ptr<T> instance_;
	};

	template<class T> std::shared_ptr<T> Singleton<T>::instance_ = std::shared_ptr<T>();
}

#endif