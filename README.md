Git Repo: https://github.com/alexdev1234/CanonicalTest/tree/main

------- Build instructions for windows -------
Requirements: libcurl
Instructions on how to download libcurl:
1) Open up command prompt
2) Navigate to your C drive (`cd C:\`)
3) Clone the vcpkg repo from Github: `git clone https://github.com/microsoft/vcpkg.git`
4) Navigate to the vcpkg directory and build it:
     `cd vcpkg
     .\bootstrap-vcpkg.bat`
5) Install libcurl using vckpkg: `.\vcpkg install curl`

Instructions for building the project on windows - if build folder is not included:
1) After extracting the project from the tar.gz, open command prompt
2) Navigate to the root of the project folder and create a build folder (`mkdir build`)
3) Navigate into the build folder (cd build) and point cmake at libcurl using the following command (`cmake -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake ..`)
     Note: The file path provided should be the same if the above steps were followed. If the file path for this file is different please insert the correct filepath after `-DCMAKE_TOOLCHAIN_FILE=`
4) You can now build the project by performing the following command: `cmake --build .` while still remaining in the build folder
5) A debug build will have built in the debug folder. Navigate to the debug folder `cd Debug`
6) Run the created executable `CanonicalTest.exe`

If build folder is included:
1) After extracting the project from the tar.gz, open command prompt and navigate to the Debug folder of the project
2) Run the executable `CanonicalTest.exe`

------- Build instructions for linux -------
Was unable to test on Linux

------ Build instructions for macOS --------
Was unable to test on macOS
