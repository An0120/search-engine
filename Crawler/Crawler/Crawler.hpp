#include <memory>
#include "Parser.hpp"
#include "PageLoader.hpp"
#include "WebsiteRepoDb.hpp"
#include "LinkEntryRepoDb.hpp"
#include "DocumentRepoDb.hpp"

namespace crawler {
	int linkId = 1;
	int documentId = 1;
	int websiteId = 1;

	void saveInvalidLink(const LinkEntry& link, std::unique_ptr<LinkEntryRepo>& linkEntryRepo)
	{
		std::cout << "Found invalid link, its corresponding URL is shown bellow\n" << link.getUrl() << std::endl
				  << "From website with < " << link.getWebsiteId() << " > ID: " << std::endl;
		linkEntryRepo->save(LinkEntry(link.getId(), link.getWebsiteId(),
				link.getUrl(), LinkStatus::INVALID, time(nullptr)));
	}

	void saveDocument(const std::string& url, const Parser& parser,
			std::unique_ptr<DocumentRepo>& documentRepo)
	{
		auto documentOpt = documentRepo->getByUrl(url);
		if (documentOpt.has_value()) {
			documentRepo->save(Document(documentOpt->getId(), url, parser.getTitle(),
					parser.getDescription(), parser.getContent(), time(nullptr)));
		}
		else {
			documentRepo->save(Document(documentId++, url, parser.getTitle(),
					parser.getDescription(), parser.getContent(), time(nullptr)));
		}
		std::cout << "The document was saved successfully, its corresponding URL is shown below.\n" << url << std::endl;
	}

	void saveLinks(const Parser& parser, const LinkEntry& link, std::unique_ptr<LinkEntryRepo>& linkEntryRepo)
	{
		for (const auto& url : parser.getUrls()) {
			if (!linkEntryRepo->getByUrl(url).has_value()) {
				linkEntryRepo->save(
						LinkEntry(linkId++, link.getWebsiteId(), url, LinkStatus::WAITING, time(nullptr)));
				std::cout << "The link was saved successfully, its corresponding URL is shown below.\n"
						  << url << std::endl;
			}
		}
	}

	void crawlLink(const LinkEntry& link,
			std::unique_ptr<LinkEntryRepo>& linkEntryRepo,
			std::unique_ptr<DocumentRepo>& documentRepo)
	{
		auto page = PageLoader::load(link.getUrl());
		if (!page.valid()) {
			saveInvalidLink(link, linkEntryRepo);
			return;
		}
		Parser parser(page.getData(), page.getEffUrl());
		if (parser.invalid()) {
			saveInvalidLink(link, linkEntryRepo);
			return;
		}
		linkEntryRepo->save(LinkEntry(link.getId(), link.getWebsiteId(),
				link.getUrl(), LinkStatus::LOADED, time(nullptr)));
		std::cout << "The link was crawled successfully, its corresponding URL is shown below.\n"
				  << link.getUrl() << std::endl;

		saveDocument(link.getUrl(), parser, documentRepo);
		saveLinks(parser, link, linkEntryRepo);
	}

	void crawlWebsite(const Website& website,
			std::unique_ptr<LinkEntryRepo>& linkEntryRepo,
			std::unique_ptr<DocumentRepo>& documentRepo)
	{
		auto homepageOpt = linkEntryRepo->getByUrl(website.getHomepage());
		if (homepageOpt.has_value()) {
			linkEntryRepo->save(LinkEntry(homepageOpt->getId(), homepageOpt->getWebsiteId(),
					homepageOpt->getUrl(), LinkStatus::WAITING, time(nullptr)));
		}
		else {
			linkEntryRepo->save(LinkEntry(linkId++, website.getId(),
					website.getHomepage(), LinkStatus::WAITING, time(nullptr)));
		}

		while (true) {
			constexpr int expectedLinksCount = 144;
			auto links = linkEntryRepo->getBy(website.getId(), LinkStatus::WAITING, expectedLinksCount);
			if (links.empty()) {
				std::cout << "There's no more links for crawling, please update database for continue." << std::endl;
				break;
			}
			for (const auto& link : links) {
				crawlLink(link, linkEntryRepo, documentRepo);
			}
		}
		std::cout << "The website was crawled successfully, its corresponding URL is shown below.\n"
				  << website.getHomepage() << std::endl;
	}

	void start(const std::string& dbName, const std::string& serverName, const std::string& username,
			const std::string& password, const unsigned long& port,
			const std::vector<std::pair<std::string, std::string>>& websitesToAdd)
	{
		try {
			std::unique_ptr<WebsiteRepo> websiteRepo =
					std::make_unique<WebsiteRepoDb>(dbName, serverName, username, password, port);
			std::unique_ptr<LinkEntryRepo> linkEntryRepo =
					std::make_unique<LinkEntryRepoDb>(dbName, serverName, username, password, port);
			std::unique_ptr<DocumentRepo> documentRepo =
					std::make_unique<DocumentRepoDb>(dbName, serverName, username, password, port);

			for (const auto& current : websitesToAdd) {
				websiteRepo->save(Website(websiteId++, current.first, current.second, time(nullptr)));
			}

			const auto& websites = websiteRepo->getAll();
			for (const auto& website : websites) {
				crawlWebsite(website, linkEntryRepo, documentRepo);
				websiteRepo->save(Website(website.getId(), website.getDomain(), website.getHomepage(), time(nullptr)));
			}
		}
		catch (const mysqlpp::ConnectionFailed& failed) {
			std::cerr << "Please check your database validation, see parameters in config file" << std::endl;
			std::cerr << failed.what() << std::endl;
		}
		catch (const mysqlpp::UseQueryError& failed) {
			std::cerr << failed.what() << std::endl;
		}
		catch (const std::exception& except) {
			std::cerr << except.what() << std::endl;
		}
	}
} // namespace crawler