
#include "tests.h"
#include "repository.h"
#include "userServices.h"
#include "services.h"

#include <assert.h>


namespace UserServicesTests
{
	void testGetTutorialsByPresenter()
	{
		TutorialRepo repo;
		TutorialServices services(repo);

		services.add("title1", "presenter", 1, 1, "link1");
		services.add("title2", "presenter1", 1, 1, "link2");
		services.add("title3", "presenter", 1, 1, "link3");

		TutorialRepo watchList;
		UserServices userServices(repo, watchList);

		DynamicVector<Tutorial> vector = userServices.getTutorialsByPresenter("");
		assert(vector.getElement(0).getTitle() == "title1");
		assert(vector.getElement(1).getTitle() == "title2");
		assert(vector.getElement(2).getTitle() == "title3");

		vector = userServices.getTutorialsByPresenter("presenter");
		assert(vector.getElement(0).getTitle() == "title1");
		assert(vector.getElement(1).getTitle() == "title3");
	}

	void testAddToWatchList()
	{
		TutorialRepo repo;
		TutorialRepo watchList;
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
		TutorialRepo repo;
		TutorialRepo watchList;
		UserServices userServices(repo, watchList);

		Tutorial tutorial1(0, "title1", "presenter1", 1, 1, "link1");
		Tutorial tutorial2(1, "title2", "presenter2", 1, 1, "link2");
		Tutorial tutorial3(2, "title3", "presenter3", 1, 1, "link3");

		userServices.addToWatchList(tutorial1);
		userServices.addToWatchList(tutorial2);
		userServices.addToWatchList(tutorial3);

		assert(watchList.getSize() == 3);
		userServices.deleteFromWatchList(tutorial1);
		assert(watchList.getSize() == 2);
		userServices.deleteFromWatchList(tutorial2);
		assert(watchList.getSize() == 1);
		userServices.deleteFromWatchList(tutorial3);
		assert(watchList.getSize() == 0);
	}

	void testLikeTutorial()
	{
		TutorialRepo repo;

		Tutorial tutorial(0, "title", "presenter", 0, 0, "link");
		repo.add(tutorial);

		TutorialRepo watchList;
		UserServices userServices(repo, watchList);

		userServices.likeTutorial(tutorial);
		assert(repo.getElement(0).getLikes() == 1);
	}

	void testGetWatchList()
	{
		TutorialRepo repo;
		TutorialRepo watchList;
		UserServices userServices(repo, watchList);

		Tutorial tutorial1(0, "title1", "presenter1", 1, 1, "link1");
		Tutorial tutorial2(1, "title2", "presenter2", 1, 1, "link2");
		Tutorial tutorial3(2, "title3", "presenter3", 1, 1, "link3");

		userServices.addToWatchList(tutorial1);
		userServices.addToWatchList(tutorial2);
		userServices.addToWatchList(tutorial3);

		DynamicVector<Tutorial> vector = userServices.getWatchList();

		assert(vector.getElement(0).getTitle() == "title1");
		assert(vector.getElement(1).getTitle() == "title2");
		assert(vector.getElement(2).getTitle() == "title3");
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