// Includes
#include "ubuntu_image_fetcher.h"

// C++ includes
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <fstream>

// External includes
#include <nlohmann/json.hpp>
#include <curl/curl.h>

// For ease of use
using json = nlohmann::json;

// Variables
static std::string url = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";

// Custom function to handle the write operation
static size_t WriteCallback(void* ptr, size_t size, size_t nmemb, std::stringstream* data)
{
	data->write(static_cast<char*>(ptr), size * nmemb);
	return size * nmemb;
}

// Progress callback function
int ProgressCallback(void* ptr, double dltotal, double dlnow, double uptotal, double upnow)
{
	// Only track download progress (not upload progress)
	if (dltotal > 0)
	{
		// Print the download progress based on the total size and current download size
		std::cout << "Download progress: " << dlnow << "/" << dltotal << std::endl;
	}
	return 0;  // Returning 0 means continue downloading
}

// Helper function to make an http get request and return the result
static std::string GetHTTP(const std::string& url)
{
	CURL* curl;
	CURLcode res;
	std::stringstream response;

	// Initialize libcurl
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		// Specify the callback function to handle the response data
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		// Enable automatic decompression (same as --compressed)
		curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip, deflate");

		// Set the progress function
		curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, ProgressCallback);
		curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, nullptr);  // No extra data passed to the callback

		// Perform the request
		res = curl_easy_perform(curl);

		if (res != CURLE_OK)
		{
			throw std::runtime_error("CURL request failed: " + std::string(curl_easy_strerror(res)));
		}

		// Cleanup
		curl_easy_cleanup(curl);

		// Cleanup global resources
		curl_global_cleanup();

		return response.str();
	}
	else
	{
		throw std::runtime_error("Failed to initialize CURL.");
	}
}


// Parse Json data and return the parsed object
static json ParseJsonData()
{
	static json cachedData = nullptr;

	// Cache the parsed data so we don't fetch the same data multiple times
	if (cachedData.is_null())
	{
		std::string data = GetHTTP(url);
		cachedData = json::parse(data);
	}

	return cachedData;
}

// Grab all supported releases
std::vector<std::string> UbuntuImageFetcher::GetSupportedReleases() const
{
	json data = ParseJsonData();
	std::vector<std::string> supportedReleases;

	for (const auto& item : data["products"].items())
	{
		const auto& product = item.value();

		// Check for amd64 architecture and that it is supported
		if (product.contains("arch") && product["arch"] == "amd64" && 
			product.contains("supported") && product["supported"] == true)
		{
			// Adding release title to array
			supportedReleases.push_back(product["release"].get<std::string>());
		}
	}

	return supportedReleases;
}

// Grab current Ubuntu LTS version
std::string UbuntuImageFetcher::GetCurrentLTSVersion() const
{
	json data = ParseJsonData();

	for (const auto& item : data["products"].items())
	{
		const auto& product = item.value();

		// Check if it's an LTS release and has the amd64 architecture
		if (product.contains("arch") && product["arch"] == "amd64" &&
			product.contains("release_title") && product["release_title"].get<std::string>().find("LTS") != std::string::npos &&
			product.contains("supported") && product["supported"] == true)
		{
			return product["release_title"].get<std::string>();  // Return the LTS version title
		}
	}

	return "No LTS version found.";
}

// Get sha256 hash of disk1.img for given Ubuntu release
std::string UbuntuImageFetcher::GetDiskSHA256(const std::string& release) const
{
	json data = ParseJsonData();

	for (const auto& item : data["products"].items())
	{
		const auto& product = item.value();

		if (product.contains("release") && product["release"] == release &&
			product.contains("arch") && product["arch"] == "amd64" &&
			product.contains("versions"))
		{
			// Iterate through versions and find the sha256 for disk1.img
			for (const auto& versionItem : product["versions"].items())
			{
				const auto& versionData = versionItem.value();
				if (versionData.contains("items") && versionData["items"].contains("disk1.img"))
				{
					return versionData["items"]["disk1.img"]["sha256"];
				}
			}
		}
	}

	return "Disk image not found";
}