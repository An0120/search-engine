#ifndef CRAWLER_WEBSITEREPOINMEM_HPP
#define CRAWLER_WEBSITEREPOINMEM_HPP

#include "WebsiteRepo.hpp"

class WebsiteRepoInMem : public WebsiteRepo {
private:
	std::vector<Website> websites;
public:
	std::vector<Website> getAll() override;
	void save(const Website& website) override;
};

#endif //CRAWLER_WEBSITEREPOINMEM_HPP