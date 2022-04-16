
#include "tests.h"
#include "services.h"

#include <assert.h>

namespace ServicesTests
{

	void testInitRepo()
	{
		Repository repo;
		TutorialServices services(repo);

		services.initRepo();
		assert(repo.getSize() == 10);
	}

	void testGetAll()
	{
		Repository repo;
		TutorialServices services(repo);

		services.add("title1", "presenter1", 1, 1, "link1");
		services.add("title2", "presenter2", 2, 2, "link2");
		services.add("title3", "presenter3", 3, 3, "link3");

		std::vector<Tutorial> data = services.getAll();
		assert(data.size() == 3);
	}

	void testAdd()
	{
		Repository repo;
		TutorialServices services(repo);

		services.add("title1", "presenter1", 1, 1, "link1");
		services.add("title2", "presenter2", 2, 2, "link2");
		services.add("title3", "presenter3", 3, 3, "link3");

		assert(services.getSize() == 3);
		assert(repo.getSize() == 3);
	}

	void testRemove()
	{
		Repository repo;
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
	}
	
	void testUpdate()
	{
		Repository repo;
		TutorialServices services(repo);

		services.add("title1", "presenter1", 1, 1, "link1");
		services.add("title2", "presenter2", 2, 2, "link2");
		services.add("title3", "presenter3", 3, 3, "link3");

		services.update(0, "title4", "presenter4", 4, 4, "link4");
		assert(services.getAll()[0].getTitle() == "title4");
	}
}

void testServices()
{
	ServicesTests::testInitRepo();
	ServicesTests::testGetAll();
	ServicesTests::testAdd();
	ServicesTests::testRemove();
	ServicesTests::testUpdate();
}