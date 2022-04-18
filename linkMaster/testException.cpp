
#include "tests.h"
#include "exception.h"
#include "validation.h"

#include <assert.h>


void testException()
{
	RepositoryException re("repositoryException");
	ValidationException ve("validationException");
	ServicesException se("servicesException");
	UIException ue("uiException");

	try
	{
		throw re;
		assert(false);
	}
	catch (const Exception& e)
	{
		assert(e.what() == "repositoryException");
	}

	try
	{
		throw ve;
		assert(false);
	}
	catch (const Exception& e)
	{
		assert(e.what() == "validationException");
	}

	try
	{
		throw se;
		assert(false);
	}
	catch (const Exception& e)
	{
		assert(e.what() == "servicesException");
	}

	try
	{
		throw ue;
		assert(false);
	}
	catch (const Exception& e)
	{
		assert(e.what() == "uiException");
	}

	try
	{
		Validation v;
		v.validateNumber(0);
		v.validateNumber(-1);
		assert(false);
	}
	catch (const Exception& e)
	{
		assert(e.what() == "Enter a positive value!\n");
	}
}