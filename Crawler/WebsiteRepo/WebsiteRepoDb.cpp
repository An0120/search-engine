#include "WebsiteRepoDb.hpp"

WebsiteRepoDb::WebsiteRepoDb(const std::string& dbName, const std::string& serverName,
		const std::string& username, const std::string& password, unsigned int port)
		: connection(true)
{
	this->connection.connect(dbName.c_str(), serverName.c_str(), username.c_str(), password.c_str(), port);
}

WebsiteRepoDb::~WebsiteRepoDb() noexcept
{
	if (this->connection.connected()) {
		this->connection.disconnect();
	}
}

std::vector<Website> WebsiteRepoDb::getAll()
{
	mysqlpp::Query query(&this->connection);
	auto result = query.use("SELECT * FROM websites");
	std::vector<Website> websites{};
	while (mysqlpp::Row row = result.fetch_row()) {
		websites.emplace_back(*WebsiteRepoDb::getSiteFromDbRow(row));
	}
	return websites;
}

void WebsiteRepoDb::save(const Website& website)
{
	std::string domain{};
	std::string homepage{};

	mysqlpp::Query query(&this->connection);
	query.escape_string(&domain, website.getDomain().c_str());
	query.escape_string(&homepage, website.getHomepage().c_str());

	query << "INSERT INTO websites(domain, homepage) "
		  << "VALUES ( '" << domain << "', '" << homepage << "' )"
		  << "ON DUPLICATE KEY UPDATE homepage='" << homepage << "', "
		  << "crawled=default;";
	if (!query.exec()) {
		std::cerr << "can't store website, domain is: " << website.getDomain() << std::endl;
		std::cerr << query.error() << std::endl;
	}
}

std::unique_ptr<Website> WebsiteRepoDb::getSiteFromDbRow(const mysqlpp::Row& row)
{
	tm timeStruct{};
	strptime(row["crawled"].c_str(), "%Y-%m-%d %H:%M:%S", &timeStruct);

	return std::make_unique<Website>(row["id"],
			std::string(row["domain"].data()),
			std::string(row["homepage"].data()),
			time_t(std::mktime(&timeStruct)));
}