BUILD_PATH = ./build

DR_DEMO_PATH = $(BUILD_PATH)/demo/dr
EAGLEMYSQL_DEMO_PATH = $(BUILD_PATH)/demo/eagleMysql

# dr linList demo
$(DR_DEMO_PATH)/linListDemo: $(DR_DEMO_PATH)/linListDemo.o
	g++ $(DR_DEMO_PATH)/linListDemo.o -o $(DR_DEMO_PATH)/linListDemo
$(DR_DEMO_PATH)/linListDemo.o: demo/dr/linListDemo.cpp src/util/dr/linList.h
	g++ -c demo/dr/linListDemo.cpp -o $(DR_DEMO_PATH)/linListDemo.o

# eagleMysql demo
$(EAGLEMYSQL_DEMO_PATH)/eagleMysqlDemo: $(EAGLEMYSQL_DEMO_PATH)/eagleMysqlDemo.o $(EAGLEMYSQL_DEMO_PATH)/eagleMysql.o
	g++ -o $(EAGLEMYSQL_DEMO_PATH)/eagleMysqlDemo $(EAGLEMYSQL_DEMO_PATH)/eagleMysqlDemo.o $(EAGLEMYSQL_DEMO_PATH)/eagleMysql.o -lmysqlclient
$(EAGLEMYSQL_DEMO_PATH)/eagleMysqlDemo.o: demo/eagleMysql/eagleMysqlDemo.cpp src/util/eagleMysql/eagleMysql.h
	g++ -c demo/eagleMysql/eagleMysqlDemo.cpp -o $(EAGLEMYSQL_DEMO_PATH)/eagleMysqlDemo.o
$(EAGLEMYSQL_DEMO_PATH)/eagleMysql.o: src/util/eagleMysql/eagleMysql.cpp src/util/eagleMysql/eagleMysql.h
	g++ -c src/util/eagleMysql/eagleMysql.cpp -o $(EAGLEMYSQL_DEMO_PATH)/eagleMysql.o

clean:
	rm $(DR_DEMO_PATH)/*.o