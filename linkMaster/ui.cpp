
#include "ui.h"

#include <iostream>
#include <stdlib.h>


UI::UI(TutorialServices& services) : services{services} {}

void UI::printMenu()
{
	std::cout << "Menu:" << std::endl;
	std::cout << "add\tAdd a tutorial." << std::endl;
	std::cout << "delete\tDelete a tutorial." << std::endl;
	std::cout << "update\tUpdate a tutorial." << std::endl;
	std::cout << "list\tList all tutorials." << std::endl;
	std::cout << std::endl;
	std::cout << "help\tShow this menu." << std::endl;
	std::cout << "exit\tExit the app." << std::endl;
}

void UI::printList(std::vector<Tutorial>& list)
{
	if (list.size() == 0)
		throw std::exception("There is nothing to print!\n");

	std::cout << "ID\tTitle\tPresenter\tDuration\tLikes\tLink\n";

	for (int i = 0; i < list.size(); i++)
	{
		Tutorial tutorial = list[i];

		int duration = tutorial.getDuration();
		int minutes = duration / 60;
		int seconds = duration % 60;

		std::cout << tutorial.getId() << "\t" << tutorial.getTitle() << "\t" << tutorial.getPresenter() << "\t"
			<< minutes << ":" << seconds << "\t" << tutorial.getLikes() << "\t"
			<< tutorial.getLink() << std::endl;
	}
}

void UI::getCommand(std::string& command)
{
	std::cout << ">>>";
	std::cin >> command;
}

void UI::getInput(std::string& title, std::string& presenter, int& duration, int& likes, std::string& link)
{
	std::cin.ignore(100, '\n');

	int minutes = 0, seconds = 0;

	std::cout << "Title: ";
	std::getline(std::cin, title);

	std::cout << "Presenter: ";
	std::getline(std::cin, presenter);

	while (true)
	{
		std::cout << "Minutes: ";
		while (!(std::cin >> minutes))
		{
			std::cin.clear();
			std::cin.ignore(100000, '\n');
			std::cout << "Enter a number!" << std::endl;
			std::cout << "Minutes: ";
		}
		if (minutes >= 0) break;
		std::cout << "Enter a positive value!" << std::endl;
	}

	while (true)
	{
		std::cout << "Seconds: ";
		while (!(std::cin >> seconds))
		{
			std::cin.clear();
			std::cin.ignore(100000, '\n');
			std::cout << "Enter a number!" << std::endl;
			std::cout << "Seconds: ";
		}
		if (seconds >= 0) break;
		std::cout << "Enter a positive value!" << std::endl;
	}

	while (true)
	{
		std::cout << "Likes: ";
		while (!(std::cin >> likes))
		{
			std::cin.clear();
			std::cin.ignore(100000, '\n');
			std::cout << "Enter a number!" << std::endl;
			std::cout << "Likes: ";
		}
		if (likes >= 0) break;
		std::cout << "Enter a positive value!" << std::endl;
	}

	std::cout << "Link: ";
	std::cin >> link;

	duration = minutes * 60 + seconds;
}

void UI::addHandler()
{
	std::string title, presenter, link;
	int duration = 0, likes = 0;

	this->getInput(title, presenter, duration, likes, link);
	
	this->services.add(title, presenter, duration, likes, link);
	
	std::cin.clear();
	std::cin.ignore(100000, '\n');
}

void UI::deleteHandler()
{
	int id = 0;

	while (true)
	{
		std::cout << "ID: ";
		while (!(std::cin >> id))
		{
			std::cin.clear();
			std::cin.ignore(100000, '\n');
			std::cout << "Enter a number!" << std::endl;
			std::cout << "ID: ";
		}
		if (id >= 0) break;
		std::cout << "Enter a positive value!" << std::endl;
	}

	this->services.remove(id);

	std::cin.clear();
	std::cin.ignore(100000, '\n');
}

void UI::updateHandler()
{
	int id = 0;

	while (true)
	{
		std::cout << "ID: ";
		while (!(std::cin >> id))
		{
			std::cin.clear();
			std::cin.ignore(100000, '\n');
			std::cout << "Enter a number!" << std::endl;
			std::cout << "ID: ";
		}
		if (id >= 0) break;
		std::cout << "Enter a positive value!" << std::endl;
	}

	std::string title, presenter, link;
	int duration = 0, likes = 0;

	std::cout << "Enter new values.." << std::endl;

	this->getInput(title, presenter, duration, likes, link);

	this->services.update(id, title, presenter, duration, likes, link);

	std::cin.clear();
	std::cin.ignore(100000, '\n');
}

void UI::commandHandler()
{
	while (true)
	{
		std::string command;
		this->getCommand(command);
		
		try
		{
			if (command == "exit")
			{
				break;
				//exit(0);
			}
			else if (command == "add")
			{
				this->addHandler();
				std::cout << "Added successfully!" << std::endl;
			}
			else if (command == "delete")
			{
				this->deleteHandler();
				std::cout << "Deleted successfully!" << std::endl;
			}
			else if (command == "update")
			{
				this->updateHandler();
				std::cout << "Updated successfully!" << std::endl;
			}
			else if (command == "list")
			{
				std::vector<Tutorial> list = this->services.getAll();
				this->printList(list);
			}
			else if (command == "help")
			{
				this->printMenu();
			}
			else
			{
				throw std::exception("Invalid command!\n");
			}
		}
		catch (std::exception& e)
		{
			std::cin.clear();
			std::cin.ignore(100000, '\n');
			std::cout << e.what();
		}
	}
}

void UI::start()
{
	this->printMenu();
	this->commandHandler();
}
