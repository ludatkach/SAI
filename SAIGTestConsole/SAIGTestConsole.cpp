// SAIGTestConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "gtest\gtest.h"
#include "SAI.h"


TEST(SAI, Exception_throw_bad_alloc)
{
	class TestA : public A
	{
	public:
		TestA(int n) : A(n) {};
		void test_do_stuff_internal(size_t size)
		{
			do_stuff_internal(size);
		}
	protected:
		virtual void do_stuff_internal(size_t size)
		{
			throw std::bad_alloc();
		}
	};

	TestA tA(10);
	EXPECT_THROW(tA.test_do_stuff_internal(80), std::bad_alloc);
}

TEST(SAI, Exception_catch_bad_alloc)
{
	class TestA : public A
	{
	public:
		TestA(int n) : A(n) {};		
	protected:
		virtual void do_stuff_internal(size_t size)
		{
			throw std::bad_alloc();
		}
	};

	TestA tA(10);
	EXPECT_NO_THROW(tA.do_stuff(80));
}

TEST(SAI, Exception_catch_overflow_error)
{
	class TestA : public A
	{
	public:
		TestA(int n) : A(n) {};
	protected:
		virtual void do_stuff_internal(size_t size)
		{
			throw std::overflow_error("Testing overflow_error");
		}
	};

	TestA tA(47);
	EXPECT_NO_THROW(tA.do_stuff(34));

}

TEST(SAI, fopen_test)
{
	class TestA : public A
	{
	public:
		TestA(int n) : A(n) {};
	protected:
		virtual FILE* fopen(const char* filename, const char* mode)
		{
			return NULL;
		}
	};

	TestA tA(10);
	tA.do_stuff(7);
	
	EXPECT_EQ(std::string("Error2"), GetLastLog());
}

TEST(SAI, fwrite_test)
{
	class TestA : public A
	{
	public:
		TestA(int n) : A(n) {};
	protected:
		virtual size_t fwrite(const void* buffer, size_t size, size_t count, FILE* stream)
		{
			return count > 1 ? --count : 0;
		}
	};

	TestA tA(10);
	tA.do_stuff(7);

	EXPECT_EQ(std::string("Error1"), GetLastLog());
}

TEST(SAI, test_positive)
{
	A tA(10);
	tA.do_stuff(5);

	EXPECT_EQ(std::string("Success!"), GetLastLog());
}