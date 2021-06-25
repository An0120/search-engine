#ifndef CRAWLER_WEBSITEREPO_HPP
#define CRAWLER_WEBSITEREPO_HPP

#include <vector>
#include "Website.hpp"

class WebsiteRepo {
public:
	virtual ~WebsiteRepo() = default;
	virtual std::vector<Website> getAll() = 0;
	virtual void save(const Website& website) = 0;
};

#endif //CRAWLER_WEBSITEREPO_HPP