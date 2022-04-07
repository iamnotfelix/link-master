
#include "tests.h"
#include "repository.h"
#include "tutorial.h"

#include <assert.h>
#include <exception>


namespace RepositoryTests
{
	void testConstructor()
	{
		TutorialRepo repo{ "testFile.txt" };
		assert(repo.getSize() == 10);
		assert(repo.getElement(0).getTitle() == "Title 1");
		assert(repo.getElement(3).getTitle() == "Title 4");
		assert(repo.getElement(3).getLink() == "Link 4");
		assert(repo.getElement(9).getLink() == "https://en.cppreference.com/w/");
	}

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

		std::vector<Tutorial> data = repo.getAll();
		for (int i = 0; i < data.size(); i++)
		{
			assert(data[i] == repo.getElement(i));
		}
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
	}

	void testUpdate()
	{
		TutorialRepo repo;

		Tutorial tutorial1(repo.getNextId(), "title1", "presenter1", 1, 2, "link1");
		
		try
		{
			repo.update(0, "title", "presenter", 1, 2, "link");
			assert(false);
		}
		catch (const std::exception& e)
		{
			assert(strcmp(e.what(), "Tutorial not found!\n") == 0);
		}

		repo.add(tutorial1);

		repo.update(0, "title4", "presenter4", 1, 2, "link4");
		assert(repo.getElement(0).getTitle() == "title4");

		repo.update(0, "title5", "presenter5", 1, 2, "link5");
		assert(repo.getElement(0).getPresenter() == "presenter5");
	}
}

void testRepository()
{
	RepositoryTests::testConstructor();
	RepositoryTests::testFind();
	RepositoryTests::testGetElement();
	RepositoryTests::testGetAll();
	RepositoryTests::testAdd();
	RepositoryTests::testRemove();
	RepositoryTests::testUpdate();
}
