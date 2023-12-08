/*
AUTHOR: Ethan Rivers
PURPSOSE: Header file that contains all output functions
DATE: 2023-08-08
FILENAME: outputs.hpp
*/
#pragma once
#include "extensionInfo.hpp"
#include "formatting.hpp"


using namespace std;


/*
*	@name displayHelp
*	@breif When called with display help menu on screen.
*	@param void
*	@return nothing
*	@note will make any other command line arguments ignored
*/
void displayHelp() {
	cout << "fileusage {v3.0.0} (c) 2016-23, Ethan Rivers\n\n"
		<< "        Usage: fileusage [--help] [-hrs(x regularexpression)] [folder]\n"
		<< "        switches:\n"
		<< "                h       help\n"
		<< "                r       reverse the order of the listing\n"
		<< "                s       sort by file sizes\n"
		<< "                x       filter with a regular expression\n\n"
		<< "        folder\n"
		<< "                starting folder or current folder if not provided\n";
	exit(EXIT_SUCCESS);
}

/*
*	@name displayFileUsage
*	@breif When called, we output the files in the current direcotry in right aligned columns
*   @param map<string, ExtensionInfo>&
*	@return nothing
*	@note
*/
void displayFileUsage(map<string, ExtensionInfo>& dataMap) {
	//formating variables for spaces needed
	size_t max_ext_len{ 0 };
	size_t max_count_len{ 0 };
	size_t max_total_len{ 0 };

	//total amounts for last output row
	uintmax_t totalExtensionTypes = dataMap.size();
	uintmax_t totalNumFiles{ 0 };
	uintmax_t totalNumBytes{ 0 };

	//find spacing needed for each row of data in outputs
	for (const auto& pair : dataMap) {
		max_ext_len = max(max_ext_len, pair.first.length());
		max_count_len = max(max_count_len, to_string(pair.second.count).length());
		max_total_len = max(max_total_len, addCommas(pair.second.totalSize).length());

		totalNumFiles += pair.second.count;
		totalNumBytes += pair.second.totalSize;

	}


	//header
	cout << right << setw(max_ext_len) << "Ext" << setw(max_count_len + 3) << "#" << setw(max_total_len + 3) << " Total" << "\n\n";

	//row data outputs
	for (const auto& pair : dataMap) {
		string temp = addCommas(pair.second.totalSize);
		cout << right << setw(max_ext_len) << pair.first << right << setw(max_count_len + 3) << pair.second.count << right << setw(max_total_len + 3) << temp << "\n\n";
	}

	 //print total counts (footer)
	cout << right << setw(max_ext_len) << totalExtensionTypes << right << setw(max_count_len + 3) << totalNumFiles << right << setw(max_total_len + 3) << addCommas(totalNumBytes) << "\n";
	exit(EXIT_SUCCESS);
}


/*
*	@name displayFileUsageR
*	@breif When called, we output the files in the current in  direcotry in right aligned columns in reverse
*   @param map<string, ExtensionInfo>&
*	@return nothing
*	@note
*/
void displayFileUsageR(map<string, ExtensionInfo>& dataMap) {
	//formating variables for spaces needed
	size_t max_ext_len{ 0 };
	size_t max_count_len{ 0 };
	size_t max_total_len{ 0 };

	//total amounts for last output row
	uintmax_t totalExtensionTypes = dataMap.size();
	uintmax_t totalNumFiles{ 0 };
	uintmax_t totalNumBytes{ 0 };

	//find spacing needed for each row of data in outputs
	for (const auto& pair : dataMap) {
		max_ext_len = max(max_ext_len, pair.first.length());
		max_count_len = max(max_count_len, to_string(pair.second.count).length());
		max_total_len = max(max_total_len, addCommas(pair.second.totalSize).length());

		totalNumFiles += pair.second.count;
		totalNumBytes += pair.second.totalSize;

	}

	//store map into a vector
	vector<pair<string, ExtensionInfo>> dataVec(dataMap.begin(), dataMap.end());
	reverse(dataVec.begin(), dataVec.end());


	//header
	cout << right << setw(max_ext_len) << "Ext" << setw(max_count_len + 3) << "#" << setw(max_total_len + 3) << " Total" << "\n\n";

	//row data outputs
	for (const auto& pair : dataVec) {
		string temp = addCommas(pair.second.totalSize);
		cout << right << setw(max_ext_len) << pair.first << right << setw(max_count_len + 3) << pair.second.count << right << setw(max_total_len + 3) << temp << "\n\n";
	}

	//print total counts (footer)
	cout << right << setw(max_ext_len) << totalExtensionTypes << right << setw(max_count_len + 3) << totalNumFiles << right << setw(max_total_len + 3) << addCommas(totalNumBytes) << "\n";
	exit(EXIT_SUCCESS);
}



