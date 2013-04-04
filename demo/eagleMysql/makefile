EAGLEMYSQL = ../../src/util/eagleMysql
CONFIG = ../../src/common/config

all: eagleMysqlDemo

eagleMysqlDemo: eagleMysqlDemo.o eagleMysql.o config.o
	g++ -o eagleMysqlDemo eagleMysqlDemo.o eagleMysql.o config.o -lmysqlclient
eagleMysqlDemo.o: eagleMysqlDemo.cpp $(EAGLEMYSQL)/eagleMysql.h $(CONFIG)/config.h
	g++ -c eagleMysqlDemo.cpp -o eagleMysqlDemo.o
eagleMysql.o: $(EAGLEMYSQL)/eagleMysql.cpp $(EAGLEMYSQL)/eagleMysql.h
	g++ -c $(EAGLEMYSQL)/eagleMysql.cpp -o eagleMysql.o
config.o: $(CONFIG)/config.cpp $(CONFIG)/config.h
	g++ -c $(CONFIG)/config.cpp -o config.o

clean:
	rm ./*.o