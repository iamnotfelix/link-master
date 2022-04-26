
#include "tests.h"
#include "ui.h"
#include "userUI.h"

#include <iostream>
#include <crtdbg.h>

#include <mysqlx/xdevapi.h>


void printMenuRepositories()
{
	std::cout << std::endl;
	std::cout << "Choose repository type:" << std::endl;
	std::cout << "memo\tRepository stored in memory." << std::endl;
	std::cout << "txt\tRepository stored in TXT files." << std::endl;
	std::cout << "csv\tRepository stored in CSV files." << std::endl;
	std::cout << "html\tRepository stored in HTML files." << std::endl;
	std::cout << "sql\tRepository stored in MySQL database." << std::endl;
	std::cout << "exit\tExit the application." << std::endl;
}

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
	printMenuRepositories();
	while (true)
	{
		std::string command;
		std::cout << ">>>";
		std::cin >> command;
		if (command == "exit")
		{
			exit(0);
		}
		else if (command == "memo")
		{
			Repository repo;
			TutorialServices services{ repo };
			services.initRepo();

			Repository watchList;
			UserServices userServices{ repo, watchList };

			UI ui{ services };
			UserUI userUI{ userServices };

			commandHandler(ui, userUI);
			printMenuRepositories();
		}
		else if (command == "txt")
		{
			TXTRepository repo{ "repository.txt" };
			TutorialServices services{ repo };

			TXTRepository watchList{ "watchList.txt" };
			UserServices userServices{ repo, watchList };

			UI ui{ services };
			UserUI userUI{ userServices };

			commandHandler(ui, userUI);
			printMenuRepositories();
		}
		else if (command == "csv")
		{
			CSVRepository repo{ "repository.csv" };
			TutorialServices services{ repo };

			CSVRepository watchList{ "watchList.csv" };
			UserServices userServices{ repo, watchList };

			UI ui{ services };
			UserUI userUI{ userServices };

			commandHandler(ui, userUI);
			printMenuRepositories();
		}
		else if (command == "html")
		{
			HTMLRepository repo{ "repository.html" };
			TutorialServices services{ repo };

			HTMLRepository watchList{ "watchList.html" };
			UserServices userServices{ repo, watchList };

			UI ui{ services };
			UserUI userUI{ userServices };

			commandHandler(ui, userUI);
			printMenuRepositories();
		}
		else if (command == "sql")
		{
			SQLRepository repo{ "localhost", 33060, "root", "root", "link_master", "tutorials" };
			TutorialServices services{ repo };

			SQLRepository watchList{ "localhost", 33060, "root", "root", "link_master", "watch_list" };
			UserServices userServices{ repo, watchList };

			UI ui{ services };
			UserUI userUI{ userServices };

			commandHandler(ui, userUI);
			printMenuRepositories();
		}
		else
			std::cout << "Invalid command!" << std::endl;
	}
}
 
void tests()
{
	testVector();
	testTutorial();
	testRepository();
	testServices();
	testUserServices();
	testException();
}

int main()
{
	//tests();
	start();

	_CrtDumpMemoryLeaks();
}
