#include <iostream>
#include "ubuntu_image_fetcher.h"

void DisplayMenu()
{
    std::cout << "Please choose an option:" << std::endl;
    std::cout << "1) Grab the supported Ubuntu releases" << std::endl;
    std::cout << "2) Get the current Ubuntu LTS version" << std::endl;
    std::cout << "3) Grab the SHA256 hash for a specific release" << std::endl;
    std::cout << "Enter your choice (1-3): ";
}

int main()
{
    UbuntuImageFetcher fetcher;
    int choice;

    // Display the menu and get the user's choice
    DisplayMenu();
    std::cin >> choice;

    //// Fetch and display supported releases
    //std::cout << "Fetching supported Ubuntu releases for amd64 architecture..." << std::endl;
    //std::vector<std::string> releases = fetcher.GetSupportedReleases();

    //if (releases.empty())
    //{
    //    std::cout << "No supported releases found!" << std::endl;
    //}
    //else
    //{
    //    std::cout << "\n Supported Ubuntu Releases:" << std::endl;
    //    for (const auto& release : releases)
    //    {
    //        std::cout << " - " << release << std::endl;  // Corrected from 'std::count'
    //    }
    //}

    //// Grab and display current Ubuntu LTS version
    //std::string ltsVersion = fetcher.GetCurrentLTSVersion();
    //std::cout << "\n Current Ubuntu LTS Version: " << ltsVersion << std::endl;

    //// Grab SHA256 hash for specific release
    //std::string testRelease = "oneiric";
    //std::string sha256 = fetcher.GetDiskSHA256(testRelease);
    //std::cout << "\n SHA256 for " << testRelease << " disk1.img: " << sha256 << std::endl;

    switch (choice)
    {
    case 1:
    {
        // Fetch and display supported releases
        std::cout << "Fetching supported Ubuntu releases for amd64 architecture..." << std::endl;
        std::vector<std::string> releases = fetcher.GetSupportedReleases();

        if (releases.empty())
        {
            std::cout << "No supported releases found!" << std::endl;
        }
        else
        {
            std::cout << "\nSupported Ubuntu Releases:" << std::endl;
            for (const auto& release : releases)
            {
                std::cout << " - " << release << std::endl;  // Display supported releases
            }
        }
        break;
    }

    case 2:
    {
        // Get and display the current Ubuntu LTS version
        std::string ltsVersion = fetcher.GetCurrentLTSVersion();
        std::cout << "\nCurrent Ubuntu LTS Version: " << ltsVersion << std::endl;
        break;
    }

    case 3:
    {
        // Get SHA256 hash for a specific release
        std::cout << "Enter the release name (e.g., 'oneiric'): ";
        std::string releaseName;
        std::cin >> releaseName;  // Get the release name from the user

        std::string sha256 = fetcher.GetDiskSHA256(releaseName);
        std::cout << "\nSHA256 for " << releaseName << " disk1.img: " << sha256 << std::endl;
        break;
    }

    default:
        std::cout << "Invalid choice. Please enter a number between 1 and 3." << std::endl;
        break;
    }

    return 0;
}
