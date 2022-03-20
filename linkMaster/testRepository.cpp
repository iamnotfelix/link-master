
#include "tests.h"
#include "repository.h"
#include "tutorial.h"

#include <assert.h>
#include <iostream>
#include <exception>


namespace RepositoryTests
{
	void testFind()
	{
		TutorialRepo repo;

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");
		Tutorial tutorial4(repo.getNextId(), "title4", "presenter4", 1, 2, "link1");

		repo.add(tutorial1);
		repo.add(tutorial2);

		assert(repo.find(tutorial3) == false);
		assert(repo.find(tutorial2) == true);
		assert(repo.find(tutorial1) == true);
		assert(repo.find(tutorial4) == true);

		std::cout << "\tFind tests\n";
	}

	void testGetElement()
	{
		TutorialRepo repo;

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		repo.add(tutorial2);

		assert(repo.getElement(0) == tutorial1);
		assert(repo.getElement(1) == tutorial2);

		try
		{
			repo.getElement(2);
			assert(false);
		}
		catch (const std::exception& e)
		{
			assert(strcmp(e.what(), "Tutorial not found!\n") == 0);
		}

		std::cout << "\tGet element test\n";
	}
	
	void testGetAll()
	{
		TutorialRepo repo;

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		repo.add(tutorial2);
		repo.add(tutorial3);

		DynamicVector<Tutorial> data = repo.getAll();
		for (int i = 0; i < data.getSize(); i++)
		{
			assert(data.getElement(i) == repo.getElement(i));
		}

		std::cout << "\tGet all tests\n";
	}

	void testAdd()
	{
		TutorialRepo repo;

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		assert(repo.getSize() == 1);

		repo.add(tutorial2);
		assert(repo.getSize() == 2);

		repo.add(tutorial3);
		assert(repo.getSize() == 3);

		try
		{
			repo.add(tutorial1);
			assert(false);
		}
		catch (const std::exception& e)
		{
			assert(strcmp(e.what(), "Tutorial already exists!\n") == 0);
		}

		std::cout << "\tAdd tests\n";
	}
	
	void testRemove()
	{
		TutorialRepo repo;

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		repo.add(tutorial2);

		assert(repo.getSize() == 2);
		repo.remove(0);
		assert(repo.getSize() == 1);
		repo.remove(1);
		assert(repo.getSize() == 0);

		try
		{
			repo.remove(2);
			assert(false);
		}
		catch (const std::exception& e)
		{
			assert(strcmp(e.what(), "Tutorial not found!\n") == 0);
		}

		std::cout << "\tRemove tests\n";
	}

	void testUpdate()
	{
		TutorialRepo repo;

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2(repo.getNextId(), "title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3(repo.getNextId(), "title3", "presenter3", 1, 2, "link3");
		
		try
		{
			repo.update(0, tutorial2);
			assert(false);
		}
		catch (const std::exception& e)
		{
			assert(strcmp(e.what(), "Tutorial not found!\n") == 0);
		}

		repo.add(tutorial1);

		repo.update(0, tutorial2);
		assert(repo.find(tutorial2) == true);

		repo.update(1, tutorial3);
		assert(repo.find(tutorial3) == true);

		std::cout << "\tUpdate tests\n";
	}
}

void testRepository()
{
	std::cout << "Repository tests:\n";
	RepositoryTests::testFind();
	RepositoryTests::testGetElement();
	RepositoryTests::testGetAll();
	RepositoryTests::testAdd();
	RepositoryTests::testRemove();
	RepositoryTests::testUpdate();
	std::cout << std::endl;
}
