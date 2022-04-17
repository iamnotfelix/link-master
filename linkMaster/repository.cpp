
#include "repository.h"

#include <exception>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>


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





TXTRepository::TXTRepository(std::string filePath) : filePath{ filePath }
{
	this->readAll();
}


void TXTRepository::readAll()
{
	std::ifstream f(this->filePath);
	std::string line;

	while (std::getline(f, line))
	{
		std::stringstream lineStream(line);
		std::string token;
		std::vector <std::string> tokens;

		while (std::getline(lineStream, token, this->separator))
			tokens.push_back(token);

		Tutorial tutorial(this->getNextId(), tokens[0], tokens[1], 
			std::stoi(tokens[2]), std::stoi(tokens[3]), tokens[4]);
		this->vector.push_back(tutorial);
	}

	f.close();
}

void TXTRepository::writeAll()
{
	std::ofstream f(this->filePath);

	for (Tutorial tutorial : this->vector)
	{
		std::string line = tutorial.getTitle() + this->separator + tutorial.getPresenter() + this->separator +
			std::to_string(tutorial.getDuration()) + this->separator + std::to_string(tutorial.getLikes()) + 
			this->separator + tutorial.getLink() + "\n";
		f << line;
	}

	f.close();
}

void TXTRepository::append(const Tutorial& tutorial)
{
	std::ofstream f(this->filePath, std::fstream::app);

	std::string line = tutorial.getTitle() + this->separator + tutorial.getPresenter() + this->separator +
		std::to_string(tutorial.getDuration()) + this->separator + std::to_string(tutorial.getLikes()) +
		this->separator + tutorial.getLink() + "\n";
	f << line;

	f.close();
}

void TXTRepository::add(const Tutorial& tutorial)
{
	Repository::add(tutorial);
	this->append(tutorial);
}

void TXTRepository::remove(const unsigned int id)
{
	Repository::remove(id);
	this->writeAll();
}

void TXTRepository::update(const unsigned int id, std::string title, std::string presenter, int duration, int likes, std::string link)
{
	Repository::update(id, title, presenter, duration, likes, link);
	this->writeAll();
}






CSVRepository::CSVRepository(std::string filePath) : filePath{ filePath }
{
	this->readAll();
}

void CSVRepository::readAll()
{
	std::ifstream f(this->filePath);
	std::string line;

	while (std::getline(f, line))
	{
		std::stringstream lineStream(line);
		std::string token;
		std::vector <std::string> tokens;

		while (std::getline(lineStream, token, this->separator))
			tokens.push_back(token);

		Tutorial tutorial(this->getNextId(), tokens[0], tokens[1],
			std::stoi(tokens[2]), std::stoi(tokens[3]), tokens[4]);
		this->vector.push_back(tutorial);
	}

	f.close();
}

void CSVRepository::writeAll()
{
	std::ofstream f(this->filePath);

	for (Tutorial tutorial : this->vector)
	{
		std::string line = tutorial.getTitle() + this->separator + tutorial.getPresenter() + this->separator +
			std::to_string(tutorial.getDuration()) + this->separator + std::to_string(tutorial.getLikes()) +
			this->separator + tutorial.getLink() + "\n";
		f << line;
	}

	f.close();
}

void CSVRepository::append(const Tutorial& tutorial)
{
	std::ofstream f(this->filePath, std::fstream::app);

	std::string line = tutorial.getTitle() + this->separator + tutorial.getPresenter() + this->separator +
		std::to_string(tutorial.getDuration()) + this->separator + std::to_string(tutorial.getLikes()) +
		this->separator + tutorial.getLink() + "\n";
	f << line;

	f.close();
}

void CSVRepository::add(const Tutorial& tutorial)
{
	Repository::add(tutorial);
	this->append(tutorial);
}

void CSVRepository::remove(const unsigned int id)
{
	Repository::remove(id);
	this->writeAll();
}

void CSVRepository::update(const unsigned int id, std::string title, std::string presenter, int duration, int likes, std::string link)
{
	Repository::update(id, title, presenter, duration, likes, link);
	this->writeAll();
}





HTMLRepository::HTMLRepository(std::string filePath) : filePath{ filePath }
{
	this->readAll();
}

void HTMLRepository::leftTrim(std::string& str)
{
	const std::string whiteSpace = " \n\r\t\f\v";
	int start = str.find_first_not_of(whiteSpace);
	str.erase(str.begin(), str.begin() + start);
	
}

void HTMLRepository::rightTrim(std::string& str)
{
	const std::string whiteSpace = " \n\r\t\f\v";
	int start = str.find_last_not_of(whiteSpace);
	str.erase(str.begin() + start + 1, str.end());
}

std::vector<std::string> HTMLRepository::htmlTagExtractor(std::string content, std::string tag)
{
	std::string endTag = "</" + tag + ">";
	tag = "<" + tag + ">";
	std::vector<std::string> tokens;

	while (true)
	{
		int pos = content.find(tag);
		if (pos >= content.size())
			break;

		content.erase(content.begin(), content.begin() + pos + tag.size());

		pos = content.find(endTag);
		if (pos >= content.size())
			break;

		tokens.push_back(content.substr(0, pos));
		content.erase(content.begin(), content.begin() + pos + endTag.size());
	}

	return tokens;
}

void HTMLRepository::readAll()
{
	std::ifstream f(this->filePath);
	std::string line;

	std::string content = "";
	while (std::getline(f, line))
	{
		this->leftTrim(line);
		this->rightTrim(line);
		content += line;
	}
	std::vector<std::string> tokens = this->htmlTagExtractor(content, "tr");

	for (auto token : tokens)
	{
		std::vector<std::string> values = this->htmlTagExtractor(token, "td");

		int first = values[4].find_first_of("\"");
		int last = values[4].find_last_of("\"");
		std::string link = values[4].substr(first + 1, last - first - 1);
		
		Tutorial tutorial(this->getNextId(), values[0], values[1],
			std::stoi(values[2]), std::stoi(values[3]), link);

		this->vector.push_back(tutorial);
	}

	f.close();
}

void HTMLRepository::writeAll()
{
	std::ofstream f(this->filePath);
	f << "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<title>Tutorials</title>\n</head>\n<body>\n<table border=\"1\">\n";
	for (Tutorial tutorial : this->vector)
	{
		std::string row;
		row += "<tr>\n";
		row += "<td>" + tutorial.getTitle() + "</td>\n";
		row += "<td>" + tutorial.getPresenter() + "</td>\n";
		row += "<td>" + std::to_string(tutorial.getDuration()) + "</td>\n";
		row += "<td>" + std::to_string(tutorial.getLikes()) + "</td>\n";
		row += "<td><a href=\"" + tutorial.getLink() + "\">Link</a></td>\n";
		row += "</tr>\n";
		f << row;
	}
	f << "</table>\n</body>\n</html>\n";
	f.close();
}

void HTMLRepository::add(const Tutorial& tutorial)
{
	Repository::add(tutorial);
	this->writeAll();
}

void HTMLRepository::remove(const unsigned int id)
{
	Repository::remove(id);
	this->writeAll();
}

void HTMLRepository::update(const unsigned int id, std::string title, std::string presenter, int duration, int likes, std::string link)
{
	Repository::update(id, title, presenter, duration, likes, link);
	this->writeAll();
}