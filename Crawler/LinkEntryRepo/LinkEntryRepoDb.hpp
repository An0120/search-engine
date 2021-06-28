#ifndef CRAWLER_LINKENTRYREPODB_HPP
#define CRAWLER_LINKENTRYREPODB_HPP

#include "mysql++/mysql++.h"
#include "LinkEntryRepo.hpp"

class LinkEntryRepoDb : public LinkEntryRepo {
private:
	mysqlpp::Connection connection;

public:
	LinkEntryRepoDb(
			const std::string& dbName, const std::string& serverName,
			const std::string& username, const std::string& password, unsigned int port);
	~LinkEntryRepoDb() noexcept override;
	std::vector<LinkEntry> getAll() override;
	std::optional<LinkEntry> getByUrl(const std::string& url) override;
	std::vector<LinkEntry> getBy(int websiteId, LinkStatus status, int count) override;
	void save(const LinkEntry& link) override;

private:
	static std::unique_ptr<LinkEntry> getLinkFromDbRow(const mysqlpp::Row& row);
};

#endif 