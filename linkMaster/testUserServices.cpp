
#include "tests.h"
#include "repository.h"
#include "userServices.h"
#include "services.h"

#include <assert.h>
#include <fstream>


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

	void testGetWatchListPath()
	{
		std::ofstream f("testFile.txt");
		f << "";
		f.close();

		Repository repo1;
		Repository watchList1;
		UserServices userServices1(repo1, watchList1);
		try
		{
			userServices1.getWatchListFilePath();
			assert(false);
		}
		catch (const std::exception& e)
		{
			assert(e.what() == std::string("Cannot open app when using in-memory repository!\n"));
		}

		TXTRepository repo2("testFile.txt");
		TXTRepository watchList2("testFile.txt");
		UserServices userServices2(repo2, watchList2);
		assert(userServices2.getWatchListFilePath() == "testFile.txt");

		CSVRepository repo3("testFile.txt");
		CSVRepository watchList3("testFile.txt");
		UserServices userServices3(repo3, watchList3);
		assert(userServices3.getWatchListFilePath() == "testFile.txt");

		HTMLRepository repo4("testFile.txt");
		HTMLRepository watchList4("testFile.txt");
		UserServices userServices4(repo4, watchList4);
		assert(userServices4.getWatchListFilePath() == "testFile.txt");
	}
}


void testUserServices()
{
	UserServicesTests::testGetTutorialsByPresenter();
	UserServicesTests::testAddToWatchList();
	UserServicesTests::testDeleteFromWatchList();
	UserServicesTests::testLikeTutorial();
	UserServicesTests::testGetWatchList();
	UserServicesTests::testGetWatchListPath();
}