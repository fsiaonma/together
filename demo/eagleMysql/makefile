EAGLEMYSQL = ../../src/util/eagleMysql

all: eagleMysqlDemo

eagleMysqlDemo: eagleMysqlDemo.o eagleMysql.o
	g++ -o eagleMysqlDemo eagleMysqlDemo.o eagleMysql.o -lmysqlclient
eagleMysqlDemo.o: eagleMysqlDemo.cpp $(EAGLEMYSQL)/eagleMysql.h
	g++ -c eagleMysqlDemo.cpp -o eagleMysqlDemo.o
eagleMysql.o: $(EAGLEMYSQL)/eagleMysql.cpp $(EAGLEMYSQL)/eagleMysql.h
	g++ -c $(EAGLEMYSQL)/eagleMysql.cpp -o eagleMysql.o

clean:
	rm ./*.o