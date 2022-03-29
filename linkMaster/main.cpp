
#include "tests.h"
#include "ui.h"
#include "userUI.h"

#include <iostream>
#include <crtdbg.h>


void printMenu()
{
	std::cout << std::endl;
	std::cout << "Menu:" << std::endl;
	std::cout << "admin\tAdministrator mode." << std::endl;
	std::cout << "user\tUser mode." << std::endl;
	std::cout << "exit\tExit the application." << std::endl;
}

void commandHandler(UI& ui, UserUI& userUI)
{
	printMenu();
	while (true)
	{
		std::string command;
		std::cout << ">>>";
		std::cin >> command;
		if (command == "exit")
		{
			break;
		}
		else if (command == "admin")
		{
			ui.start();
			printMenu();
		}
		else if (command == "user")
		{
			userUI.start();
			printMenu();
		}
		else
			std::cout << "Invalid command!" << std::endl;
	}
}

void start()
{
	TutorialRepo repo{ "tutorialRepo.txt" };
	TutorialServices services{ repo };
	//services.initRepo();

	TutorialRepo watchList{ "watchList.txt" };
	UserServices userServices{ repo, watchList };

	UI ui{ services };
	UserUI userUI{ userServices };

	commandHandler(ui, userUI);
}
 
void tests()
{
	testVector();
	testTutorial();
	testRepository();
	testServices();
	testUserServices();
}

int main()
{
	//tests();
	start();

	_CrtDumpMemoryLeaks();
}
