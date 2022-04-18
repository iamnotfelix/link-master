#pragma once

#include <exception>
#include <string>


class Exception
{
protected:
	std::string message;
public:
	Exception(std::string msg = "") :message{ msg } {};
	virtual std::string what() const = 0;
};

class RepositoryException :public Exception
{
public:
	RepositoryException(std::string msg = "") : Exception{ msg } {};
	std::string what() const;
};

class ValidationException :public Exception
{
public:
	ValidationException(std::string msg = "") : Exception{ msg } {};
	std::string what() const;
};

class ServicesException :public Exception
{
public:
	ServicesException(std::string msg = "") : Exception{ msg } {};
	std::string what() const;
};

class UIException :public Exception
{
public:
	UIException(std::string msg = "") : Exception{ msg } {};
	std::string what() const;
};
