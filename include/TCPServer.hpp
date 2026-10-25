#include<sys/socket.h> //listen, accept,socket,bind
#include<netinet/in.h> //sockaddr_in, htons
#include<unistd.h> //close
#include<stdexcept> //std::runtime_error
#include "WorkQueue.hpp"
#define PORT 8080
class TCPServer{
    WorkQueue &workqueue;
    int server_fd;
    struct sockaddr_in serv_addr;
    public:
    TCPServer(WorkQueue&wq):workqueue(wq){
        //socket(domain,type,protocol) returns file descriptor or -1 on error
        if((server_fd=socket(AF_INET,SOCK_STREAM,0))<0){
            throw std::runtime_error("Server creation failed.\n");
        }
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=INADDR_ANY;
        serv_addr.sin_port=htons(PORT);
        if(bind(server_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
            throw std::runtime_error("Server Bind Failed.\n");
        }
        if(listen(server_fd,10)<0){
            throw std::runtime_error("Listening to the port failed.\n");
        }
    }
    ~TCPServer(){
        close(server_fd);
    }
    void listen_and_serve(){
        while(1){
            int sockfd;
            struct sockaddr_in client_addr;
            socklen_t client_len=sizeof(client_addr);
            sockfd=accept(server_fd,(struct sockaddr*)&client_addr,&client_len);
            if(sockfd<0){
                continue;
            }else{
                std::vector<uint8_t>buf(1024);
                int n;
                if((n=recv(sockfd,buf.data(),1024,0))<=0){
                    close(sockfd);
                    continue;
                }else buf.resize(n);
                WorkItem w;
                w.client_fd=sockfd;
                w.data=buf;
                w.sender=client_addr;
                w.protocol=Protocol::TCP;
                workqueue.push(w);
                //write
            }
        }
    }
};