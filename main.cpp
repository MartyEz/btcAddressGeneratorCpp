#include <iostream>
#include "Utils.h"
#include <secp256k1.h>
#include <mutex>
#include "ThreadPool.h"

int main() {

    secp256k1_context *context = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);

    ThreadPool *tp = new ThreadPool(context);

    auto start = std::chrono::high_resolution_clock::now();

    for (int j = 0; j < 1000000; ++j) {
        tp->sendWork(random_string(25));
    }

    tp->endWork();

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "It took me " << time_span.count() << " seconds.";

    secp256k1_context_destroy(context);
    return 0;
}
