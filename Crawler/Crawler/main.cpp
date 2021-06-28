#include "Crawler.hpp"

int main(int argc, char** argv)
{
	std::cout << "Look the program  output in 'errors.txt' and 'logs.txt' files." << std::endl;
	crawler::start(
			parser.getDbName(), parser.getServerName(), parser.getUsername(),
			parser.getPassword(), parser.getPort(), parser.getWebsites());
	return 0;
}