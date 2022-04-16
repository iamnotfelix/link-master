
#include "tests.h"
#include "repository.h"
#include "userServices.h"
#include "services.h"

#include <assert.h>


namespace UserServicesTests
{
	void testGetTutorialsByPresenter()
	{
		Repository repo;
		TutorialServices services(repo);

		services.add("title1", "presenter", 1, 1, "link1");
		services.add("title2", "presenter1", 1, 1, "link2");
		services.add("title3", "presenter", 1, 1, "link3");

		Repository watchList;
		UserServices userServices(repo, watchList);

		std::vector<Tutorial> vector = userServices.getTutorialsByPresenter("");
		assert(vector[0].getTitle() == "title1");
		assert(vector[1].getTitle() == "title2");
		assert(vector[2].getTitle() == "title3");

		vector = userServices.getTutorialsByPresenter("presenter");
		assert(vector[0].getTitle() == "title1");
		assert(vector[1].getTitle() == "title3");
	}

	void testAddToWatchList()
	{
		Repository repo;
		Repository watchList;
		UserServices userServices(repo, watchList);

		Tutorial tutorial1(0, "title1", "presenter1", 1, 1, "link1");
		Tutorial tutorial2(1, "title2", "presenter2", 1, 1, "link2");
		Tutorial tutorial3(2, "title3", "presenter3", 1, 1, "link3");

		userServices.addToWatchList(tutorial1);
		assert(watchList.getSize() == 1);
		userServices.addToWatchList(tutorial2);
		assert(watchList.getSize() == 2);
		userServices.addToWatchList(tutorial3);
		assert(watchList.getSize() == 3);
	}

	void testDeleteFromWatchList()
	{
		Repository repo;
		Repository watchList;
		UserServices userServices(repo, watchList);

		Tutorial tutorial1(0, "title1", "presenter1", 1, 1, "link1");
		Tutorial tutorial2(1, "title2", "presenter2", 1, 1, "link2");
		Tutorial tutorial3(2, "title3", "presenter3", 1, 1, "link3");

		userServices.addToWatchList(tutorial1);
		userServices.addToWatchList(tutorial2);
		userServices.addToWatchList(tutorial3);

		assert(userServices.getWatchListSize() == 3);
		userServices.deleteFromWatchList(tutorial1);
		assert(userServices.getWatchListSize() == 2);
		userServices.deleteFromWatchList(tutorial2);
		assert(userServices.getWatchListSize() == 1);
		userServices.deleteFromWatchList(tutorial3);
		assert(userServices.getWatchListSize() == 0);
	}

	void testLikeTutorial()
	{
		Repository repo;

		Tutorial tutorial(0, "title", "presenter", 0, 0, "link");
		repo.add(tutorial);

		Repository watchList;
		UserServices userServices(repo, watchList);

		userServices.likeTutorial(tutorial);
		assert(repo.getElement(0).getLikes() == 1);
	}

	void testGetWatchList()
	{
		Repository repo;
		Repository watchList;
		UserServices userServices(repo, watchList);

		Tutorial tutorial1(0, "title1", "presenter1", 1, 1, "link1");
		Tutorial tutorial2(1, "title2", "presenter2", 1, 1, "link2");
		Tutorial tutorial3(2, "title3", "presenter3", 1, 1, "link3");

		userServices.addToWatchList(tutorial1);
		userServices.addToWatchList(tutorial2);
		userServices.addToWatchList(tutorial3);

		std::vector<Tutorial> vector = userServices.getWatchList();

		assert(vector[0].getTitle() == "title1");
		assert(vector[1].getTitle() == "title2");
		assert(vector[2].getTitle() == "title3");
	}
}


void testUserServices()
{
	UserServicesTests::testGetTutorialsByPresenter();
	UserServicesTests::testAddToWatchList();
	UserServicesTests::testDeleteFromWatchList();
	UserServicesTests::testLikeTutorial();
	UserServicesTests::testGetWatchList();
}