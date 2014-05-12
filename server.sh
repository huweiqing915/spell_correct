#!bin/bash
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
