#include "DocumentRepoDb.hpp"

DocumentRepoDb::DocumentRepoDb(const std::string& dbName, const std::string& serverName,
		const std::string& username, const std::string& password, unsigned int port)
		: connection(true)
{
	this->connection.connect(dbName.c_str(), serverName.c_str(), username.c_str(), password.c_str(), port);
}

DocumentRepoDb::~DocumentRepoDb() noexcept
{
	if (this->connection.connected()) {
		this->connection.disconnect();
	}
}

std::optional<Document> DocumentRepoDb::getByUrl(const std::string& url)
{
	mysqlpp::Query query(&this->connection);
	std::string pureUrl{};
	query.escape_string(&pureUrl, url.c_str());
	auto result = query.use("SELECT * FROM links WHERE url = '" + pureUrl + "'");
	mysqlpp::Row row = result.fetch_row();
	if (!row.empty()) {
		return std::optional<Document>(*DocumentRepoDb::getDocumentFromDbRow(row));
	}
	return std::optional<Document>(std::nullopt);
}

void DocumentRepoDb::save(const Document& document)
{
	mysqlpp::Query query(&this->connection);

	std::string url{};
	query.escape_string(&url, document.getUrl().c_str());
	std::string title{};
	query.escape_string(&title, document.getTitle().c_str());
	std::string description{};
	query.escape_string(&description, document.getDescription().c_str());
	std::string content{};
	query.escape_string(&content, document.getContent().c_str());

	query << "INSERT INTO documents(url, title, description, content) " << "VALUES ('"
		  << url << "', '" << title << "', '" << description << "', '" << content << "') "
		  << "ON DUPLICATE KEY UPDATE title='" << title
		  << "', description='" << description << "', content='" << content << "', updated=DEFAULT;";
	if (!query.exec()) {
		std::cerr << "can't store document: " << document.getUrl() << std::endl;
		std::cerr << query.error() << std::endl;
	}
}

std::unique_ptr<Document> DocumentRepoDb::getDocumentFromDbRow(const mysqlpp::Row& row)
{
	tm timeStruct{};
	strptime(row["updated"].c_str(), "%Y-%m-%d %H:%M:%S", &timeStruct);

	return std::make_unique<Document>(row[0], row[1].data(), row[2].data(),
			row[3].data(), row[4].data(), time_t(std::mktime(&timeStruct)));
}
