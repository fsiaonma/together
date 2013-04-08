sessionDemo: sessionDemo.o tool.o session.o
	g++ -o sessionDemo sessionDemo.o tool.o session.o
sessionDemo.o: ./sessionDemo.cpp ../../src/lib/session/session.cpp ../../src/lib/session/session.h 
	g++ -c ./sessionDemo.cpp
session.o: ../../src/lib/session/session.cpp ../../src/lib/session/session.h ../../src/util/tool/tool.h
	g++ -c ../../src/lib/session/session.cpp
tool.o: ../../src/util/tool/tool.cpp ../../src/util/tool/tool.h
	g++ -c ../../src/util/tool/tool.cpp

clean:
	rm ./*.o