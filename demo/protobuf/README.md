protobuf demo
============

### protobuf 例子
### 安装protobuf
> 解压安装包后
> ./configure
> make
> make install
> ldconfig
### 编译、运行demo
> 在该目录下运行compileProto.sh和make
> ./writer (将数据序列化,保存在目录下的response.log)
> ./reader (读取目录下的response.log,解析)
### protobuf使用流程简要说明
> 先编写xx.proto,定义数据格式
> protoc -I=. --cpp_out=. ./xx.proto --proto_path=./ (编译proto文件)
> 然后会生成对应xx.pb.cc和xx.pb.h
> 在代码中引用xx.pb.h就可以使用
### protobuf相关资料
> Google Protocol Buffer 的使用和原理 http://www.ibm.com/developerworks/cn/linux/l-cn-gpb/
> Protocol Buffer技术详解(语言规范)  http://www.cnblogs.com/stephen-liu74/archive/2013/01/02/2841485.html

