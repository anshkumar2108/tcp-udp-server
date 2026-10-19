#include<vector>
#include "WorkQueue.hpp"
#include<thread>
#define N 100
class ThreadPool{
    std::vector<std::thread>threadPool;
    WorkQueue& workqueue;
    void workerLoop(){
        while(true){
            WorkItem w=workqueue.pop();
            if(w.protocol==Protocol::SHUTDOWN){
                break;
            }
        }
    }
    public:
    ThreadPool(WorkQueue&wq):workqueue(wq){
        for(int i=0;i<N;i++){
            std::thread t(&ThreadPool::workerLoop,this);
            threadPool.push_back(std::move(t));
        }
    }
    void shutdown(){
        for(int i=0;i<N;i++){
            WorkItem w;
            w.protocol=Protocol::SHUTDOWN;
            workqueue.push(w);
        }
    }
    ~ThreadPool(){
        for(int i=0;i<N;i++){
            threadPool[i].join();
        }
    }
};