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

cmd:
	mkdir -p $(BUILD)/$(GLOBAL)
	mkdir -p $(BUILD)/$(CONST)
	mkdir -p $(BUILD)/$(SERVER)
	mkdir -p $(BUILD)/$(USER)
	mkdir -p $(BUILD)/$(DR)
	mkdir -p $(BUILD)/$(EAGLEMYSQL)
	mkdir -p $(BUILD)/$(LOG)
	mkdir -p $(BUILD)/$(TIMER)
