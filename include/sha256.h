

#ifndef WEBWALLETCRACKER_SHA_H
#define WEBWALLETCRACKER_SHA_H

#include <openssl/sha.h>

#define SHA256_STRING_LENGTH 64
#define SHA256_PUBEXTENDED_DIGEST_LENGTH 33

// Make sha256 hash fontion on a string
std::string sha256_string(const char *string);

// Make sha256 hash fontion on a bytes array
int sha256_bytes(unsigned char *bytesInput,unsigned char *hashed,size_t size);

#endif //WEBWALLETCRACKER_SHA_H