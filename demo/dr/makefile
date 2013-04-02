DR_PATH = ../../src/util/dr

all: linListDemo

linListDemo: linListDemo.o
	g++ $(DR_DEMO_B_PATH)/linListDemo.o -o linListDemo
linListDemo.o: linListDemo.cpp $(DR_PATH)/linList.h
	g++ -c linListDemo.cpp -o linListDemo.o

clean:
	rm ./*.o