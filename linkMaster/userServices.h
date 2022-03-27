#pragma once

#include "repository.h"


class UserServices
{
private:
	TutorialRepo& repo;
	TutorialRepo& watchList;

public:
	UserServices(TutorialRepo& repo, TutorialRepo& watchList);
	DynamicVector<Tutorial> getTutorialsByPresenter(const std::string presenter="");
	void addToWatchList(const Tutorial& tutorial);
	void deleteFromWatchList(const Tutorial& tutorial);
	void likeTutorial(const Tutorial& tutorial);
	DynamicVector<Tutorial> getWatchList();

};

