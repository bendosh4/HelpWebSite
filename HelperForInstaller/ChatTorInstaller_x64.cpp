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

namespace fs = std::filesystem;

const std::wstring BASE_URL = L"https://bendosh4.github.io/ChatTorWebSite/";

const std::vector<std::wstring> FILES = {
    L"FilesToDownload/Client.exe",
    L"FilesToDownload/entry.exe",
    L"FilesToDownload/exit.exe",
    L"FilesToDownload/middle.exe"
};

bool DownloadFile(std::wstring url, std::wstring outputPath)
{
    std::wcout << L"Downloading: " << outputPath << std::endl;

    fs::create_directories(fs::path(outputPath).parent_path());

    HRESULT hr = URLDownloadToFileW(
        NULL,
        url.c_str(),
        outputPath.c_str(),
        0,
        NULL
    );

    if (SUCCEEDED(hr))
    {
        std::wcout << L"  OK\n";
        return true;
    }

    std::wcout << L"  FAILED\n";
    return false;
}

int main()
{
    std::wcout << L"==== ChatTor Installer x64 ====\n\n";

    fs::path exeDir = fs::current_path();

    int success = 0;
    int fail = 0;

    for (const auto& file : FILES)
    {
        std::wstring url = BASE_URL + file;
        fs::path localPath = exeDir / file;

        if (DownloadFile(url, localPath.wstring()))
            success++;
        else
            fail++;
    }

    std::wcout << L"\nFinished: "
               << success << L" succeeded, "
               << fail << L" failed\n";

    system("pause");
    return fail ? 1 : 0;
}
