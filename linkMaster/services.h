#pragma once

#include "repository.h"


class TutorialServices
{
private:
	TutorialRepo& repo;

public:
	TutorialServices(TutorialRepo& repo);

	void initRepo();

	int getSize();
	DynamicVector<Tutorial> getAll();

	void add(std::string title, std::string presenter, int duration, int likes, std::string link);
	void remove(const unsigned int id);
	void update(const unsigned int id, std::string title, std::string presenter, int duration, int likes, std::string link);
};
