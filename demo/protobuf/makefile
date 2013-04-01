LIBS=-lprotobuf
CC=g++
ARGS=-Wall -c

all:writer reader

reader:read.o user.pb.o global.pb.o
	$(CC) $^ $(LIBS) -o $@
read.o:read.cpp ./user.pb.h
	$(CC) $(ARGS) read.cpp -o $@
writer:write.o user.pb.o global.pb.o
	$(CC) $^ $(LIBS) -o $@
write.o:write.cpp ./user.pb.h
	$(CC) $(ARGS) write.cpp -o $@
user.pb.o:./user.pb.cc ./user.pb.h
	$(CC) $(ARGS) ./user.pb.cc -o $@
global.pb.o:./global.pb.cc ./global.pb.h
	$(CC) $(ARGS) ./global.pb.cc -o $@
clean:
	rm *.o -f
cleanall:
	rm *.o writer *.log reader -f
