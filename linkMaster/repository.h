#pragma once

#include "vector.h"
#include "tutorial.h"


class TutorialRepo
{
private:
	DynamicVector <Tutorial> vector;
	int getPosition(const unsigned int id);
	unsigned int idCount=0;
public:

	inline int getNextId() { return this->idCount++; }
	int getSize();
	bool find(const Tutorial& tutorial);
	Tutorial getElement(const unsigned int id);
	DynamicVector<Tutorial> getAll();

	void add(const Tutorial& tutorial);
	void remove(const unsigned int id);
	void update(const unsigned int id, std::string title, std::string presenter, int duration, int likes, std::string link);
};