#include "PageLoader.hpp"

Page PageLoader::load(const std::string& url)
{
	try {
		// for sending a request into given url
		curlpp::Easy request;

		// will clean up when destructor has been called
		curlpp::Cleanup cleaner;

		request.setOpt(curlpp::Options::Url(url));
		// try to find correct location
		request.setOpt(curlpp::Options::FollowLocation(true));

		// for saving info in this stream
		std::ostringstream os;

		// make option for writing into 'os' stream
		curlpp::options::WriteStream ws(&os);

		// change default write stream as 'os'
		request.setOpt(ws);
		request.perform();

		std::string effUrl;
		// write found effective url into effective url
		curlpp::infos::EffectiveUrl::get(request, effUrl);

		return Page(effUrl, os.str(), curlpp::infos::ResponseCode::get(request));
	}
	catch (const curlpp::LibcurlRuntimeError& error) {
		std::cout << "thrown exception from 'page loader': " << error.what() << std::endl;
		return Page(url, std::string{}, 400);
	}
}