#ifndef CRAWLER_LINKENTRYREPOINMEM_HPP
#define CRAWLER_LINKENTRYREPOINMEM_HPP

#include <algorithm>
#include "LinkEntryRepo.hpp"

class LinkEntryRepoInMem : public LinkEntryRepo {
private:
	std::vector<LinkEntry> links;

public:
	std::vector<LinkEntry> getAll() override;
	std::optional<LinkEntry> getByUrl(const std::string& url) override;
	std::vector<LinkEntry> getBy(int websiteId, LinkStatus status, int count) override;
	void save(const LinkEntry& link) override;
};

#endif //CRAWLER_LINKENTRYREPOINMEM_HPP