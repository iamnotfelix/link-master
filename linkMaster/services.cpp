
#include "services.h"


int TutorialServices::getSize()
{
	return this->repo.getSize();
}

TutorialServices::TutorialServices(TutorialRepo& repo) : repo{ repo } {}

void TutorialServices::initRepo()
{
	this->add("Title 1", "Presenter 1", 100, 1000, "Link 1");
	this->add("Title 2", "Presenter 2", 200, 2000, "Link 2");
	this->add("Title 3", "Presenter 3", 300, 3000, "Link 3");
	this->add("Title 4", "Presenter 4", 400, 4000, "Link 4");
	this->add("Title 5", "Presenter 5", 500, 5000, "Link 5");
	this->add("Title 6", "Presenter 6", 600, 6000, "Link 6");
	this->add("Title 7", "Presenter 7", 700, 7000, "Link 7");
	this->add("Title 8", "Presenter 8", 800, 8000, "Link 8");
	this->add("Title 9", "Presenter 9", 900, 9000, "Link 9");
	this->add("Title 10", "Presenter 10", 1000, 10000, "https://en.cppreference.com/w/");
}

DynamicVector<Tutorial> TutorialServices::getAll()
{
	return this->repo.getAll();
}

void TutorialServices::add(std::string title, std::string presenter, int duration, int likes, std::string link)
{
	Tutorial tutorial(this->repo.getNextId(), title, presenter, duration, likes, link);

	this->repo.add(tutorial);
}

void TutorialServices::remove(const unsigned int id)
{
	this->repo.remove(id);
}

void TutorialServices::update(const unsigned int id, std::string title, std::string presenter, int duration, int likes, std::string link)
{
	this->repo.update(id, title, presenter, duration, likes, link);
}


