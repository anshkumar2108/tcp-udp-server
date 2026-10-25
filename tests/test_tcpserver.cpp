#include"../include/TCPServer.hpp"
#include"../include/ThreadPool.hpp"
#include"../include/WorkQueue.hpp"
int main(){
    WorkQueue wq;
    ThreadPool pool(wq);
    TCPServer tcpserver(wq);
    tcpserver.listen_and_serve();
}