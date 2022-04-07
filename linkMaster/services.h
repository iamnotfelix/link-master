#pragma once

#include "repository.h"


class TutorialServices
{
private:
	TutorialRepo& repo;

public:
	TutorialServices(TutorialRepo& repo);

	/*
	* Initializes the repository with some tutorials.
	*/
	void initRepo();

	/*
	* Returns the number of elements in the repository.
	*/
	int getSize();

	/*
	* Returns a dynamic array containing a copy of the repository.
	*/
	std::vector<Tutorial> getAll();

	/*
	* Adds a tutorial.
	*/
	void add(std::string title, std::string presenter, int duration, int likes, std::string link);
	
	/*
	* Removes a tutorial with a given id.
	*/
	void remove(const unsigned int id);

	/*
	* Update a tutorial with a given id.
	*/
	void update(const unsigned int id, std::string title, std::string presenter, int duration, int likes, std::string link);
};
