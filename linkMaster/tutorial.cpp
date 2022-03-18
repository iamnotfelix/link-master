
#include "tutorial.h"


unsigned int Tutorial::idCount = 0;

Tutorial::Tutorial(std::string title, std::string presenter, int duration, int likes, std::string link) :
	id{ this->idCount++ }, title{ title }, presenter{ presenter }, duration{ duration }, likes{ likes }, link{ link } { }
