#pragma once

#include <vector>
#include "tutorial.h"


class Repository
{
protected:
	std::vector<Tutorial> vector;
	int getPosition(const unsigned int id);
	unsigned int idCount=0;
	std::string filePath;
public:

	Repository(std::string filePath="");
	~Repository();

	/*
	* Returns the next unique id.
	*/
	inline int getNextId() { return this->idCount++; }

	/*
	* Returns the number of elements in the repository.
	*/
	int getSize();

	/*
	* Checks if the a tutorial is in the repository.
	*	tutorial - the tutorial to be searched
	* Returns true if the tutorial is in the repository, false otherwise.
	*/
	bool find(const Tutorial& tutorial);

	/*
	* Gets an element with a given id.
	*	id - the id to search for
	* Returns the element or throws an exception if the element is not in the repository.
	*/
	Tutorial getElement(const unsigned int id);

	/*
	* Returns a vector containing a copy of the repository.
	*/
	std::vector<Tutorial> getAll();

	/*
	* Adds a tutorial to the repository.
	*/
	virtual void add(const Tutorial& tutorial);

	/*
	* Removes a tutorial from the repository with a given id.
	*/
	virtual void remove(const unsigned int id);

	/*
	* Update a tutorial from the repository with a given id.
	*/
	virtual void update(const unsigned int id, std::string title, std::string presenter, int duration, int likes, std::string link);
};