# btcAddressGeneratorCpp

- This program was made in order to test security of web wallet and app wallet. Some of theses use user inputs in order to generate seed for the privKey
- It generates privKey, pubKey, Segwit, Bech32, Legacy addresses from seed
- The seed generation algorithms targeted have been replaced by a simple random string generator in this version.
- This program uses multi-Threads/multi-WorkQueue

# Dependencies

- This program use OpenSSL libs for SHA256 and ripemd160 hashing functions. 
    - https://www.openssl.org/
- This program use gmplib for BigInt implementations. OpenSSL use lgmp too.
    - https://gmplib.org/
- C libsecp256k1  
    - https://github.com/bitcoin-core/secp256k1
    - lib/libsecp256k1.a is compiled for unix 64x. But you can recompile your own

# Sources
- This program use Pieter Wuille codes for Segwit and Bench32 generation addresses
    - https://github.com/bitcoin/bitcoin
    - https://github.com/sipa
    
# Performances

- 5 Millions generations in 48 seconds.  

I made the same program in GO : https://github.com/MartyEz/btcAddressGeneratorGo
 