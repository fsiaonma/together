BUILD_DIR = ./build

DR_DEMO_DIR = $(BUILD_DIR)/demo/dr

# dr linList demo
$(DR_DEMO_DIR)/linListDemo: $(DR_DEMO_DIR)/linListDemo.o
	g++ $(DR_DEMO_DIR)/linListDemo.o -o $(DR_DEMO_DIR)/linListDemo
$(DR_DEMO_DIR)/linListDemo.o: demo/dr/linListDemo.cpp src/util/dr/linList.h
	g++ -c demo/dr/linListDemo.cpp -o $(DR_DEMO_DIR)/linListDemo.o

clean:
	rm $(DR_DEMO_DIR)/*.o