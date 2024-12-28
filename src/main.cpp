#include <iostream>
#include "ubuntu_image_fetcher.h"

int main()
{
    UbuntuImageFetcher fetcher;

    // Fetch and display supported releases
    std::cout << "Fetching supported Ubuntu releases for amd64 architecture..." << std::endl;
    std::vector<std::string> releases = fetcher.GetSupportedReleases();

    if (releases.empty())
    {
        std::cout << "No supported releases found!" << std::endl;
    }
    else
    {
        std::cout << "\n Supported Ubuntu Releases:" << std::endl;
        for (const auto& release : releases)
        {
            std::cout << " - " << release << std::endl;  // Corrected from 'std::count'
        }
    }

    // Grab and display current Ubuntu LTS version
    std::string ltsVersion = fetcher.GetCurrentLTSVersion();
    std::cout << "\n Current Ubuntu LTS Version: " << ltsVersion << std::endl;

    // Grab SHA256 hash for specific release
    std::string testRelease = "oneiric";
    std::string sha256 = fetcher.GetDiskSHA256(testRelease);
    std::cout << "\n SHA256 for " << testRelease << " disk1.img: " << sha256 << std::endl;

    return 0;
}
