#include "LinkEntryRepoInMem.hpp"

std::vector<LinkEntry> LinkEntryRepoInMem::getAll()
{
	return this->links;
}

std::optional<LinkEntry> LinkEntryRepoInMem::getByUrl(const std::string& url)
{
	for (const auto& link : this->links) {
		if (link.getUrl() == url) {
			return std::optional<LinkEntry>(link);
		}
	}
	return std::optional<LinkEntry>(std::nullopt);
}

std::vector<LinkEntry> LinkEntryRepoInMem::getBy(int websiteId, LinkStatus status, int count)
{
	std::vector<LinkEntry> validLinks;
	for (const auto& link : this->links) {
		if (link.getStatus() == status && link.getWebsiteId() == websiteId) {
			validLinks.emplace_back(link);
		}
	}
	std::sort(validLinks.begin(), validLinks.end(),
			[](const LinkEntry& link1, const LinkEntry& link2) -> bool {
				return link1.getUpdatedTime() < link2.getUpdatedTime();
			});
	if (count < validLinks.size()) {
		validLinks.erase(validLinks.begin() + count, validLinks.end());
	}
	return validLinks;
}

void LinkEntryRepoInMem::save(const LinkEntry& link)
{
	for (auto& current : this->links) {
		if (current == link) {
			current = link;
			return;
		}
	}
	this->links.emplace_back(link);
}