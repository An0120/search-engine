#ifndef CRAWLER_PAGELOADER_HPP
#define CRAWLER_PAGELOADER_HPP

#include <string>
#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>

#include "Page.hpp"

class PageLoader {
public:
	Page load(const std::string& url);
};  

#endif //CRAWLER_PAGELOADER_HPP

