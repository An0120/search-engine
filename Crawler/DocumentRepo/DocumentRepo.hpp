#ifndef CRAWLER_DOCUMENTREPO_HPP
#define CRAWLER_DOCUMENTREPO_HPP

#include <vector>
#include <optional>
#include "Document.hpp"

class DocumentRepo {
public:
	virtual ~DocumentRepo() = default;
	virtual std::optional<Document> getByUrl(const std::string& url) = 0;
	virtual void save(const Document& document) = 0;
};

#endif 