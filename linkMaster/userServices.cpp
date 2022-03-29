#include "userServices.h"

UserServices::UserServices(TutorialRepo& repo, TutorialRepo& watchList) : repo{ repo }, watchList{ watchList } {}

DynamicVector<Tutorial> UserServices::getTutorialsByPresenter(const std::string presenter)
{
	DynamicVector<Tutorial> tutorials = this->repo.getAll();
	
	if (presenter.empty())
		return tutorials;

	DynamicVector<Tutorial> wanted;
	for (int i = 0; i < tutorials.getSize(); i++)
	{
		Tutorial tutorial = tutorials.getElement(i);
		if (tutorial.getPresenter() == presenter)
			wanted.add(tutorial);
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

DynamicVector<Tutorial> UserServices::getWatchList()
{
	return this->watchList.getAll();
}


