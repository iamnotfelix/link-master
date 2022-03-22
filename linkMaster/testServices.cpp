
#include "tests.h"
#include "services.h"

#include <iostream>
#include <assert.h>

namespace ServicesTests
{

	void testInitRepo()
	{
		TutorialRepo repo;
		TutorialServices services(repo);

		services.initRepo();
		assert(repo.getSize() == 10);

		std::cout << "\tInit repo tests\n";
	}

	void testGetAll()
	{
		TutorialRepo repo;
		TutorialServices services(repo);

		services.add("title1", "presenter1", 1, 1, "link1");
		services.add("title2", "presenter2", 2, 2, "link2");
		services.add("title3", "presenter3", 3, 3, "link3");

		DynamicVector<Tutorial> data = services.getAll();
		assert(data.getSize() == 3);

		std::cout << "\tGet all tests\n";
	}

	void testAdd()
	{
		TutorialRepo repo;
		TutorialServices services(repo);

		services.add("title1", "presenter1", 1, 1, "link1");
		services.add("title2", "presenter2", 2, 2, "link2");
		services.add("title3", "presenter3", 3, 3, "link3");

		assert(services.getSize() == 3);
		assert(repo.getSize() == 3);

		std::cout << "\tAdd tests\n";
	}

	void testRemove()
	{
		TutorialRepo repo;
		TutorialServices services(repo);

		services.add("title1", "presenter1", 1, 1, "link1");
		services.add("title2", "presenter2", 2, 2, "link2");
		services.add("title3", "presenter3", 3, 3, "link3");

		services.remove(0);
		assert(services.getSize() == repo.getSize());
		services.remove(1);
		assert(services.getSize() == repo.getSize());
		services.remove(2);
		assert(services.getSize() == repo.getSize());

		std::cout << "\tAdd tests\n";
		std::cout << "\tRemove tests\n";
	}
	
	void testUpdate()
	{
		TutorialRepo repo;
		TutorialServices services(repo);

		services.add("title1", "presenter1", 1, 1, "link1");
		services.add("title2", "presenter2", 2, 2, "link2");
		services.add("title3", "presenter3", 3, 3, "link3");

		services.update(0, "title4", "presenter4", 4, 4, "link4");
		assert(services.getAll()[0].getTitle() == "title4");
		

		std::cout << "\tUpdate tests\n";
	}
}

void testServices()
{
	std::cout << "Services tests:\n";
	ServicesTests::testInitRepo();
	ServicesTests::testGetAll();
	ServicesTests::testAdd();
	ServicesTests::testRemove();
	ServicesTests::testUpdate();
	std::cout << std::endl;
}