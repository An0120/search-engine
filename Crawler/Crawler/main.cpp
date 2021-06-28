#include <filesystem>
#include "ConfigParser.hpp"
#include "Crawler.hpp"

int main(int argc, char** argv)
{
	std::cout << "Look the program  output in 'errors.txt' and 'logs.txt' files." << std::endl;
	RedirectFStream redirectErr("errors.txt", stderr);
	RedirectFStream redirectLog("logs.txt", stdout);
	ConfigParser parser(getGivenFilePath(argc, argv));
	crawler::start(
			parser.getDbName(), parser.getServerName(), parser.getUsername(),
			parser.getPassword(), parser.getPort(), parser.getWebsites());
	return 0;
}