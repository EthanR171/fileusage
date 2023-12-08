/*
AUTHOR: Ethan Rivers
PURPSOSE: INFO1156-02 Project 4 fileusage
DATE: 2023-08-08
FILENAME: traverse.hpp
*/
#pragma once
#include "extensionInfo.hpp"
using namespace std;
namespace fs = std::filesystem;



/*
*	@name loadMap
*	@breif When called, we use an iterator to store files into a map as key value pairs
*	@param const fs::path& , map<string, ExtensionInfo>&
*	@return nothing
*	@note this version uses a try catch block to keep the program alive in the case of restriced files being encountered. (stays alive on path c:\)
*/
void loadMap(const fs::path& path, map<string, ExtensionInfo>& dataMap) {
	try {
		for (const auto& entry : fs::directory_iterator(path)) {
			try {
				if (entry.is_directory()) {
					loadMap(entry.path(), dataMap);
				}
				else if (entry.is_regular_file()) {
					string ext = entry.path().extension().string(); // extract extension to use as key in map
					dataMap[ext].count++; // value 1 for key
					dataMap[ext].totalSize += fs::file_size(entry); // value 2 for key
				}
			}
			catch (const fs::filesystem_error&) {
				// ignore restricted files and continue on to the next file or directory
			}
		}
	}
	catch (const fs::filesystem_error&) {
		// if the actual top lvel direcgtory is restricted for some reason we catch it here
	}
}


void loadMapRegex(const fs::path& path, map<string, ExtensionInfo>& dataMap, const string& pattern) {
    std::regex regexPattern(pattern);

    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            try {
                if (entry.is_directory()) {
                    loadMapRegex(entry.path(), dataMap, pattern);
                }
                else if (entry.is_regular_file()) {
                    string fileName = entry.path().filename().string(); // extract filename

                    // Match against the regex
                    if (std::regex_match(fileName, regexPattern)) {
                        string ext = entry.path().extension().string(); // extract extension to use as key in map
                        dataMap[ext].count++; // increment the count for the file's extension
                        dataMap[ext].totalSize += fs::file_size(entry); // accumulate the size for the file's extension
                    }
                }
            }
            catch (const fs::filesystem_error&) {
                // ignore restricted files and continue on to the next file or directory
            }
        }
    }
    catch (const fs::filesystem_error&) {
        // if the actual top-level directory is restricted, catch the error here
    }
}