/*
*	@name displayFileUsageS
*	@breif When called, we output the files in the current in  direcotry in right aligned columns by ascending fileSize
*   @param map<string, ExtensionInfo>&
*	@return nothing
*	@note
*/
void displayFileUsageS(map<string, ExtensionInfo>& dataMap) {
	//formating variables for spaces needed
	size_t max_ext_len{ 0 };
	size_t max_count_len{ 0 };
	size_t max_total_len{ 0 };

	//total amounts for last output row
	uintmax_t totalExtensionTypes = dataMap.size();
	uintmax_t totalNumFiles{ 0 };
	uintmax_t totalNumBytes{ 0 };

	//find spacing needed for each row of data in outputs
	for (const auto& pair : dataMap) {
		max_ext_len = max(max_ext_len, pair.first.length());
		max_count_len = max(max_count_len, to_string(pair.second.count).length());
		max_total_len = max(max_total_len, addCommas(pair.second.totalSize).length());

		totalNumFiles += pair.second.count;
		totalNumBytes += pair.second.totalSize;

	}

	//store map into a vector
	vector<pair<string, ExtensionInfo>> dataVec(dataMap.begin(), dataMap.end());
	//use lambda expression to sort based on file size ascending (returns a bool)
	sort(dataVec.begin(), dataVec.end(), [](const pair<string, ExtensionInfo>& a, const pair<string, ExtensionInfo>& b) {
		return a.second.totalSize < b.second.totalSize;
		});


	//header
	cout << right << setw(max_ext_len) << "Ext" << setw(max_count_len + 3) << "#" << setw(max_total_len + 3) << " Total" << "\n\n";

	//row data outputs
	for (const auto& pair : dataVec) {
		string temp = addCommas(pair.second.totalSize);
		cout << right << setw(max_ext_len) << pair.first << right << setw(max_count_len + 3) << pair.second.count << right << setw(max_total_len + 3) << temp << "\n\n";
	}

	//print total counts (footer)
	cout << right << setw(max_ext_len) << totalExtensionTypes << right << setw(max_count_len + 3) << totalNumFiles << right << setw(max_total_len + 3) << addCommas(totalNumBytes) << "\n";
	exit(EXIT_SUCCESS);
}


/*
*	@name displayFileUsageRS
*	@breif When called, we output the files in the current in  direcotry in right aligned columns by descending fileSize
*   @param map<string, ExtensionInfo>&
*	@return nothing
*	@note
*/
void displayFileUsageRS(map<string, ExtensionInfo>& dataMap) {
	//formating variables for spaces needed
	size_t max_ext_len{ 0 };
	size_t max_count_len{ 0 };
	size_t max_total_len{ 0 };

	//total amounts for last output row
	uintmax_t totalExtensionTypes = dataMap.size();
	uintmax_t totalNumFiles{ 0 };
	uintmax_t totalNumBytes{ 0 };

	//find spacing needed for each row of data in outputs
	for (const auto& pair : dataMap) {
		max_ext_len = max(max_ext_len, pair.first.length());
		max_count_len = max(max_count_len, to_string(pair.second.count).length());
		max_total_len = max(max_total_len, addCommas(pair.second.totalSize).length());

		totalNumFiles += pair.second.count;
		totalNumBytes += pair.second.totalSize;

	}

	//store map into a vector
	vector<pair<string, ExtensionInfo>> dataVec(dataMap.begin(), dataMap.end());
	//use lambda expression to sort based on file size ascending (returns a bool)
	sort(dataVec.begin(), dataVec.end(), [](const pair<string, ExtensionInfo>& a, const pair<string, ExtensionInfo>& b) {
		return a.second.totalSize < b.second.totalSize;
		});
	reverse(dataVec.begin(), dataVec.end());


	//header
	cout << right << setw(max_ext_len) << "Ext" << setw(max_count_len + 3) << "#" << setw(max_total_len + 3) << " Total" << "\n\n";

	//row data outputs
	for (const auto& pair : dataVec) {
		string temp = addCommas(pair.second.totalSize);
		cout << right << setw(max_ext_len) << pair.first << right << setw(max_count_len + 3) << pair.second.count << right << setw(max_total_len + 3) << temp << "\n\n";
	}

	//print total counts (footer)
	cout << right << setw(max_ext_len) << totalExtensionTypes << right << setw(max_count_len + 3) << totalNumFiles << right << setw(max_total_len + 3) << addCommas(totalNumBytes) << "\n";
	exit(EXIT_SUCCESS);
}
