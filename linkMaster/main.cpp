
#include "tests.h"

#include <iostream>
#include <crtdbg.h>


int main()
{
	testVector();

	_CrtDumpMemoryLeaks();

	int x = getchar();
}