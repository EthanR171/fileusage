#pragma once

/*
AUTHOR: Ethan Rivers
PURPSOSE: contains struct for map values
DATE: 2023-08-08
FILENAME: extensionInfo.hpp
*/
#include <string>
#include <filesystem>

struct ExtensionInfo {
    size_t count{ 0 };
    uintmax_t totalSize{ 0 };
};
