
#include "validation.h"
#include "exception.h"


void Validation::validateNumber(const int number)
{
	if (number < 0)
		throw ValidationException("Enter a positive value!\n");
	return;
}
