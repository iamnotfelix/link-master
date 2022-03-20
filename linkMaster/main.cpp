
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

//TODO: add validation for integer input
//TODO: move the idCount from the domain to the repo
//TODO: add 'left unchanged' feature to update functionality(add to services a getElement method)
