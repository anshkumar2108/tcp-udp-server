#include<sys/socket.h> //listen, accept,socket,bind
#include<netinet/in.h> //sockaddr_in, htons
#include<unistd.h> //close
#include<stdexcept> //std::runtime_error
#include "WorkQueue.hpp"

class TCPServer{
    WorkQueue &workqueue;
    int server_fd;
    struct sockaddr_in serv_addr;
    public:
    TCPServer(WorkQueue&wq):workqueue(wq){
        if((server_fd=socket(AF_INET,SOCK_STREAM,0))<0){
            std::runtime_error("Server creation failed.\n");
            return;
        }
        

    }
    ~TCPServer(){
        close(server_fd);
    }
};