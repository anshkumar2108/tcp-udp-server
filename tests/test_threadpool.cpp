#include"WorkQueue.hpp"
#include"ThreadPool.hpp"

int main(){
    WorkQueue wq;
    ThreadPool pool(wq);
    for(int i=0;i<50;i++){
        WorkItem w;
        w.protocol=Protocol::TCP;
        wq.push(w);
        WorkItem q;
        q.protocol=Protocol::UDP;
        wq.push(q);
    }
    pool.shutdown();
}