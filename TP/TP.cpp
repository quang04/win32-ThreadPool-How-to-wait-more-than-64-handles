// TP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "TP.h"



#define THREADPOOL_SIZE	10

DWORD WINAPI WaitThreadGroup(LPVOID lpParam)
{
    pStoreHandleStruct data = std::move(reinterpret_cast<pStoreHandleStruct>(lpParam));
    lpParam = nullptr;

    WaitForMultipleObjects(data->nQuantity, data->vectorStoreHandles.data(), TRUE, INFINITE);

    //When done delete
    delete data;

    return 0;
}

BOOL CreateTask(CTaskVector& tasks, const int& totalThread)
{
    if (totalThread <= 0) return FALSE;

    CTaskBase* pTask = nullptr;

    for (auto i = 0; i < totalThread; i++)
    {
        if (i % 2)
            pTask = new CTask1();
        else
            pTask = new CTask2();

        tasks.emplace_back(pTask);
    }

    return TRUE;
}

int main()
{
    int nRetCode = 0;

    std::cout << "TP" << std::endl;

    CThreadPool<CWorkerDummy> pool;
    CTaskVector tasks;

    //Init pool
    auto hr = pool.Initialize((void*)123, THREADPOOL_SIZE);

    //Vector stores all handle corresponding to each thread
    HandleVector vectorWaitAllThread;

    //Create 3000 threads and feed to the pool
    //Currently max is 64x64 thread
    const int& totalThreadCreate = 3000;

    //Vector wait for group handle
    HandleVector vectorWaitGroup;

    //Calculate group need
    int groupNeeded = totalThreadCreate / MAXIMUM_WAIT_OBJECTS;
    groupNeeded += (totalThreadCreate % MAXIMUM_WAIT_OBJECTS) == 0 ? 0 : 1;

    auto startTime = std::chrono::high_resolution_clock::now();

    if (SUCCEEDED(hr))
    {
        CTaskBase* pTask = nullptr;

        vectorWaitAllThread.reserve(totalThreadCreate);

        if (CreateTask(tasks, totalThreadCreate))
        {
            //feed to pool and store handle
            for (CTaskBase* p : tasks)
            {
                vectorWaitAllThread.emplace_back(p->GetWaitTaskCompleteEvent());
                pool.QueueRequest((CWorkerDummy::RequestType)p);
            }

            //store wait group
            for (auto j = 0; j < groupNeeded; j++)
            {
                //In order to pass struct to thread need allocate in heap
                pStoreHandleStruct pData = new StoreHandleStruct();
                const auto& beginPos = vectorWaitAllThread.begin() + (static_cast<INT64>(j) * MAXIMUM_WAIT_OBJECTS);

                if ((j + 1) < groupNeeded)
                    pData->nQuantity = MAXIMUM_WAIT_OBJECTS;
                else
                    pData->nQuantity = totalThreadCreate % MAXIMUM_WAIT_OBJECTS;

                pData->vectorStoreHandles.resize(pData->nQuantity);
                std::copy(beginPos,
                    beginPos + pData->nQuantity,
                    pData->vectorStoreHandles.begin());

                //Start thread group wait event
                HANDLE waitThradHandle = CreateThread(NULL, NULL, WaitThreadGroup, pData, 0, NULL);
                //Store handle
                vectorWaitGroup.emplace_back(waitThradHandle);
            }
        }

        //wait all thread in a pool complete
        WaitForMultipleObjects(static_cast<DWORD>(vectorWaitGroup.size()), vectorWaitGroup.data(), TRUE, INFINITE);

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::milliseconds>(endTime - startTime);
        std::cout << "Time: " << duration.count() << "ms" << std::endl;

        //Clean up tasks
        for (CTaskBase* e : tasks)
        {
            ASSERT(e != nullptr);
            delete e;
        }

        // Shutdown the thread pool
        pool.Shutdown();
    }
    else
    {
        std::cout << "Failed to init pool" << std::endl;
    }


    std::cout << "Press any key to close\n";
    std::getchar();
    return nRetCode;
}
