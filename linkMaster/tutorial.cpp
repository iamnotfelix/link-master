
#include "tutorial.h"

#include <sstream>
#include <vector>


Tutorial::Tutorial(unsigned int id, std::string title, std::string presenter, int duration, int likes, std::string link) :
	id{ id }, title{ title }, presenter{ presenter }, duration{ duration }, likes{ likes }, link{ link } {}

bool Tutorial::operator==(const Tutorial& tutorial)
{
	if (this->id == tutorial.getId())
		return true;

	if (this->link == tutorial.getLink())
		return true;

	return false;
}

std::ostream& operator<<(std::ostream& os, Tutorial& tutorial)
{
	int minutes = tutorial.getDuration() / 60;
	int seconds = tutorial.getDuration() % 60;
	std::string time = std::to_string(minutes) + ":" + std::to_string(seconds);

	os.width(5); os << std::left << tutorial.getId();
	os.width(20); os << std::right << tutorial.getTitle();
	os.width(20); os << std::right << tutorial.getPresenter();
	os.width(10); os << std::right << time;
	os.width(10); os << std::right << tutorial.getLikes();
	os.width(35); os << std::right << tutorial.getLink();
	os << std::endl;

	return os;
}

//std::istream& operator>>(std::istream& is, Tutorial& tutorial)
//{
//	std::string token;
//	std::vector <std::string> tokens;
//
//	while (std::getline(is, token, '|'))
//		tokens.push_back(token);
//
//	Tutorial tut(0, tokens[0], tokens[1],
//		std::stoi(tokens[2]), std::stoi(tokens[3]), tokens[4]);
//
//	return is;
//}
