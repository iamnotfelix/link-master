
#include "tests.h"

#include <iostream>
#include <crtdbg.h>


int main()
{
	testVector();
	testTutorial();
	testRepository();
	testServices();

	_CrtDumpMemoryLeaks();

	int x = getchar();
}