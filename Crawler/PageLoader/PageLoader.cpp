#include "PageLoader.hpp"

Page PageLoader::load(const std::string& url)
{
	try {
		curlpp::Easy request;

		curlpp::Cleanup cleaner;

		request.setOpt(curlpp::Options::Url(url));
		request.setOpt(curlpp::Options::FollowLocation(true));

		std::ostringstream os;

		curlpp::options::WriteStream ws(&os);

		request.setOpt(ws);
		request.perform();

		std::string effUrl;
		curlpp::infos::EffectiveUrl::get(request, effUrl);

		return Page(effUrl, os.str(), curlpp::infos::ResponseCode::get(request));
	}
	catch (const curlpp::LibcurlRuntimeError& error) {
		std::cout << "thrown exception from 'page loader': " << error.what() << std::endl;
		return Page(url, std::string{}, 400);
	}
}