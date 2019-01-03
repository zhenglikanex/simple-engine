#ifndef CLOCK_H_
#define CLOCK_H_

#include <chrono>

namespace aurora
{
	class Clock
	{
	public:

		using clock_type = std::chrono::high_resolution_clock;
		
		Clock()
			:time_point_(clock_type::now())
		{
			
		}
		
		uint64_t Count()
		{
			return time_point_.time_since_epoch().count();
		}

		float GetSecond(const Clock& clock)
		{
			float elapsed = static_cast<float>((time_point_ - clock.time_point_).count());
			return elapsed * clock_type::period::num / clock_type::period::den;
		}

		float operator-(const Clock& clock)
		{
			return GetSecond(clock);
		}

	private:
		clock_type::time_point time_point_;
	};
}

#endif
