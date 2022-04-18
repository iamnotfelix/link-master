
#include "exception.h"


std::string RepositoryException::what() const
{
	return this->message;
}

std::string ValidationException::what() const
{
	return this->message;
}

std::string ServicesException::what() const
{
	return this->message;
}

std::string UIException::what() const
{
	return this->message;
}
