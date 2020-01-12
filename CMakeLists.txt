cmake_minimum_required(VERSION 3.14)
project(btcaddressgeneratorcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "-lgmp")
find_package(OpenSSL REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


add_executable(btcaddressgeneratorcpp main.cpp src/generator.cpp include/generator.h src/Utils.cpp include/Utils.h src/sha256.cpp include/sha256.h src/base58.cpp include/base58.h include/bech32.h src/bech32.cpp include/segwit_addr.h src/segwit_addr.cpp src/ThreadPool.cpp include/ThreadPool.h)
include_directories(secp256k1/include)
include_directories(/usr/lib)
include_directories(include)

target_link_libraries(btcaddressgeneratorcpp ${PROJECT_SOURCE_DIR}/lib/libsecp256k1.a gmp OpenSSL::SSL Threads::Threads)