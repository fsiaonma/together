server demo
============

### 服务器例子
编译:
make
gcc -o client client.c
gcc -o fileclient fileclient.c

使用
运行./s
运行./client 9080 (注:用于处理HTTP请求,5秒后自动断开)
运行./fileclient 9081 (注:用于处理上传文件)
运行./client 9082 (注:用于处理长连接请求,不主动断开)
