// Experiments.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef unsigned char *byte_pointer;

bool isEqual(const int &x, const int &y);
void TestStructure();
void show_bytes(byte_pointer start, int len);

struct Experiment
{
	int foo;
	char bar;
	double baz;
	short bil;
};

bool IsEqual(const int &x, const int &y)
{
	return !(x ^ y);
}

template <typename T>
size_t GetSize(const T &object)
{
	size_t retVal;
	retVal = ((size_t)(&(object) + 1) - (size_t)(&(object)));
	return retVal;
}

void TestStructure()
{
	int testObject1;
	Experiment testObject2;
	bool test1 = IsEqual(0x80000000, 0x7fffffff);
	bool test2 = IsEqual(0x80000000, 0x80000000);
	bool test3 = (GetSize(testObject1) == sizeof(testObject1));
	bool test4 = (GetSize(testObject2) == sizeof(testObject2));
	printf("Test 1: %s \n", ((!test1) ? "PASS" : "FAIL"));
	printf("Test 2: %s \n", (test2 ? "PASS" : "FAIL"));
	printf("Test 3: %s \n", (test3 ? "PASS" : "FAIL"));
	printf("Test 4: %s \n", (test4 ? "PASS" : "FAIL"));

	char cTest = 'R';
	printf("%u \n", cTest);
	printf("%c \n", cTest);

	cTest++;

	printf("%u \n", cTest);
	printf("%c \n", cTest);

	printf("%ld \n", GetSize(testObject2));
	printf("%ld \n", sizeof(testObject2));
}

void show_bytes(byte_pointer start, int len)
{
	for (int i = 0; i < len; i++)
	{
		printf(" %.2x", start[i]);
	}
	printf("\n");
}

template <class T>
void show(T x)
{
	show_bytes((byte_pointer)&x, sizeof(x));
}

void TestBits()
{
	int x = 20;
	int y = -21;
	short sx = 20;
	short sy = -21;

	show(x);
	show(y);


	show(sx);
	show(sy);
}


int _tmain(int argc, _TCHAR* argv[])
{
	TestStructure();
	TestBits();

	return 0;
}


