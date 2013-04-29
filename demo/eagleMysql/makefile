EAGLEMYSQL = ../../src/util/eagleMysql

all: eagleMysqlDemo

eagleMysqlDemo: eagleMysqlDemo.o eagleMysql.o tool.o config.o
	g++ -o eagleMysqlDemo eagleMysqlDemo.o eagleMysql.o tool.o config.o -lmysqlclient
eagleMysqlDemo.o: eagleMysqlDemo.cpp $(EAGLEMYSQL)/eagleMysql.h
	g++ -c eagleMysqlDemo.cpp -o eagleMysqlDemo.o
eagleMysql.o: $(EAGLEMYSQL)/eagleMysql.cpp $(EAGLEMYSQL)/eagleMysql.h
	g++ -c $(EAGLEMYSQL)/eagleMysql.cpp -o eagleMysql.o
tool.o: ../../src/util/tool/tool.cpp ../../src/util/tool/tool.h
	g++ -c ../../src/util/tool/tool.cpp -o tool.o
config.o: ../../src/common/config/config.cpp ../../src/common/config/config.h
	g++ -c ../../src/common/config/config.cpp -o config.o

clean:
	rm -f ./*.o ./eagleMysqlDemo