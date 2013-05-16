#include <stdio.h>    
#include <sys/types.h>    
#include <sys/socket.h>    
#include <netinet/in.h>    
#include <arpa/inet.h>    
#include <string.h>  
#include <stdlib.h>  
#include <time.h> 
  
#define BUFFER_SIZE 40000

void printNowTime()
{
time_t t = time(NULL);
struct tm *lt = localtime(&t);
printf("(%d:%d:%d)", lt->tm_hour, lt->tm_min, lt->tm_sec);
} 
      
    int main(int argc, char *argv[])     
    {     
        int client_sockfd;     
        int len;  
	if (argc < 2)
	{
		printf("enter port\n");
		exit(0);
	}   
	char *port = argv[1];
        struct sockaddr_in remote_addr; // 服务器端网络地址结构体     
        char buf[BUFFER_SIZE];  // 数据传送的缓冲区     
        memset(&remote_addr,0,sizeof(remote_addr)); // 数据初始化--清零     
        remote_addr.sin_family=AF_INET; // 设置为IP通信     
        remote_addr.sin_addr.s_addr=inet_addr("127.0.0.1");// 服务器IP地址     
        remote_addr.sin_port=htons(atoi(port)); // 服务器端口号     
        // 创建客户端套接字--IPv4协议，面向连接通信，TCP协议   
        if((client_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)     
        {     
            perror("client socket creation failed");     
            exit(EXIT_FAILURE);
        }     
        // 将套接字绑定到服务器的网络地址上   
        if(connect(client_sockfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))<0)     
        {     
            perror("connect to server failed");     
            exit(EXIT_FAILURE);  
        }    
        // 循环监听服务器请求      
        while(1)  
        {  
            printf("Please input the message:");  
            scanf("%s",buf);  
            // exit  
            if(strcmp(buf,"exit")==0)  
            {  
                break;  
            } else if (strcmp(buf,"server")==0){
                #if 0
                char *temp = 
                "POST /USER HTTP/1.1\n"
                "Host: kc123kc.vicp.cc:9080\n"
                "Content-Length: 34\n"
                "Accept-Encoding: gzip\n"
                "Content-Type: application/x-www-form-urlencoded; charset=utf-8\n"
                "User-Agent: iReading 2.2 (iPad Simulator; iPhone OS 6.1; en_US)\n"
                "Connection: close\n"
                "\n"
                "suohi=kuangchao&shadiao=kuangchao2\0";
                #else
                char *temp = 
                "POST /USER HTTP/1.1\n"
                "Host: kc123kc.vicp.cc:9080\n"
                "Connection: keep-alive\n"
                "Content-Length: 43\n"
                "Accept-Charset: GBK,utf-8;q=0.7,*;q=0.3\n"
                "\n"
                "action=101&username=xianjh&password=123456\0";
                #endif
                strcpy(buf, temp);
            }
            send(client_sockfd,buf,strlen(buf),0);  
            // 接收服务器端信息   
            len=recv(client_sockfd,buf,BUFFER_SIZE,0); 
            buf[len] = 0;
		    printNowTime(); 
            printf("receive from server:%s\n",buf);  
            memset(buf, 0, BUFFER_SIZE);
            if(len<0)  
            {  
                perror("receive from server failed");  
                exit(EXIT_FAILURE);  
            }  
        }  
        close(client_sockfd);// 关闭套接字     
        return 0;  
    }  
