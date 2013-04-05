#include <stdio.h>    
#include <stdlib.h>  
#include <sys/types.h>    
#include <sys/socket.h>    
#include <netinet/in.h>    
#include <arpa/inet.h>    
#include <string.h>  
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h> 
#include <ctype.h>


#define STR_VALUE(val) #val
#define STR(name) STR_VALUE(name)

#define PATH_LEN 256
#define MD5_LEN 32
  
#define BUFFER_SIZE 1024


#define copy_str(dst, src) strncpy(dst, src, strlen(src) + 1)
#define write_to_header(string_to_write) copy_str(buf + strlen(buf), string_to_write)


int CalcFileMD5(char *file_name, char *md5_sum)
{
    #define MD5SUM_CMD_FMT "md5sum %." STR(PATH_LEN) "s 2>/dev/null"
    char cmd[PATH_LEN + sizeof (MD5SUM_CMD_FMT)];
    sprintf(cmd, MD5SUM_CMD_FMT, file_name);
    #undef MD5SUM_CMD_FMT

    FILE *p = popen(cmd, "r");
    if (p == NULL) return 0;

    int i, ch;
    for (i = 0; i < MD5_LEN && isxdigit(ch = fgetc(p)); i++) {
        *md5_sum++ = ch;
    }

    *md5_sum = '\0';
    pclose(p);
    return i == MD5_LEN;
}

void str_server(int sock, char *filename) 
{ 
    char buf[1025]; 
    // const char* filename = "/file/t.bmp"; 
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
		printf("%d\n", errno);
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
	if (argc < 4)
	{
		printf("enter port md5 filename\n");
		exit(0);
	}   
	char *port = argv[1];
    char *m = argv[2];
    char *fileName = argv[3];

    struct stat ss;
    if( stat( fileName, &ss ) == -1 )
    {
        return ;
    }
    int fileSize = ss.st_size - 1;

    char md5[MD5_LEN + 1];
    strcpy(md5, m);

    int cc = 0;
    int n = fileSize;
    for (; n > 0; n = n / 10)
        cc++;
    printf("len %d\n", cc);
    int contentLength = 10 + cc + 5 + 32;

    char *p = strstr(fileName, ".");
    char suffix[10];
    if (p == 0)
        suffix[0] = 0;
    else
        strncpy(suffix, p, strlen(p) + 1);
    printf("suffix %s\n", suffix);
    int suffix_len = strlen(suffix);
    char *suffix_data;
    if (suffix_len > 0)
    {
        suffix_data = "&suffix=";
        contentLength = contentLength + 8 + suffix_len;
    } else {
        suffix_data = "\0";
    }

    char f[50];
    strncpy(f, md5, MD5_LEN + 1);
    strncpy(f + strlen(f), suffix, strlen(suffix) + 1);
    printf("file name :%s\n", f);


    

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
            }  else if(strcmp(buf,"server")==0)  
            {  
                // char *temp = 
                // "POST /USER HTTP/1.1\n"
                // "Host: kc123kc.vicp.cc:9080\n"
                // "Connection: keep-alive\n"
                // "Content-Length: 54\n"
                // "Accept-Charset: GBK,utf-8;q=0.7,*;q=0.3\n"
                // "\n"
                // "file_size=4500053&md5=cefcb8e6d025249ad9156f30c0c7fe8c\0"; 

            sprintf(buf,
                "POST /UPLOAD HTTP/1.1\n"
                "Host: kc123kc.vicp.cc:9080\n"
                "Connection: keep-alive\n"
                "Content-Length: %d\n"
                "Accept-Charset: GBK,utf-8;q=0.7,*;q=0.3\n"
                "\n"
                "file_size=%d&md5=%s%s%s\0"
                , contentLength, fileSize, md5, suffix_data, suffix);
                // strcpy(buf, temp);
            }

            send(client_sockfd,buf,strlen(buf),0);
            str_server(client_sockfd, fileName);


            // 接收服务器端信息   
            len=recv(client_sockfd,buf,BUFFER_SIZE,0); 

            buf[len] = 0;
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
