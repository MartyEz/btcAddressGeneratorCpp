//
// Created by tux on 20/11/2019.
//
#include "generator.h"
#include "sha256.h"
#include <openssl/ripemd.h>
#include "base58.h"
#include "Utils.h"
#include "segwit_addr.h"

std::vector<std::string> generateAddress(unsigned char *pub_compressed) {

    unsigned char pbcSha[SHA256_DIGEST_LENGTH];
    sha256_bytes(pub_compressed, pbcSha, SHA256_PUBEXTENDED_DIGEST_LENGTH);

//---------------------------------RIPEMD160-----------------------------------
    unsigned char ripemd160Hash[RIPEMD160_DIGEST_LENGTH];
    RIPEMD160((unsigned char *) pbcSha, SHA256_DIGEST_LENGTH, (unsigned char *) &ripemd160Hash);
//-----------------------------------------------------------------------------

    std::string legacyAddress = generateLegacy(ripemd160Hash);
    std::string segWitAddress = generateSegwit(ripemd160Hash);
    std::string bech32Address = generateBech32(ripemd160Hash);

    std::vector<std::string> address;
    address.push_back(legacyAddress);
    address.push_back(segWitAddress);
    address.push_back(bech32Address);

    return address;

}

std::string generateLegacy(unsigned char *ripemd160Hash) {

    unsigned char concat[RIPEMD160_DIGEST_LENGTH + 1];
    concat[0] = 0x00;
    for (int i = 0; i < RIPEMD160_DIGEST_LENGTH; i++)
        concat[i + 1] = ripemd160Hash[i];

    unsigned char out3[SHA256_DIGEST_LENGTH];
    sha256_bytes(concat, out3, 21);

    unsigned char out4[SHA256_DIGEST_LENGTH];
    sha256_bytes(out3, out4, SHA256_DIGEST_LENGTH);

    unsigned char checksum[4] = {out4[0], out4[1], out4[2], out4[3]};

    unsigned char beforebase58[RIPEMD160_DIGEST_LENGTH + 1 + 4];
    beforebase58[0] = 0x00;
    for (int i = 0; i < RIPEMD160_DIGEST_LENGTH; i++)
        beforebase58[i + 1] = ripemd160Hash[i];
    for (int i = 0; i < 4; i++)
        beforebase58[RIPEMD160_DIGEST_LENGTH + i + 1] = checksum[i];

    std::string b58encoded = EncodeBase58(beforebase58,beforebase58+RIPEMD160_DIGEST_LENGTH + 1 + 4);

    return b58encoded;
}

std::string generateSegwit(unsigned char *ripemd160Hash) {

    unsigned char concat[RIPEMD160_DIGEST_LENGTH + 2];
    concat[0] = 0x00;
    concat[1] = 0x14;

    for (int i = 0; i < RIPEMD160_DIGEST_LENGTH; i++)
        concat[i + 2] = ripemd160Hash[i];

    unsigned char out3[SHA256_DIGEST_LENGTH];
    sha256_bytes(concat, out3, 22);

    unsigned char ripemd160Hash2[RIPEMD160_DIGEST_LENGTH];
    RIPEMD160((unsigned char *) out3, SHA256_DIGEST_LENGTH, (unsigned char *) &ripemd160Hash2);

    unsigned char extendedRipemd160Hash2[RIPEMD160_DIGEST_LENGTH + 1];
    extendedRipemd160Hash2[0] = 0x05;

    for (int i = 0; i < RIPEMD160_DIGEST_LENGTH; i++)
        extendedRipemd160Hash2[i + 1] = ripemd160Hash2[i];

    unsigned char out4[SHA256_DIGEST_LENGTH];
    sha256_bytes(extendedRipemd160Hash2, out4, 21);

    unsigned char out5[SHA256_DIGEST_LENGTH];
    sha256_bytes(out4, out5, SHA256_DIGEST_LENGTH);

    unsigned char checksum[4] = {out5[0], out5[1], out5[2], out5[3]};

    unsigned char beforebase58[RIPEMD160_DIGEST_LENGTH + 5];

    for (int i = 0; i <= RIPEMD160_DIGEST_LENGTH; i++)
        beforebase58[i] = extendedRipemd160Hash2[i];
    for (int i = 0; i < 4; i++)
        beforebase58[RIPEMD160_DIGEST_LENGTH + 1 + i] = checksum[i];

    std::string b58encoded = EncodeBase58(beforebase58,beforebase58+RIPEMD160_DIGEST_LENGTH + 1 + 4);

    return b58encoded;
}

std::string generateBech32(unsigned char *ripemd160Hash) {
    const std::string hrp = "bc";
    std::vector<uint8_t> in;
    for (int i = 0; i < RIPEMD160_DIGEST_LENGTH; i++)
        in.push_back(ripemd160Hash[i]);

    std::string bech32Address = segwit_addr::encode(hrp, 0, in);

    return bech32Address;
}

void generateKeyPair(secp256k1_context *context, std::string &stringSeed) {

        // Hash it to get 32 bytes value (64 as hex string)
        std::string s = sha256_string(stringSeed.c_str());

        // Transform 64 bytes hex string to 32 bytes char[] used as privKey
        unsigned char privKey[SHA256_DIGEST_LENGTH];
        hexStringToByteChar(addSpace(s), privKey, SHA256_DIGEST_LENGTH);

        // Init secp145k1 context and get pubKey from privKey

        secp256k1_pubkey pubKey;
        secp256k1_pubkey *ptr_pubKey = &pubKey;
        int result = secp256k1_ec_pubkey_create(context, ptr_pubKey, privKey);

        // Serialize the pubKey in his compressed format
        unsigned char pub_compressed[SHA256_PUBEXTENDED_DIGEST_LENGTH];
        size_t outputlen = SHA256_PUBEXTENDED_DIGEST_LENGTH;
        secp256k1_ec_pubkey_serialize(context, pub_compressed, &outputlen, ptr_pubKey, SECP256K1_EC_COMPRESSED);

        // Generate Bech32, Segwit and Legacy addresses from pubKey
        std::vector<std::string> address = generateAddress(pub_compressed);

        printf("%s\n%s\n%s\n%s\n%s\n%s\n--------------------------------------------------------------\n", stringSeed.c_str(),s.c_str(),byteCharToHexString(pub_compressed,SHA256_PUBEXTENDED_DIGEST_LENGTH).c_str(),address[0].c_str(),address[1].c_str(),address[2].c_str());

}
