
#include "repository.h"

#include <exception>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>


Repository::Repository(std::string filePath) : filePath{ filePath }
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
			this->vector.push_back(tutorial);
		}

		f.close();
	}
}

Repository::~Repository()
{
	if (!this->filePath.empty())
	{
		std::ofstream f(this->filePath);
		for (Tutorial tutorial : this->vector)
		{
			std::string line = tutorial.getTitle() + "," + tutorial.getPresenter() + "," +
				std::to_string(tutorial.getDuration()) + "," + std::to_string(tutorial.getLikes()) + "," + tutorial.getLink() + "\n";
			f << line;
		}

		f.close();
	}
}

int Repository::getSize()
{
	return this->vector.size();
}

bool Repository::find(const Tutorial& tutorial)
{
	auto result = std::find(this->vector.begin(), this->vector.end(), tutorial);
	return (result != this->vector.end());
}

int Repository::getPosition(const unsigned int id)
{
	for (int i = 0; i < this->vector.size(); i++)
		if (this->vector[i].getId() == id)
			return i;

	throw std::exception("Tutorial not found!\n");
}

Tutorial Repository::getElement(const unsigned int id)
{
	int position = this->getPosition(id);

	return this->vector[position];
}

std::vector<Tutorial> Repository::getAll()
{
	return std::vector<Tutorial>{this->vector};
}

void Repository::add(const Tutorial& tutorial)
{
	if (this->find(tutorial))
		throw std::exception("Tutorial already exists!\n");

	this->vector.push_back(tutorial);
}

void Repository::remove(const unsigned int id)
{
	int position = this->getPosition(id);

	this->vector.erase(this->vector.begin() + position);
}

void Repository::update(const unsigned int id, std::string title, std::string presenter, int duration, int likes, std::string link)
{	
	int position = this->getPosition(id);

	Tutorial& tutorial = this->vector[position];

	tutorial.setTitle(title);
	tutorial.setPresenter(presenter);
	tutorial.setDuration(duration);
	tutorial.setLikes(likes);
	tutorial.setLink(link);
}
