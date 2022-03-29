
#include "repository.h"

#include <exception>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>


TutorialRepo::TutorialRepo(std::string filePath) : filePath{ filePath }
{
	if (!filePath.empty())
	{
		std::ifstream f(filePath);

		std::string line;
		while (std::getline(f, line))
		{
			std::stringstream lineStream(line);
			std::string token;
			std::vector <std::string> tokens;

			while (std::getline(lineStream, token, ','))
				tokens.push_back(token);

			Tutorial tutorial(this->getNextId(), tokens[0], tokens[1], 
				std::stoi(tokens[2]), std::stoi(tokens[3]), tokens[4]);
			this->vector.add(tutorial);
		}

		f.close();
	}
}

#include <iostream>
TutorialRepo::~TutorialRepo()
{
	if (!this->filePath.empty())
	{
		std::ofstream f(this->filePath);
		for (int i = 0; i < this->vector.getSize(); i++)
		{
			Tutorial tutorial = this->vector.getElement(i);
			std::string line = tutorial.getTitle() + "," + tutorial.getPresenter() + "," +
				std::to_string(tutorial.getDuration()) + "," + std::to_string(tutorial.getLikes()) + "," + tutorial.getLink() + "\n";
			f << line;
		}

		f.close();
	}
}

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
