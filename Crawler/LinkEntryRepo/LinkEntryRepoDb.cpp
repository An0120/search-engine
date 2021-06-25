#include "LinkEntryRepoDb.hpp"

LinkEntryRepoDb::LinkEntryRepoDb(const std::string& dbName, const std::string& serverName,
		const std::string& username, const std::string& password, unsigned int port)
		: connection(true)
{
	this->connection.connect(dbName.c_str(), serverName.c_str(), username.c_str(), password.c_str(), port);
}

LinkEntryRepoDb::~LinkEntryRepoDb() noexcept
{
	if (this->connection.connected()) {
		this->connection.disconnect();
	}
}

std::vector<LinkEntry> LinkEntryRepoDb::getAll()
{
	mysqlpp::Query query(&this->connection);
	auto result = query.use("SELECT * FROM links");
	std::vector<LinkEntry> links{};
	while (mysqlpp::Row row = result.fetch_row()) {
		links.emplace_back(*LinkEntryRepoDb::getLinkFromDbRow(row));
	}
	return links;
}

std::optional<LinkEntry> LinkEntryRepoDb::getByUrl(const std::string& url)
{
	mysqlpp::Query query(&this->connection);
	auto result = query.use("SELECT * FROM links WHERE url = '" + url + "'");
	mysqlpp::Row row = result.fetch_row();
	if (!row.empty()) {
		return std::optional<LinkEntry>(*LinkEntryRepoDb::getLinkFromDbRow(row));
	}
	return std::optional<LinkEntry>(std::nullopt);
}

std::vector<LinkEntry> LinkEntryRepoDb::getBy(int websiteId, LinkStatus status, int count)
{
	std::string sqlCmd("SELECT * FROM links WHERE websiteId = " + std::to_string(websiteId)
			+ " AND status = " + std::to_string(int(status))
			+ " ORDER BY updated DESC");
	mysqlpp::Query query(&this->connection);
	auto result = query.use(sqlCmd);

	std::vector<LinkEntry> links{};
	while (mysqlpp::Row row = result.fetch_row()) {
		if (count == 0) {
			break;
		}
		--count;
		links.emplace_back(*LinkEntryRepoDb::getLinkFromDbRow(row));
	}
	return links;
}

void LinkEntryRepoDb::save(const LinkEntry& link)
{
	mysqlpp::Query query(&this->connection);
	std::string url{};
	query.escape_string(&url, link.getUrl().c_str());
	query << "INSERT INTO links(websiteId, url, status) " << "VALUES ('"
		  << link.getWebsiteId() << "', '" << url << "', '" << int(link.getStatus())
		  << "') ON DUPLICATE KEY UPDATE status='" << int(link.getStatus()) << "', updated=DEFAULT;";
	if (!query.exec()) {
		std::cerr << "can't store link: " << link.getUrl() << std::endl;
		std::cerr << query.error() << std::endl;
	}
}

std::unique_ptr<LinkEntry> LinkEntryRepoDb::getLinkFromDbRow(const mysqlpp::Row& row)
{
	tm timeStruct{};
	strptime(row["updated"].c_str(), "%Y-%m-%d %H:%M:%S", &timeStruct);

	return std::make_unique<LinkEntry>(row["id"], row["websiteId"],
			std::string(row["url"].data()), LinkStatus(int(row["status"])),
			time_t(std::mktime(&timeStruct)));
}