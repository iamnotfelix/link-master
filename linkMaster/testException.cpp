
#include "tests.h"
#include "exception.h"

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
	}
	catch (const Exception& e)
	{
		assert(e.what() == "repositoryException");
	}

	try
	{
		throw ve;
	}
	catch (const Exception& e)
	{
		assert(e.what() == "validationException");
	}

	try
	{
		throw se;
	}
	catch (const Exception& e)
	{
		assert(e.what() == "servicesException");
	}

	try
	{
		throw ue;
	}
	catch (const Exception& e)
	{
		assert(e.what() == "uiException");
	}
}