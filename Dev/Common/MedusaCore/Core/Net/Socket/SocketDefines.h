#pragma once
#include "MedusaCorePreCompiled.h"

MEDUSA_BEGIN;

namespace Socket
{
	//使用的协议族类型
	namespace SocketAddressFamily
	{
		enum SocketAddressFamily_t
		{
			TCPIP=AF_INET,
			Unix=AF_UNIX
		};
	}
	

	//传输模式
	namespace SocketType
	{
		enum SocketType_t
		{
			TCP=SOCK_STREAM,
			UDP=SOCK_DGRAM
		};
	}
	

	//协议类型
	namespace SocketProtocolType
	{
		enum SocketProtocolType_t
		{
			TCP=IPPROTO_TCP,
			UDP=IPPROTO_UDP
		};
	}
	
		 

	//数据传输状态
	/*
	Success 成功传输数据
	PartAll	传输了部分或者是全部的数据 >0
	Fault	失败 -1 <0
	Interrupt	中断错误
	ConnectFault	网络连接出现了问题(对方已经关闭了连接).
	*/
	namespace SocketError
	{
		enum SocketError_t
		{
			Success=0,
			Fault=-1,
			Interrupt=EINTR,
			ConnectFault=EPIPE,
			Timeout=-2,


		};
	}
	

	//套接字通道
	namespace SocketPipeType
	{
		enum SocketPipeType_t
		{
			Read=0,
			Write=1,
			ReadWrite=2
		};

	}
	
}

MEDUSA_END;
