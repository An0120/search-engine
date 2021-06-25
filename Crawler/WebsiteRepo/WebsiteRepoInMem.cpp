#include "WebsiteRepoInMem.hpp"

std::vector<Website> WebsiteRepoInMem::getAll()
{
	return this->websites;
}

void WebsiteRepoInMem::save(const Website& website)
{
	for (auto& current : this->websites) {
		if (current == website) {
			current = website;
			return;
		}
	}
	this->websites.emplace_back(website);
}