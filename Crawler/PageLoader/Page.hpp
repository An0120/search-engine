#ifndef CRAWLER_PAGE_HPP
#define CRAWLER_PAGE_HPP

#include <string>

class Page {
private:
	std::string data;
	std::string effUrl;
	long status;

public:
	Page(std::string effUrl, std::string data, long status);

    std::string geteffurl();

	std::string getdata();

	long getstatus();
};

#endif //CRAWLER_PAGE_HPP