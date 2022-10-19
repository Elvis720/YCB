#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<sstream>
#include <netinet/tcp.h>  
#include <sys/types.h>          
#include <sys/socket.h>

using namespace std;

string fun(const char * buffer,int size);
int main(){
    //创建用于监听的socket 文件
    int lfd;
    lfd = socket(AF_INET,SOCK_STREAM,0);
    if(lfd == -1){
        perror("socket");
        exit(-1);
    }
    //设置端口复用 
    int opt1 = 1;
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt1,sizeof(opt1));
    //关闭 nagle 算法
    cout << "是否启用Nagle算法：0.YES 1.NO (请输入序号)" <<endl;
    int nagle;
    cin >>nagle;
    if(nagle==0){
        cout << "开启" <<endl;
    }
    else{
        cout << "关闭" <<endl;
    }
    //int opt2 = (nagle !=1);//0开启，1关闭
    setsockopt(lfd,IPPROTO_TCP,TCP_NODELAY,&nagle,sizeof(nagle));
    //绑定
    sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = 0;
    saddr.sin_port = ntohs(9999);
    int ret = bind(lfd,(sockaddr *)&saddr,sizeof(saddr));
    if(ret == -1){
        perror("bind");
        exit(-1);
    }
    //监听
    ret = listen(lfd,6);
    if(ret == -1){
        perror("listen");
        exit(-1);
    }
    //接收
    int cfd;
    sockaddr_in clientaddr;
    socklen_t len = sizeof(clientaddr);
    cfd = accept(lfd,(sockaddr *)&clientaddr,&len);
    if(cfd == -1){
        perror("accept");
        exit(-1);
    }
    //打印客户端信息
    char ip[16];
    inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr,ip,16);
    cout << "client:ip:"<<ip << endl;
    cout << "client:port:"<<ntohs(clientaddr.sin_port) << endl;
    //
    //读写；
    while(1){
        char buffer[1024] = {0};
        ret = read(cfd,buffer,sizeof(buffer));
        if(ret == -1){
            perror("read");
            exit(-1);
        }else if(ret >0){
            cout << buffer << endl;
        }
        else{
            //ret == 0 //客服端断开连接
            cout << "client close" << endl;
        }
        string ans = fun(buffer,sizeof(buffer));
        ret = write(cfd,&ans[0],strlen(&ans[0]));
        if(ret == -1){
            perror("write");
            exit(0);
        }
    }
    

    //
    
    close(cfd);
    close(lfd);
    return 0;
}

string fun(const char * buffer,int size){
    string ans;
    string a,b;
    int A,B;
    stringstream sstr;
    int i = 0;
    //取到a,b的值
    while(isdigit(*(buffer+i)) && i < size){
        a += *(buffer+i);
        i++;
    }
    sstr << a;sstr>>A;
    sstr.clear();

    //第一个非数字字符不是 + ，直接返回 “0”; 
    if(*(buffer+i) != '+'){
        return "0";
    }
    
    i++;

    while(isdigit(*(buffer+i)) && i < size){
        b += *(buffer+i);
        i++;
    }
    sstr<<b;sstr>>B;
    sstr.clear();
    
    
    int C = A +B;
   
    sstr << C;
    sstr >> ans;
    return ans;
}