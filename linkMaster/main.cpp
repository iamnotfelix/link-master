
#include "tests.h"
#include "ui.h"

#include <iostream>
#include <crtdbg.h>


int main()
{
	/*testVector();
	testTutorial();
	testRepository();
	testServices();*/

	TutorialRepo repo;
	TutorialServices services{ repo };
	UI ui{ services };

	ui.start();

	_CrtDumpMemoryLeaks();

	int x = getchar();
}

//TODO: add 'left unchanged' feature to update functionality(add to services a getElement method)
