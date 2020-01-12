//
// Created by tux on 06/10/2019.
//

#ifndef WEBWALLETCRACKER_UTILS_H
#define WEBWALLETCRACKER_UTILS_H

#include <map>
#include <vector>

// Dump function which add space every 2 char of a char[]
std::string addSpace(std::string str);

// Convert bytes char to Hex string
std::string byteCharToHexString(unsigned char* arr, size_t size);

// Conversion from hex string to bytes char
void hexStringToByteChar(std::string hashAsHex, unsigned char* ptr, size_t size);

// Generate a random string
std::string random_string(std::size_t length);

#endif //WEBWALLETCRACKER_UTILS_H
