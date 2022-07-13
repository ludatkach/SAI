#pragma once

#include <vector>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <exception>
#include <sstream>
#include <iostream>
#include <new>

extern std::string gsLogData;

#define ERROR(s) {std::ostringstream stringStream; stringStream << s; gsLogData = stringStream.str(); std::cout << gsLogData << std::endl;}
#define LOG(s)  {std::ostringstream stringStream; stringStream << s; gsLogData = stringStream.str(); std::cout << gsLogData << std::endl;}

std::string GetLastLog();

class A
{
public:
	A(int v) : m_val(v) {};

	void do_stuff(size_t size);

protected:
	virtual void do_stuff_internal(size_t size);
	virtual FILE* fopen(const char* filename, const char* mode)
	{
		return ::fopen(filename, mode);
	}
	virtual size_t fwrite(const void* buffer,size_t size,size_t count,FILE* stream)
	{
		return ::fwrite(buffer, size, count, stream);
	}

private:
	size_t m_val;
};