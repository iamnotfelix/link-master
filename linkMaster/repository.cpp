
#include "repository.h"

#include <exception>
#include <string>


int TutorialRepo::getSize()
{
	return this->vector.getSize();
}

bool TutorialRepo::find(const Tutorial& tutorial)
{
	for (int i = 0; i < this->vector.getSize(); i++)
		if (this->vector.getElement(i) == tutorial)
			return true;
	
	return false;
}

int TutorialRepo::getPosition(const unsigned int id)
{
	for (int i = 0; i < this->vector.getSize(); i++)
		if (this->vector.getElement(i).getId() == id)
			return i;

	throw std::exception("Tutorial not found!\n");
}

Tutorial TutorialRepo::getElement(const unsigned int id)
{
	int position = this->getPosition(id);

	return this->vector[position];
}

DynamicVector<Tutorial> TutorialRepo::getAll()
{
	return DynamicVector<Tutorial>{this->vector};
}

void TutorialRepo::add(const Tutorial& tutorial)
{
	if (this->find(tutorial))
		throw std::exception("Tutorial already exists!\n");

	this->vector.add(tutorial);
}

void TutorialRepo::remove(const unsigned int id)
{
	int position = this->getPosition(id);

	this->vector.remove(position);
}

void TutorialRepo::update(const unsigned int id, std::string title, std::string presenter, int duration, int likes, std::string link)
{	
	int position = this->getPosition(id);

	Tutorial& tutorial = this->vector.getElement(position);

	tutorial.setTitle(title);
	tutorial.setPresenter(presenter);
	tutorial.setDuration(duration);
	tutorial.setLikes(likes);
	tutorial.setLink(link);
}
