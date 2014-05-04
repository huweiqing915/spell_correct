<?php 
	
	$client_fd = socket_create ( AF_INET, SOCK_DGRAM, SOL_UDP);
	if(!$client_fd)
	{
		die("Unable to create client socket!");
	}
	$host = "127.0.0.1";
	$port = "6688";
	$send_buf = $_REQUEST["search_content"];
	set_time_limit(0);
	$len = strlen($send_buf);
	$bytes_sent = socket_sendto($client_fd, $send_buf, $len, 0, $host, $port);
	if($bytes_sent == -1)
	{
		die("Send to server error");
	}

	$recv_buf = "";
	$from = "";
	$port1 = 0;
	$bytes_recv = socket_recvfrom($client_fd, $recv_buf, 65535, 0, $from, $port1);
	if ($bytes_recv == -1) 
	{
		die("Receive from server error");
	}

	echo trim($recv_buf)."\n";//去掉接受到的字符串的首尾空格，返回给post请求的data

//	echo "Received $recv_buf from remote address $from and remote port $port1<br\>"
	socket_close($client_fd);
?>




