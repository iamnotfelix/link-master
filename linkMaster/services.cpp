
#include "services.h"


int TutorialServices::getSize()
{
	return this->repo.getSize();
}

TutorialServices::TutorialServices(TutorialRepo& repo) : repo{ repo } {}

DynamicVector<Tutorial> TutorialServices::getAll()
{
	return this->repo.getAll();
}

void TutorialServices::add(std::string title, std::string presenter, int duration, int likes, std::string link)
{
	Tutorial tutorial(title, presenter, duration, likes, link);

	this->repo.add(tutorial);
}

void TutorialServices::remove(const unsigned int id)
{
	this->repo.remove(id);
}

void TutorialServices::update(const unsigned int id, std::string title, std::string presenter, int duration, int likes, std::string link)
{
	Tutorial tutorial(title, presenter, duration, likes, link);

	this->repo.update(id, tutorial);
}


