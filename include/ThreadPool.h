//
// Created by tux on 07/01/2020.
//

#ifndef BTCADDRESSGENERATORCPP_THREADPOOL_H
#define BTCADDRESSGENERATORCPP_THREADPOOL_H

#include <mutex>
#include <vector>
#include <thread>
#include <secp256k1.h>
#include <map>

class ThreadPool {

private:
    int m_maxThreads;
    std::thread *m_poolThread;
    std::vector<std::string> **m_ptrQueueArr;
    std::mutex **m_ptrMutexArr;

    bool m_finishVal;
    std::mutex m_finishMut;
    secp256k1_context *m_prtContext;


public:
    explicit ThreadPool(secp256k1_context *prtContext);
    ~ThreadPool();
    void work(std::vector<std::string> *queue, std::mutex *queueLock);
    void endWork();
    void joinThread();
    void sendWork(std::string &&line);

};

#endif //BTCADDRESSGENERATORCPP_THREADPOOL_H