/*
Compile:
  g++ ChatTorInstaller_x64.cpp -o ChatTorInstaller_x64.exe -mconsole -lurlmon -lole32 -std=c++17 -static
  https://bendosh4.github.io/ChatTorWebSite/
*/

#include <windows.h>
#include <urlmon.h>
#include <iostream>
#include <filesystem>
#include <vector>

#pragma comment(lib, "urlmon.lib")

const std::string BASE_URL = "https://bendosh4.github.io/ChatTorWebSite/HelperForInstaller/FilesToDownload/";

const std::vector<std::string> FILES = {
    "Client.exe",
    "entry.exe",
    "exit.exe",
    "middle.exe"
};

int main()
{
    std::cout << "==== ChatTor Installer x64 ====\n\n";

    namespace fs = std::filesystem;
    fs::path destDir = fs::current_path();

    for (const auto& filename : FILES)
    {
        std::string url = BASE_URL + filename;
        fs::path destPath = destDir / filename;

        std::cout << "Downloading " << filename << " ... ";
        HRESULT hr = URLDownloadToFileA(nullptr, url.c_str(), destPath.string().c_str(), 0, nullptr);
        if (SUCCEEDED(hr))
            std::cout << "OK\n";
        else
            std::cout << "Failed (HRESULT " << std::hex << hr << ")\n";
    }

    system("pause");
    return 0;
}
