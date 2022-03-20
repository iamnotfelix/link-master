
#include "tutorial.h"


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
