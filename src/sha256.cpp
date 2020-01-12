
#include "Utils.h"
#include "sha256.h"
#include <cstring>

std::string sha256_string(const char *string)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, string, strlen(string));
    SHA256_Final(hash, &sha256);

    static const char characters[] = "0123456789abcdef";
    std::string result (SHA256_DIGEST_LENGTH * 2, ' ');
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        result[2*i] = characters[(unsigned int) hash[i] >> 4];
        result[2*i+1] = characters[(unsigned int) hash[i] & 0x0F];
    }
    return result;
}


int sha256_bytes(unsigned char *bytesInput,unsigned char *hashed,size_t size)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    int i=0;
    while(i < size)
    {
        SHA256_Update(&sha256, (bytesInput+i++), 1);
    }
    SHA256_Final(hash, &sha256);
    memcpy ( hashed, hash, SHA256_DIGEST_LENGTH );

    return 0;
}