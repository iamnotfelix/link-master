
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

		Tutorial tutorial1("title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2("title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3("title3", "presenter3", 1, 2, "link3");
		Tutorial tutorial4("title4", "presenter4", 1, 2, "link1");

		repo.add(tutorial1);
		repo.add(tutorial2);

		assert(repo.find(tutorial3) == false);
		assert(repo.find(tutorial2) == true);
		assert(repo.find(tutorial1) == true);
		assert(repo.find(tutorial4) == true);

		std::cout << "Find tests: success\n";
	}

	void testGetElement()
	{
		TutorialRepo repo;

		Tutorial tutorial1("title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2("title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3("title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		repo.add(tutorial2);

		assert(repo.getElement(tutorial1.getId()) == tutorial1);
		assert(repo.getElement(tutorial2.getId()) == tutorial2);

		try
		{
			repo.getElement(tutorial3.getId());
			assert(false);
		}
		catch (const std::exception& e)
		{
			assert(strcmp(e.what(), "Tutorial not found!\n") == 0);
		}

		std::cout << "Get element test: success\n";
	}
	
	void testGetAll()
	{
		TutorialRepo repo;

		Tutorial tutorial1("title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2("title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3("title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		repo.add(tutorial2);
		repo.add(tutorial3);

		DynamicVector<Tutorial> data = repo.getAll();
		for (int i = 0; i < data.getSize(); i++)
		{
			assert(data.getElement(i) == repo.getElement(data.getElement(i).getId()));
		}

		std::cout << "Get all tests: success\n";
	}

	void testAdd()
	{
		TutorialRepo repo;

		Tutorial tutorial1("title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2("title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3("title3", "presenter3", 1, 2, "link3");

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

		std::cout << "Add tests: success\n";
	}
	
	void testRemove()
	{
		TutorialRepo repo;

		Tutorial tutorial1("title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2("title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3("title3", "presenter3", 1, 2, "link3");

		repo.add(tutorial1);
		repo.add(tutorial2);

		assert(repo.getSize() == 2);
		repo.remove(tutorial1.getId());
		assert(repo.getSize() == 1);
		repo.remove(tutorial2.getId());
		assert(repo.getSize() == 0);

		try
		{
			repo.remove(tutorial3.getId());
			assert(false);
		}
		catch (const std::exception& e)
		{
			assert(strcmp(e.what(), "Tutorial not found!\n") == 0);
		}

		std::cout << "Remove tests: success\n";
	}

	void testUpdate()
	{
		TutorialRepo repo;

		Tutorial tutorial1("title1", "presenter1", 1, 2, "link1");
		Tutorial tutorial2("title2", "presenter2", 1, 2, "link2");
		Tutorial tutorial3("title3", "presenter3", 1, 2, "link3");
		
		try
		{
			repo.update(tutorial1.getId(), tutorial2);
			assert(false);
		}
		catch (const std::exception& e)
		{
			assert(strcmp(e.what(), "Tutorial not found!\n") == 0);
		}

		repo.add(tutorial1);

		repo.update(tutorial1.getId(), tutorial2);
		assert(repo.find(tutorial2) == true);

		repo.update(tutorial2.getId(), tutorial3);
		assert(repo.find(tutorial3) == true);

		std::cout << "Update tests: success\n";
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
