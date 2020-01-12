//
// Created by tux on 20/11/2019.
//

#ifndef WEBWALLETCRACKER_GENERATOR_H
#define WEBWALLETCRACKER_GENERATOR_H

#include <string>
#include <vector>
#include <secp256k1.h>
#include <map>

// geberateAddress do first hash fonctions ( sha et ripemd) and launch Legacy, Segwit, Bech32 address generation
std::vector<std::string> generateAddress(unsigned char * pub);

// Generate a Legacy btc address from pubkey
std::string generateLegacy(unsigned char* ripemd160Hash);

// Generate a Segwit btc address from pubkey
std::string generateSegwit(unsigned char* ripemd160Hash);

// Generate a Bech32 btc address from pubkey
std::string generateBech32(unsigned char* ripemd160Hash);

// Generate keyPairs
void generateKeyPair(secp256k1_context *context, std::string& stringSeed);

#endif //WEBWALLETCRACKER_GENERATOR_H
