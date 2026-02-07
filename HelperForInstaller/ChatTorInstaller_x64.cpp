/*
Compile:
g++ ChatTorInstaller_x64.cpp -o ChatTorInstaller_x64.exe -mconsole -lurlmon -lole32 -std=c++17 -static
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
    "middle.exe",
    "ChatTorFrontEnd.exe"
};

int main()
{
    std::cout << "==== ChatTor Installer x64 ====\n\n";

    namespace fs = std::filesystem;

    fs::path installDir = "C:\\ChatTor";

    try
    {
        if (!fs::exists(installDir))
        {
            std::cout << "Creating install directory...\n";
            fs::create_directories(installDir);
        }
    }
    catch (...)
    {
        std::cout << "Failed to create install directory!\n";
        system("pause");
        return 1;
    }

    bool allSuccess = true;

    for (const auto& filename : FILES)
    {
        std::string url = BASE_URL + filename;
        fs::path destPath = installDir / filename;

        std::cout << "Downloading " << filename << " ... ";

        HRESULT hr = URLDownloadToFileA(
            nullptr,
            url.c_str(),
            destPath.string().c_str(),
            0,
            nullptr
        );

        if (SUCCEEDED(hr))
        {
            std::cout << "OK\n";
        }
        else
        {
            std::cout << "FAILED (HRESULT 0x" << std::hex << hr << std::dec << ")\n";
            allSuccess = false;
        }
    }

    if (!allSuccess)
    {
        std::cout << "\nSome files failed to download.\n";
        system("pause");
        return 1;
    }

    std::cout << "\nInstallation complete!\n";

    std::string frontendPath = (installDir / "ChatTorFrontEnd.exe").string();

    ShellExecuteA(
        NULL,
        "open",
        frontendPath.c_str(),
        NULL,
        installDir.string().c_str(),
        SW_SHOW
    );

    return 0;
}
