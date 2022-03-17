#pragma once

#include <string>

class Tutorial
{
private:
	std::string title;
	std::string presenter;
	int duration;
	int likes;
	std::string link;
public:
	Tutorial(std::string title, std::string presenter, int duration, int likes, std::string link);
	
	inline std::string getTitle() const { return this->title; }
	inline std::string getPresenter() const { return this->presenter; }
	inline int getDuration() const { return this->duration; }
	inline int getLikes() const { return this->likes; }
	inline std::string getLink() const { return this->link; }

	inline void setTitle(const std::string newTitle) { this->title = newTitle; }
	inline void setPresenter(const std::string newPresenter) { this->presenter = newPresenter; }
	inline void setDuration(const int newDuration) { this->duration = newDuration; }
	inline void setLikes(const int newLikes) { this->likes = newLikes; }
	inline void setLink(const std::string newLink) { this->link = newLink; }
};
