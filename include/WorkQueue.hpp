#pragma once
#include<netinet/in.h>
#include<vector>
#include<queue>
#include<mutex>
#include<condition_variable>
enum class Protocol{
    TCP,
    UDP,
    SHUTDOWN
};
struct WorkItem{
    int client_fd;
    sockaddr_in sender;
    std::vector<uint8_t> data;
    Protocol protocol;
};
class WorkQueue{
    private:
    std::queue<WorkItem>workbuffer;
    std::mutex mtx;
    std::condition_variable cv;
    public:
    void push(WorkItem item){
        std::unique_lock<std::mutex>uniquelock(mtx);//Locked upon construction
        workbuffer.push(item);
        uniquelock.unlock();
        cv.notify_one();
        //No need to unlock, automatically unlocks when goes out of scope.
    };
    WorkItem pop(){
        std::unique_lock<std::mutex>uniquelock(mtx);
        cv.wait(uniquelock,[this]{return !workbuffer.empty();});
        WorkItem item=workbuffer.front();
        workbuffer.pop();
        return item;
    };
    
};