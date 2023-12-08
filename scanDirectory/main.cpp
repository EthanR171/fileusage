/*
AUTHOR: Ethan Rivers
PURPSOSE: Scan through a given directory to get size of files
DATE: 2023-08-08
FILENAME: main.cpp
*/
#include <iostream>
#include <deque>
#include <filesystem>
#include <iomanip>
#include <map>
#include <algorithm>
#include <regex>
#include "extensionInfo.hpp"
#include "outputs.hpp"
#include "traverse.hpp"
#include "formatting.hpp"
using namespace std;
namespace fs = std::filesystem;

/*

	Purpose: c++ windows console application that lists file usage.
	Files will be counted and their sizes totaled.
	Files will be grouped by file extension.
	The files should be listed in alphabetical order of the extension.

	non functional requirments:

	Sizes must be comma seperated numbers
	Listing should be right aligned columns

	-----------------------------------------------------------

	command line options: fileusage [-hrsx] [--help] [folder]

	default: If no switches, the program runs recursively in the current directory, showing all files
	with file types listed in alphabetical order by extension, without the directory listing

	switches: h(displays help)
	 r(reverse order of listing)
	 s(sort by ascending file size not by extension)
	 x(limits search to only files that match extensions specified by a regex expression ie. "\.(docx|xlsx)")

	 sr|rs (sort in descending order by file size not extension)

		Folder: [folder] is root directoy

*/

int main(int argc, char* argv[]) {
	deque<string> myDeque;

	vector<char> switches{ 'h','r','s','x' };
	bool flagH = false, flagR = false, flagS = false, flagX = false, switchDetected = false;
	string switchREQ;
	string regexPattern;

	fs::path path = fs::current_path();
	map<string, ExtensionInfo> dataMap;

	//load deque with arguments
	for (size_t i = 0; i < argc; ++i)
		myDeque.push_back(argv[i]);
	myDeque.pop_front();
		
	//look for --help or -h on first initial pass through. (do second pass later to isolate for -h embedded within switch)
	for (size_t i = 0; i < myDeque.size(); ++i) {
		if (myDeque[i] == "--help" || myDeque[i] == "-h")
			displayHelp();
	}

	//defualt functionality case (empty deque)
	if (myDeque.empty()) {
		loadMap(path, dataMap);
		displayFileUsage(dataMap);    
	}

	//switch entered case
	/*
		set the switch to be front of deque
		loop through the string to set switch flags to true if needed
		if switch -h display help and quit the program
	*/
	if (myDeque.front()[0] == '-') {
		switchREQ = myDeque.front();
		myDeque.pop_front();
		for (size_t i = 1; i < switchREQ.size(); ++i) {
			char ch = switchREQ[i];
			switch (ch) {
			case 'h':
				displayHelp();
				break;
			case 'r':
				switchDetected = true;
				flagR = true;
				break;
			case 's':
				switchDetected = true;
				flagS = true;
				break;
			case 'x':
				switchDetected = true;
				flagX = true;
				break;
			}
		}

	}

	//invalid switch
	if (myDeque.empty() && !switchDetected) {
		loadMap(path, dataMap);
		displayFileUsage(dataMap);
	}

	//look for regex pattern if switch x was found
	if (flagX && !myDeque.empty()) {
		regexPattern = ".*\\" + myDeque.front().substr(1);
		myDeque.pop_front();
	}
	else if (flagX && myDeque.empty()) {
		cerr << "Error: Error: -x switch used without regular expression argument provided.\n";
		exit(EXIT_FAILURE);
	}


	//look for folder
	if (!myDeque.empty()) {
		//new path will be the value still in deque
		try {
			path = fs::canonical(myDeque.front()); // This will throw an exception if the path is not valid.
			myDeque.pop_front(); //after this anything left over in deque is an extra argument
		}
		catch (const fs::filesystem_error& e) {
			cerr << "Error: " << e.what() << "\n";
			exit(EXIT_FAILURE);
		}

		if (!myDeque.empty()) {
			cerr << "Error: Error: too many commandline arguments: " << myDeque.front() << "...";
			exit(EXIT_FAILURE);
		}
	}
	//only a folder was given (no switches)
	if (!switchDetected) {
		loadMap(path, dataMap);
		displayFileUsage(dataMap);
	}

	if (flagX) {
		loadMapRegex(path, dataMap, regexPattern);
		displayFileUsage(dataMap);
	}

	if (flagR && flagS) {
		loadMap(path, dataMap);
		displayFileUsageRS(dataMap);
	}
	else if (flagR) {
		loadMap(path, dataMap);
		displayFileUsageR(dataMap);
	}
	else if (flagS) {
		loadMap(path, dataMap);
		displayFileUsageS(dataMap);
	}
	return 0;
}