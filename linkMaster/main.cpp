
#include "tests.h"

#include <iostream>
#include <crtdbg.h>


int main()
{
	testVector();
	testTutorial();
	testRepository();

	_CrtDumpMemoryLeaks();

	int x = getchar();
}