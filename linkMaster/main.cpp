
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
	services.initRepo();
	UI ui{ services };

	ui.start();

	_CrtDumpMemoryLeaks();
}
