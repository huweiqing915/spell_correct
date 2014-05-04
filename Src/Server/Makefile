MAIN:=server.exe
OBJS:=main.cpp Thread.cpp WorkThread.cpp Task.cpp ThreadPool.cpp UDPServer.cpp TextQuery.cpp
$(MAIN):$(OBJS) MutexLock.h Condition.h Thread.h WorkThread.h Task.h ThreadPool.h UDPServer.h TextQuery.h
	g++ -g -o $@ $(OBJS) -lpthread -ljson
