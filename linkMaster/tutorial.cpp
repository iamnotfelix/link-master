
#include "tutorial.h"


unsigned int Tutorial::idCount = 0;

Tutorial::Tutorial(std::string title, std::string presenter, int duration, int likes, std::string link) :
	id{ this->idCount }, title{ title }, presenter{ presenter }, duration{ duration }, likes{ likes }, link{ link } 
{ 
	this->idCount++;
}

bool Tutorial::operator==(const Tutorial& tutorial)
{
	if (this->id == tutorial.getId())
		return true;

	if (this->link == tutorial.getLink())
		return true;

	return false;
}
