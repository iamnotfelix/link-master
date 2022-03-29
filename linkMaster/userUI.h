#pragma once

#include "userServices.h"


class UserUI
{
private:
	UserServices& userServices;
	
	void printMenu();
	void diplayTutorial(const Tutorial& tutorial);
	void printActionMenu();
	void printWatchMenu();

	void actionHandler(const Tutorial& tutorial);
	void tutorialsHandler();

	bool promptLike();
	bool watchHandler(const Tutorial& tutorial);
	void watchListHandler();

	void commandHandler();

public:
	UserUI(UserServices& userServices);
	void start();
};

