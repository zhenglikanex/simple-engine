#ifndef UTIL_H_
#define UTIL_H_

#include <string>

// BKDR Hash Function
inline unsigned int BKDRHash(const char *str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;

	while (*str)
	{
		hash = hash * seed + (*str++);
	}

	return (hash & 0x7FFFFFFF);
}

inline unsigned int FSTR(const char *str)
{
	return BKDRHash(str);
}

inline unsigned int FSTR(const std::string& str)
{
	return FSTR(str.c_str());
}

#endif
