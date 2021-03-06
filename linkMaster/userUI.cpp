
#include "userUI.h"
#include "exception.h"

#include <iostream>


UserUI::UserUI(UserServices& userServices) : userServices{ userServices } {}

void UserUI::printMenu()
{
	std::cout << std::endl;
	std::cout << "Menu:" << std::endl;
	std::cout << "tuts\tSee available tutorials." << std::endl;
	std::cout << "watch\tSee your watch list." << std::endl;
	std::cout << "open\tOpen the watch list in another app." << std::endl;
	std::cout << "help\tShow this menu." << std::endl;
	std::cout << "exit\tExit the application." << std::endl;
}

void UserUI::diplayTutorial(const Tutorial& tutorial)
{
	int duration = tutorial.getDuration();
	int minutes = duration / 60;
	int seconds = duration % 60;

	std::cout << std::endl;
	std::cout.width(5); std::cout << std::left << "ID";
	std::cout.width(20); std::cout << std::right << "Title";
	std::cout.width(20); std::cout << std::right << "Presenter";
	std::cout.width(10); std::cout << std::right << "Duration";
	std::cout.width(10); std::cout << std::right << "Likes";
	std::cout.width(60); std::cout << std::right << "Link";
	std::cout << std::endl;
	std::cout << tutorial;

	std::string aux = "start " + tutorial.getLink();
	char* link = &aux[0];
	system(link);
}

void UserUI::printActionMenu()
{
	std::cout << "Choose an action..." << std::endl;
	std::cout << "add\tAdd to watch list." << std::endl;
	std::cout << "next\tGo to next tutorial." << std::endl;
	std::cout << "quit\tQuit seeing tutorials." << std::endl;
}

void UserUI::printWatchMenu()
{
	std::cout << "Choose an action..." << std::endl;
	std::cout << "delete\tRemove tutorial from watch list." << std::endl;
	std::cout << "next\tGo to next tutorial." << std::endl;
	std::cout << "quit\tQuit seeing tutorials." << std::endl;
}

void UserUI::actionHandler(const Tutorial& tutorial)
{
	while (true)
	{
		std::string action;
		std::cout << ">>>";
		std::cin >> action;
		if (action == "add")
		{
			this->userServices.addToWatchList(tutorial);
			break;
		}
		else if (action == "next")
			break;
		else if (action == "quit")
			throw UIException("Quitted successfully!\n");
		else
			std::cout << "Invalid action!" << std::endl;
	}
}

void UserUI::tutorialsHandler()
{
	std::string presenter;
	
	std::cin.clear();
	std::cin.ignore(10000, '\n');

	std::cout << "Presenter: ";
	std::getline(std::cin, presenter);

	std::vector<Tutorial>  tutorials = this->userServices.getTutorialsByPresenter(presenter);
	
	if (tutorials.size() == 0)
		throw UIException("No matching tutorials!\n");

	int i = 0;
	while (true)
	{
		Tutorial tutorial = tutorials[i];

		this->diplayTutorial(tutorial);
		this->printActionMenu();
		this->actionHandler(tutorial);

		i++;
		if (i == tutorials.size())
			i = 0;
	}
}

bool UserUI::promptLike()
{
	std::cout << "Do you want to like the tutorial?(y/n) ";
	std::string like;
	std::cin >> like;
	return (like == "y");
}

bool UserUI::watchHandler(const Tutorial& tutorial)
{
	while (true)
	{
		std::string action;
		std::cout << ">>>";
		std::cin >> action;
		if (action == "delete")
		{
			bool likes = this->promptLike();
			if (likes) this->userServices.likeTutorial(tutorial);

			this->userServices.deleteFromWatchList(tutorial);
			return true;
		}
		else if (action == "next")
			return false;
		else if (action == "quit")
			throw UIException("Quitted successfully!\n");
		else
			std::cout << "Invalid action!" << std::endl;
	}
	return false;
}

void UserUI::watchListHandler()
{
	if (this->userServices.getWatchListSize() == 0)
		throw UIException("Watch list is empty!\n");
	
	int i = 0;
	while (true && this->userServices.getWatchListSize() != 0)
	{
		std::vector<Tutorial> watchList = this->userServices.getWatchList();
		Tutorial tutorial = watchList[i];

		this->diplayTutorial(tutorial);
		this->printWatchMenu();
		bool deleted = this->watchHandler(tutorial);

		if (!deleted)
			i++;
		if (i >= this->userServices.getWatchListSize())
			i = 0;
	}
	throw UIException("Watch list is empty!\n");
}

void UserUI::openHandler()
{
	std::string aux = "start " + this->userServices.getWatchListFilePath();
	char* link = &aux[0];
	system(link);
}

void UserUI::commandHandler()
{
	while (true)
	{
		std::string command;
		std::cout << ">>>";
		std::cin >> command;

		try
		{
			if (command == "exit")
			{
				break;
			}
			else if (command == "help")
			{
				this->printMenu();
			}
			else if (command == "tuts")
			{
				this->tutorialsHandler();
			}
			else if (command == "watch")
			{
				this->watchListHandler();
			}
			else if (command == "open")
			{
				this->openHandler();
			}
			else
				throw UIException("Invalid command!\n");
		}
		catch (const Exception& e)
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << e.what();
		}
	}
}

void UserUI::start()
{
	this->printMenu();
	this->commandHandler();
}
