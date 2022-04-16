
#include "userServices.h"

#include<algorithm>


UserServices::UserServices(Repository& repo, Repository& watchList) : repo{ repo }, watchList{ watchList } {}

std::vector<Tutorial> UserServices::getTutorialsByPresenter(const std::string presenter)
{
	std::vector<Tutorial> tutorials = this->repo.getAll();
	if (presenter.empty())
		return tutorials;

	std::vector<Tutorial> wanted(tutorials.size());

	auto lambda = [presenter](Tutorial tutorial) { return (tutorial.getPresenter() == presenter); };
	auto it = std::copy_if(tutorials.begin(), tutorials.end(), wanted.begin(), lambda);
	wanted.resize(std::distance(wanted.begin(), it));
	
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


