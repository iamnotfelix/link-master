
#include "tests.h"
#include "tutorial.h"

#include <iostream>
#include <assert.h>

namespace TutorialTests
{

	void testGetters()
	{
		Tutorial tutorial1{ "title1", "presenter1", 12, 100, "link1" };

		assert(tutorial1.getId() == 0);
		assert(tutorial1.getTitle() == "title1");
		assert(tutorial1.getPresenter() == "presenter1");
		assert(tutorial1.getDuration() == 12);
		assert(tutorial1.getLikes() == 100);
		assert(tutorial1.getLink() == "link1");

		Tutorial tutorial2{ "title2", "presenter2", 12, 100, "link2" };

		assert(tutorial2.getId() == 1);

		std::cout << "Getters tests: success\n";
	}
}

void testTutorial()
{
	std::cout << "Tutorial tests:\n"; 
	TutorialTests::testGetters();
	std::cout << std::endl;
}