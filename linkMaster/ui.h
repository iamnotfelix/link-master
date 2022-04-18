#pragma once

#include "services.h"
#include "validation.h"

class UI
{
private:
	TutorialServices& services;
	Validation validation{};
	void printMenu();
	void printList(std::vector<Tutorial>& list);
	void getCommand(std::string& command);
	void getInput(std::string& title, std::string& presenter, int& duration, int& likes, std::string& link);
	void addHandler();
	void deleteHandler();
	void updateHandler();
	void commandHandler();

public:
	UI(TutorialServices& services);
	void start();
};
