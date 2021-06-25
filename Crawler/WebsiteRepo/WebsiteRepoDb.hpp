#ifndef CRAWLER_WEBSITEREPODB_HPP
#define CRAWLER_WEBSITEREPODB_HPP

#include "mysql++/mysql++.h"
#include "WebsiteRepo.hpp"

class WebsiteRepoDb : public WebsiteRepo {
private:
	mysqlpp::Connection connection;

public:
	WebsiteRepoDb(
			const std::string& dbName, const std::string& serverName,
			const std::string& username, const std::string& password, unsigned int port);
	~WebsiteRepoDb() noexcept override;
	std::vector<Website> getAll() override;
	void save(const Website& website) override;

private:
	static std::unique_ptr<Website> getSiteFromDbRow(const mysqlpp::Row& row);
};

#endif //CRAWLER_WEBSITEREPODB_HPP