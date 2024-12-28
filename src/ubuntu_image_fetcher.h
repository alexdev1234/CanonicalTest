#ifndef UBUNTU_IMAGE_FETCHER_H
#define UBUNTU_IMAGE_FETCHER_H

// Includes
#include <string>
#include <vector>


// Virtual class - implementation class will be in cpp file, from which executable is built
class UbuntuImageFetcher
{
public:
	~UbuntuImageFetcher() = default;

	// Return list of supported releases
	std::vector<std::string> GetSupportedReleases() const;

	// Return current Ubuntu LTS version
	std::string GetCurrentLTSVersion() const;

	// Return SHA256 hash of disk1.img of given Ubuntu release
	std::string GetDiskSHA256(const std::string& release) const;
};

#endif