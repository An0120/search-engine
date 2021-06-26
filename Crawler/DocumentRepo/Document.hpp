#ifndef CRAWLER_DOCUMENT_HPP
#define CRAWLER_DOCUMENT_HPP
#include <ctime>
#include <string>

class Document {
private:
	int id;
	std::string url;
	std::string title;
	std::string description;
	std::string content;
	time_t updated;

public:
	Document(int id, std::string url, std::string title, std::string description, std::string content, time_t updated)
			: id{ id }, url{ std::move(url) },
			  title{ std::move(title) },
			  description{ std::move(description) },
			  content{ std::move(content) }, updated{ updated }
	{
	}

	bool operator ==(const Document& other) const
	{
		return this->id == other.id;
	}

	[[nodiscard]] inline int getId() const
	{
		return this->id;
	}

	[[nodiscard]] inline const std::string& getUrl() const
	{
		return this->url;
	}

	[[nodiscard]] inline const std::string& getTitle() const
	{
		return this->title;
	}

	[[nodiscard]] inline const std::string& getDescription() const
	{
		return this->description;
	}

	[[nodiscard]] inline const std::string& getContent() const
	{
		return this->content;
	}

	[[nodiscard]] inline time_t getUpdatedTime() const
	{
		return this->updated;
	}
};

#endif //CRAWLER_DOCUMENT_HPP