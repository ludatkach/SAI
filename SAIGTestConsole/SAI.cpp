
#include "SAI.h"

std::string gsLogData;
std::string GetLastLog()
{ 
	return gsLogData; 
}

void A::do_stuff_internal(size_t size)
{
	std::vector<int> v(size);  // this allocator can throw std::bad_alloc exception. need to add test case

	std::srand(unsigned(std::time(nullptr)));
	std::generate(v.begin(), v.end(), std::rand);

	FILE* fp = fopen("aaa.bbb", "w");

	if (fp)
	{
		size_t w = fwrite(v.data(), sizeof(int), v.size(), fp);

		if (w == v.size())
		{
			LOG("Success!");
		}
		else
		{
			ERROR("Error1");
		}
	}
	else
	{
		ERROR("Error2");
	}
}

void A::do_stuff(size_t size)
{
	try
	{
		do_stuff_internal(size);
	}

	catch (std::bad_alloc &e)
	{
		ERROR(e.what());
	}

	catch (std::range_error &e)
	{
		ERROR(e.what());
	}

	catch (std::exception &e)
	{
		ERROR(e.what());
	}
}