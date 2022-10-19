#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
using namespace std;

int main(){
    //创建socket
    int fd;
    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1){
        perror("socket");
        exit(0);
    }
    //初始化有服务端ip 和 端口的 addr
    sockaddr_in caddr;
    caddr.sin_family = AF_INET;
    caddr.sin_port = htons(9999);
    string ip = "127.0.0.1";
    inet_pton(AF_INET,&ip[0],&caddr.sin_addr.s_addr);
    //连接服务端

    int ret = connect(fd,(sockaddr *)&caddr,sizeof(caddr));
    if(ret == -1){
        perror("connect");
        exit(-1);
    }
    while(1){
        string str;
        cin >> str;
        ret = write(fd,&str[0],sizeof(str));
        if(ret == -1){
            perror("write");
            exit(0);
        }
        else if(ret == 0){
            cout << "缓存满，请稍等" <<endl;
        }
        char buf[1024] = {0};
        ret = read(fd,buf,sizeof(buf));
        if(ret == -1){
            perror("read");
            exit(-1);
        }
        else if(ret == 0){
            cout << "服务端已关闭" <<endl;
        }
        else{
            cout << buf <<endl;
        }
        
    }
    
    close(fd);
    return 0;
}