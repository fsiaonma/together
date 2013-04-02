BUILD = ./build
SRC = ./src

GLOBAL = common/global
CONST = common

SERVER = core/server

USER = module/user

DR = util/dr
EAGLEMYSQL = util/eagleMysql
LOG = util/log
TIMER = util/timer

all: cmd $(BUILD)/$(SERVER)/server

cmd:
	mkdir -p $(BUILD)/$(GLOBAL)
	mkdir -p $(BUILD)/$(CONST)
	mkdir -p $(BUILD)/$(SERVER)
	mkdir -p $(BUILD)/$(USER)
	mkdir -p $(BUILD)/$(DR)
	mkdir -p $(BUILD)/$(EAGLEMYSQL)
	mkdir -p $(BUILD)/$(LOG)
	mkdir -p $(BUILD)/$(TIMER)

$(BUILD)/$(SERVER)/server: $(BUILD)/$(TIMER)/timer.o $(BUILD)/$(SERVER)/ss.o $(BUILD)/$(USER)/user.o $(BUILD)/$(GLOBAL)/global.o $(BUILD)/$(LOG)/log.o
	g++ -o $(BUILD)/$(SERVER)/server $(BUILD)/$(TIMER)/timer.o $(BUILD)/$(SERVER)/ss.o $(BUILD)/$(USER)/user.o $(BUILD)/$(GLOBAL)/global.o $(BUILD)/$(LOG)/log.o
$(BUILD)/$(SERVER)/ss.o: $(SRC)/$(SERVER)/ss.cpp $(SRC)/$(SERVER)/s.h $(SRC)/$(LOG)/log.cpp $(SRC)/$(LOG)/log.h $(SRC)/$(GLOBAL)/global.cpp $(SRC)/$(GLOBAL)/global.h
	g++ -c $(SRC)/$(SERVER)/ss.cpp -o $(BUILD)/$(SERVER)/ss.o
$(BUILD)/$(USER)/user.o: $(SRC)/$(USER)/user.cpp $(SRC)/$(USER)/user.h $(SRC)/$(GLOBAL)/global.cpp $(SRC)/$(GLOBAL)/global.h
	g++ -c $(SRC)/$(USER)/user.cpp -o $(BUILD)/$(USER)/user.o
$(BUILD)/$(TIMER)/timer.o: $(SRC)/$(TIMER)/timer.cpp $(SRC)/$(TIMER)/timer.h $(SRC)/$(LOG)/log.cpp $(SRC)/$(LOG)/log.h
	g++ -c $(SRC)/$(TIMER)/timer.cpp -o $(BUILD)/$(TIMER)/timer.o
$(BUILD)/$(LOG)/log.o: $(SRC)/$(LOG)/log.cpp $(SRC)/$(LOG)/log.h
	g++ -c $(SRC)/$(LOG)/log.cpp -o $(BUILD)/$(LOG)/log.o
$(BUILD)/$(GLOBAL)/global.o: $(SRC)/$(GLOBAL)/global.cpp $(SRC)/$(GLOBAL)/global.h $(SRC)/$(CONST)/const.h
	g++ -c $(SRC)/$(GLOBAL)/global.cpp -o $(BUILD)/$(GLOBAL)/global.o

clean: 
	find $(BUILD) -type f ! -name "*.md" | xargs rm -f
