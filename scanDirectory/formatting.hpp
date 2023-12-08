/*
AUTHOR: Ethan Rivers
PURPSOSE: contains any formatting functions
DATE: 2023-08-08
FILENAME: formatting.hpp
*/
#pragma once
//#include "extensionInfo.hpp"
#include <string>

/*
*	@name addCommas
*	@breif When called, we format a number with commas every third position(hundreds spot)
*	@param uintmax_t 
*	@return string
*	@note 
*/
std::string addCommas(uintmax_t number) {
    std::string formattedNumber = std::to_string(number);
    int count = 0;
    for (int i = formattedNumber.length() - 1; i > 0; --i) {
        count++;
        if (count % 3 == 0) {
            formattedNumber.insert(i, ",");
        }
    }
    return formattedNumber;
}






