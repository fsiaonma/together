SRC_DIR= src/
CFLAGS+=-Wall -g 
CFLAGS+=$(addprefix -I, $(SRC_DIR))
CFILES=$(shell find $(SRC_DIR) -maxdepth 6 -name "*.cpp")
OBJS=$(CFILES:%.cpp=%.o)

CCFILES=$(shell find $(SRC_DIR) -maxdepth 6 -name "*.cc")
CCOBJS=$(CCFILES:%.cc=%.o)

LIBS+= -lmysqlclient -lprotobuf
TARGET = ./build/server

all:$(TARGET)

-include $(addsuffix /*.d, $(SRC_DIR))

$(TARGET):$(OBJS) $(CCOBJS)
	g++ $(LDFLAGS) $^ -o $@ $(LIBS)

$(OBJS):%.o:%.cpp
	g++ -c $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -o $@ -std=c++11  $<

$(CCOBJS):%.o:%.cc
	g++ -c $(CCFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -o $@  $<

clean:
	find $(SRC_DIR) -name "*.d" | xargs rm -f
	find $(SRC_DIR) -name "*.o" | xargs rm -f

cleanall:clean
	rm -f $(TARGET)

upload:cleanall
	find ./ -name *~ | xargs rm -f
	find ./ * | xargs chmod 777