DIR := .
SRC_DIR:=./Src/Server/
INCLUDE_DIR:=./Include
LIB_DIR:=./Lib
DATA_DIR:=./Data
MAIN:=$(DIR)/Bin/server.exe
OBJS:=$(SRC_DIR)main.cpp $(SRC_DIR)Config.cpp $(SRC_DIR)Thread.cpp $(SRC_DIR)WorkThread.cpp $(SRC_DIR)ThreadPool.cpp $(SRC_DIR)UDPServer.cpp $(SRC_DIR)Task.cpp $(SRC_DIR)SpellCorrect.cpp $(SRC_DIR)EncodingConverter.cpp $(SRC_DIR)CacheManageThread.cpp $(SRC_DIR)Log.cpp $(SRC_DIR)Cache.cpp $(SRC_DIR)Index.cpp
$(MAIN):$(OBJS) 
	g++ -g -o $@ $(OBJS) -lpthread -ljson -I$(INCLUDE_DIR) -I$(LIB_DIR) -DCPPJIEBA_GBK -DNDEBUG -std=c++11
