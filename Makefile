DIR := .
SRC_DIR:=./Src/Server/
INCLUDE_DIR:=./Include
MAIN:=$(DIR)/Bin/server.exe
OBJS:=$(SRC_DIR)main.cpp $(SRC_DIR)Thread.cpp $(SRC_DIR)WorkThread.cpp $(SRC_DIR)ThreadPool.cpp $(SRC_DIR)UDPServer.cpp $(SRC_DIR)Task.cpp $(SRC_DIR)SpellCorrect.cpp
$(MAIN):$(OBJS) 
	g++ -g -o $@ $(OBJS) -lpthread -ljson -I$(INCLUDE_DIR)
