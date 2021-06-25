#ifndef CRAWLER_CONFIGPARSER_HPP
#define CRAWLER_CONFIGPARSER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "nlohmann/json.hpp"

#define DB_INFO "databaseInfo"
#define DB_NAME "databaseName"
#define SERVER_NAME "serverName"
#define USERNAME "username"
#define PASSWORD "password"
#define PORT "port"
#define WEBSITES "websitesToAdd"
#define DOMAIN "domain"
#define HOMEPAGE "homepageUrl"

class ConfigParser {
private:
	std::string dbName;
	std::string serverName;
	std::string username;
	std::string password;
	unsigned long port;
	std::vector<std::pair<std::string, std::string>> websites;

public:
	explicit ConfigParser(const std::string& configFilePath);

	[[nodiscard]] inline const std::string& getDbName() const
	{
		return this->dbName;
	}

	[[nodiscard]] inline const std::string& getServerName() const
	{
		return this->serverName;
	}

	[[nodiscard]] inline const std::string& getUsername() const
	{
		return this->username;
	}

	[[nodiscard]] inline const std::string& getPassword() const
	{
		return this->password;
	}

	[[nodiscard]] inline const unsigned long& getPort() const
	{
		return this->port;
	}

	[[nodiscard]] inline const std::vector<std::pair<std::string, std::string>>& getWebsites() const
	{
		return this->websites;
	}

private:
	void readFile(const std::string& path);
	void parseArguments();

	nlohmann::json configs;
};

#endif //CRAWLER_CONFIGPARSER_HPP