#include "userServices.h"

UserServices::UserServices(TutorialRepo& repo, TutorialRepo& watchList) : repo{ repo }, watchList{ watchList } {}

std::vector<Tutorial> UserServices::getTutorialsByPresenter(const std::string presenter)
{
	std::vector<Tutorial> tutorials = this->repo.getAll();
	
	if (presenter.empty())
		return tutorials;

	std::vector<Tutorial> wanted;
	for (int i = 0; i < tutorials.size(); i++)
	{
		Tutorial tutorial = tutorials[i];
		if (tutorial.getPresenter() == presenter)
			wanted.push_back(tutorial);
	}
	
	return wanted;
}

void UserServices::addToWatchList(const Tutorial& tutorial)
{
	this->watchList.add(tutorial);
}

void UserServices::deleteFromWatchList(const Tutorial& tutorial)
{
	this->watchList.remove(tutorial.getId());
}

void UserServices::likeTutorial(const Tutorial& tutorial)
{
	int newLikes = tutorial.getLikes() + 1;
	this->repo.update(tutorial.getId(), tutorial.getTitle(), tutorial.getPresenter(), tutorial.getDuration(), newLikes, tutorial.getLink());
}

int UserServices::getWatchListSize()
{
	return this->watchList.getSize();
}

std::vector<Tutorial> UserServices::getWatchList()
{
	return this->watchList.getAll();
}


