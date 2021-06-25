#ifndef CRAWLER_WEBSITE_HPP
#define CRAWLER_WEBSITE_HPP

#include <ctime>
#include <string>

class Website {
private:
	int id;
	std::string domain;
	std::string homepage;
	time_t crawled;

public:
	Website(int id, std::string domain, std::string homepage, time_t crawled)
			: id{ id }, domain{ std::move(domain) },
			  homepage{ std::move(homepage) },
			  crawled{ crawled }
	{
	}

	bool operator ==(const Website& other) const
	{
		return this->id == other.id;
	}

	[[nodiscard]] inline int getId() const
	{
		return this->id;
	}

	[[nodiscard]] inline const std::string& getDomain() const
	{
		return this->domain;
	}

	[[nodiscard]] inline const std::string& getHomepage() const
	{
		return this->homepage;
	}

	[[nodiscard]] inline time_t getCrawledTime() const
	{
		return this->crawled;
	}
};

#endif //CRAWLER_WEBSITE_HPP