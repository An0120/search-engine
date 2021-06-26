#ifndef CRAWLER_DOCUMENTREPODB_HPP
#define CRAWLER_DOCUMENTREPODB_HPP

#include "mysql++/mysql++.h"
#include "DocumentRepo.hpp"

class DocumentRepoDb : public DocumentRepo {
private:
	mysqlpp::Connection connection;

public:
	DocumentRepoDb(
			const std::string& dbName, const std::string& serverName,
			const std::string& username, const std::string& password, unsigned int port);
	~DocumentRepoDb() noexcept override;
	std::optional<Document> getByUrl(const std::string& url) override;
	void save(const Document& document) override;

private:
	static std::unique_ptr<Document> getDocumentFromDbRow(const mysqlpp::Row& row);
};

#endif //CRAWLER_DOCUMENTREPODB_HPP