#pragma once

#include "repository.h"


class UserServices
{
private:
	Repository& repo;
	Repository& watchList;

public:
	UserServices(Repository& repo, Repository& watchList);
	/*
	* Returns a dynamic vector containing all the tutorials from the repo that match the given presenter.
	*	presenter - the presenter to be matched
	*/
	std::vector<Tutorial> getTutorialsByPresenter(const std::string presenter="");

	/*
	* Adds a tutorial to the watchlist.
	*	tutorial - the tutorial to be added
	*/
	void addToWatchList(const Tutorial& tutorial);
	
	/*
	* Deletes a tutorial from the watch list.
	*	tutorial - the tutorial to be deleted
	*/
	void deleteFromWatchList(const Tutorial& tutorial);
	
	/*
	* Likes a given tutorial from the repository.
	*	tutorial - the tutorial to be liked
	*/
	void likeTutorial(const Tutorial& tutorial);

	/*
	* Returns the size of the watch list.
	*/
	int getWatchListSize();

	/*
	* Returns a dynamic vector containing the watch list.
	*/
	std::vector<Tutorial> getWatchList();

	std::string getWatchListFilePath();
};

