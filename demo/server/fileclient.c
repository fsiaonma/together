#include <stdio.h>    
#include <sys/types.h>    
#include <sys/socket.h>    
#include <netinet/in.h>    
#include <arpa/inet.h>    
#include <string.h>  
#include <stdlib.h>  
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h> 
  
#define BUFFER_SIZE 1024

void str_server(int sock) 
{ 
    char buf[1025]; 
    const char* filename = "./t.bmp"; 
    FILE *file = fopen(filename, "rb"); 
    if (!file)
    {
        printf("Can't open file for reading"); 
        return;
    }
    while (!feof(file)) 
    { 
        int rval = fread(buf, 1, sizeof(buf), file); 
        if (rval < 1)
        {
            printf("Can't read from file");
            fclose(file);
            return;
        }

        int off = 0;
        do
        {
            int sent = send(sock, &buf[off], rval - off, 0);
            if (sent < 1)
            {
                // if the socket is non-blocking, then check
                // the socket error for WSAEWOULDBLOCK/EAGAIN
                // (depending on platform) and if true then
                // use select() to wait for a small period of
                // time to see if the socket becomes writable
                // again before failing the transfer...
		printf("%d", errno);
                if (errno != EAGAIN) {
                    printf("Can't write to socket");
                    fclose(file);
                    return;
                }
            }

            off += sent;
        }
        while (off < rval);
    } 

    fclose(file);
} 

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
            }  
            send(client_sockfd,buf,strlen(buf),0);
            str_server(client_sockfd);

            // FILE * fp = fopen(file_name, "rb");
            // char file_data[BUFFER_SIZE];
            // size_t nbytes;
            // int sent;
            // while ( (nbytes = fread(file_data, sizeof(char), BUFFER_SIZE, fp)) > 0)
            // {
            //     sent = send(client_sockfd, file_data, nbytes, 0);
            //     int offset = 0;
            //     while ((sent = send(client_sockfd, file_data + offset, nbytes, 0)) > 0
            //           || (sent == -1 && errno == EINTR) ) {
            //             if (sent > 0) {
            //                 offset += sent;
            //                 nbytes -= sent;
            //             }
            //     }
            // }
            // printf("---------%d\n", sent);
            // fclose(fp);

            // int readpos;
            // int fd = open(file_name, O_RDONLY);
            // while (1) {
            //     off_t offset = 0;
            //     int s = sendfile(client_sockfd, fd, &offset, total_length);
            //     readpos = offset;
            //     if (readpos == total_length) {
            //         // 读写完毕
            //         return;
            //     }
            // }
            // close(fd);
            // FILE * fp = fopen(file_name, "rb");
            // int numbytes;
            // int file_block_length = 0;
            // char buffer[BUFFER_SIZE];
            // while ((file_block_length = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0)
            // {
            //     if (send(client_sockfd, buffer, file_block_length, 0) < 0)
            //     {
            //         printf("Send File:\t%s Failed\n", file_name);
            //         break;
            //     }
            //     bzero(buffer, BUFFER_SIZE);
            // }
            // fclose(fp);

                //Sending file
    // while(!feof(fp)){
    //     numbytes = fread(buf, sizeof(char), sizeof(buf), fp);
    //     //printf("fread %d bytes, ", numbytes);
    //     numbytes = write(client_sockfd, buf, numbytes);
    //     bzero(buf, BUFFER_SIZE);
    //     //printf("Sending %d bytes\n",numbytes);
    // }

            //send(client_sockfd,buf,strlen(buf),0);  
            // 接收服务器端信息   
            len=recv(client_sockfd,buf,BUFFER_SIZE,0); 
		printNowTime(); 
            printf("receive from server:%s\n",buf);  
            if(len<0)  
            {  
                perror("receive from server failed");  
                exit(EXIT_FAILURE);  
            }  
        }  
        close(client_sockfd);// 关闭套接字     
        return 0;  
    }  
