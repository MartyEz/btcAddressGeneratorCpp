//
// Created by tux on 07/01/2020.
//

#include <generator.h>
#include "ThreadPool.h"


ThreadPool::~ThreadPool() {

    for (int i = 0; i < m_maxThreads; ++i) {
        delete m_ptrQueueArr[i];
        delete m_ptrMutexArr[i];
    }

    delete m_poolThread;
    free(m_ptrMutexArr);
    free(m_ptrQueueArr);

}


void ThreadPool::work(std::vector<std::string> *queue, std::mutex *queueLock) {
    bool localStop = false;
    std::string workString;
    while (!localStop) {
        queueLock->lock();
        if (!queue->empty()) {
            workString = queue->at(queue->size() - 1);
            queue->pop_back();
            queueLock->unlock();
            generateKeyPair(m_prtContext, workString);
        } else {
            if (m_finishMut.try_lock()) {
                if (m_finishVal)
                    localStop = true;
                m_finishMut.unlock();
            }
            queueLock->unlock();
        }
    }
//    printf("%p out\n", std::this_thread::get_id());
}

void ThreadPool::endWork() {
    m_finishMut.lock();
    m_finishVal = true;
    m_finishMut.unlock();

    joinThread();
}

void ThreadPool::sendWork(std::string &&line) {
    int i=0;
    bool workSended = false;
    while (!workSended) {
        m_ptrMutexArr[i]->lock();
        if (m_ptrQueueArr[i]->size() <= 250000) {
            m_ptrQueueArr[i]->emplace_back(line);
            workSended = true;
        }
//            printf("queue size of %d : %d\n", i,ptrQueueArr[i]->size());
        m_ptrMutexArr[i]->unlock();
        i = (i + 1) % m_maxThreads;
    }
}

void ThreadPool::joinThread() {
    for (int i = 0; i < m_maxThreads; ++i) {
        m_poolThread[i].join();
    }
}

ThreadPool::ThreadPool(secp256k1_context *prtContext) {
    unsigned int umaxThreads = std::thread::hardware_concurrency();
    m_maxThreads = int(umaxThreads);
    m_finishVal = false;
    m_prtContext = prtContext;
    m_poolThread = new std::thread[m_maxThreads];
    m_ptrQueueArr = (std::vector<std::string> **)malloc(m_maxThreads* sizeof(std::vector<std::string> *));
    m_ptrMutexArr = (std::mutex **)malloc(m_maxThreads* sizeof(std::mutex *));

    for (int i = 0; i < m_maxThreads; ++i) {
        m_ptrQueueArr[i] = new std::vector<std::string>();
        m_ptrMutexArr[i] = new std::mutex();
    }

    for (int i = 0; i < m_maxThreads; ++i) {
        m_poolThread[i] = std::thread(&ThreadPool::work,this, m_ptrQueueArr[i], m_ptrMutexArr[i]);
    }
}
