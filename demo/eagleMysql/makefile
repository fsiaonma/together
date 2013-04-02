EAGLEMYSQL_PATH = ../../src/util/eagleMysql

all: eagleMysqlDemo

eagleMysqlDemo: eagleMysqlDemo.o eagleMysql.o
	g++ -o eagleMysqlDemo eagleMysqlDemo.o eagleMysql.o -lmysqlclient
eagleMysqlDemo.o: eagleMysqlDemo.cpp $(EAGLEMYSQL_PATH)/eagleMysql.h
	g++ -c eagleMysqlDemo.cpp -o eagleMysqlDemo.o
eagleMysql.o: $(EAGLEMYSQL_PATH)/eagleMysql.cpp $(EAGLEMYSQL_PATH)/eagleMysql.h
	g++ -c $(EAGLEMYSQL_PATH)/eagleMysql.cpp -o $(EAGLEMYSQL_DEMO_B_PATH)/eagleMysql.o

clean:
	rm ./*.o