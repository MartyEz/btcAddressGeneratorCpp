//
// Created by tux on 06/10/2019.
//
#include "Utils.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <filesystem>
#include <openssl/ripemd.h>
#include <random>
#include <algorithm>

std::string addSpace(std::string str) {
    std::stringstream ss;
    for (std::string::iterator it = str.begin(); it != str.end(); ++it)
        ss << *it << *(++it) << " ";
    return ss.str();
}

std::string byteCharToHexString(unsigned char *arr, size_t size) {
    std::stringstream ss;
    for (int i = 0; i < size; ++i) {
        ss << std::setfill('0') << std::setw(2) << std::hex << (int) arr[i];
    }
    std::string outputString = ss.str();
    return outputString;
}

void hexStringToByteChar(std::string hashAsHex, unsigned char *ptr, size_t size) {
    std::istringstream hex_chars_stream(hashAsHex);
    int i = 0;
    unsigned int c;
    while (hex_chars_stream >> std::hex >> c) {
        *(ptr + i++) = c;
    }
}

std::string random_string(std::size_t length)
{
        auto randchar = []() -> char
        {
            const char charset[] =
                    "0123456789"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
        };
        std::string str(length,0);
        std::generate_n( str.begin(), length, randchar );
        return str;
}

