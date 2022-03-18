
#include "tests.h"

#include <iostream>
#include <crtdbg.h>


int main()
{
	testVector();
	testTutorial();

	_CrtDumpMemoryLeaks();

	int x = getchar();
}