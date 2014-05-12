#########################################################################
# File Name: server.sh
# Author: huwq
# mail: huweiqing915@gmail.com
# Created Time: 2014年05月12日 星期一 19时28分33秒
#########################################################################
#!/bin/bash

echo "Current Work Directory:$PWD"

start()
{
	cd ./Bin
	./server.exe
}

stop()
{
	cd ./Bin
	killall -9 server.exe
}

stat()
{
	ps -ef | grep server.exe
}

restart()
{
	stop
	start
}

case $1 in
	start   ) start ;;
	stop    ) stop ;;
	stat    ) stat ;;
	restart ) restart;;
	*) echo "Input again.." ;;
esac

