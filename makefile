SRC_DIR= src/
CFLAGS+=-Wall -g 
CFLAGS+=$(addprefix -I, $(SRC_DIR))
CFILES=$(shell find $(SRC_DIR) -maxdepth 6 -name "*.cpp")
OBJS=$(CFILES:%.cpp=%.o)
LIBS+= -lmysqlclient -lprotobuf
TARGET = ./build/server

all:$(TARGET) clean

-include $(addsuffix /*.d, $(SRC_DIR))

$(TARGET):$(OBJS)
	g++ $(LDFLAGS) $^ -o $@ $(LIBS)

$(OBJS):%.o:%.cpp
	g++ -c $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -o $@ $<

clean:
	find $(SRC_DIR) -name "*.d" | xargs rm -f
	find $(SRC_DIR) -name "*.o" | xargs rm -f

cleanall:clean
	rm -f $(TARGET)

upload:cleanall
	find ./ * | xargs chmod 777
