#pragma once

#include <fstream>

namespace libS101{

class File: public std::fstream{
	public:
		void write(const void *buffer, size_t size);
		size_t read(void *buffer, size_t size);
		long long length();
};

};