// Experiments.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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

int _tmain(int argc, _TCHAR* argv[])
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

	return 0;
}

