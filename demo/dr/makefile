DR = ../../src/util/dr

all: linListDemo

linListDemo: linListDemo.o
	g++ linListDemo.o -o linListDemo
linListDemo.o: linListDemo.cpp $(DR)/linList.h
	g++ -c linListDemo.cpp -o linListDemo.o

clean:
	rm ./*.o