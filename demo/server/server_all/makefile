s:timer.o ss.o user.o global.o log.o
	g++ -o s timer.o ss.o user.o global.o log.o
ss.o:ss.cpp s.h log.cpp log.h global.cpp global.h
	g++ -c ss.cpp
user.o:user.cpp user.h global.cpp global.h
	g++ -c user.cpp
timer.o:timer.cpp timer.h log.cpp log.h
	g++ -c timer.cpp
log.o:log.cpp log.h
	g++ -c log.cpp
global.o:global.cpp global.h const.h
	g++ -c global.cpp
clean:
	rm -f *.o
cleanall:
	rm -f *.o s
