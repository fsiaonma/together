BUILD_PATH = ./build

DR_PATH = src/util/dr
DR_DEMO_PATH = demo/dr
DR_DEMO_B_PATH = $(BUILD_PATH)/demo/dr

EAGLEMYSQL_PATH = src/util/eagleMysql
EAGLEMYSQL_DEMO_PATH = demo/eagleMysql
EAGLEMYSQL_DEMO_B_PATH = $(BUILD_PATH)/demo/eagleMysql

SERVER_PATH = $(BUILD_PATH)/server


all: $(DR_DEMO_B_PATH)/linListDemo $(EAGLEMYSQL_DEMO_B_PATH)/eagleMysqlDemo

# dr linList demo
$(DR_DEMO_B_PATH)/linListDemo: $(DR_DEMO_B_PATH)/linListDemo.o
	g++ $(DR_DEMO_B_PATH)/linListDemo.o -o $(DR_DEMO_B_PATH)/linListDemo
$(DR_DEMO_B_PATH)/linListDemo.o: $(DR_DEMO_PATH)/linListDemo.cpp $(DR_PATH)/linList.h
	g++ -c $(DR_DEMO_PATH)/linListDemo.cpp -o $(DR_DEMO_B_PATH)/linListDemo.o

# eagleMysql demo
$(EAGLEMYSQL_DEMO_B_PATH)/eagleMysqlDemo: $(EAGLEMYSQL_DEMO_B_PATH)/eagleMysqlDemo.o $(EAGLEMYSQL_DEMO_B_PATH)/eagleMysql.o
	g++ -o $(EAGLEMYSQL_DEMO_B_PATH)/eagleMysqlDemo $(EAGLEMYSQL_DEMO_B_PATH)/eagleMysqlDemo.o $(EAGLEMYSQL_DEMO_B_PATH)/eagleMysql.o -lmysqlclient
$(EAGLEMYSQL_DEMO_B_PATH)/eagleMysqlDemo.o: $(EAGLEMYSQL_DEMO_PATH)/eagleMysqlDemo.cpp $(EAGLEMYSQL_PATH)/eagleMysql.h
	g++ -c $(EAGLEMYSQL_DEMO_PATH)/eagleMysqlDemo.cpp -o $(EAGLEMYSQL_DEMO_B_PATH)/eagleMysqlDemo.o
$(EAGLEMYSQL_DEMO_B_PATH)/eagleMysql.o: $(EAGLEMYSQL_PATH)/eagleMysql.cpp $(EAGLEMYSQL_PATH)/eagleMysql.h
	g++ -c $(EAGLEMYSQL_PATH)/eagleMysql.cpp -o $(EAGLEMYSQL_DEMO_B_PATH)/eagleMysql.o

clean:
	rm $(DR_DEMO_B_PATH)/*.o && rm $(EAGLEMYSQL_DEMO_B_PATH)/*.o