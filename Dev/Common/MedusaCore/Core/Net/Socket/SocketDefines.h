#pragma once
#include "MedusaCorePreCompiled.h"

MEDUSA_BEGIN;

namespace Socket
{
	//ʹ�õ�Э��������
	namespace SocketAddressFamily
	{
		enum SocketAddressFamily_t
		{
			TCPIP=AF_INET,
			Unix=AF_UNIX
		};
	}
	

	//����ģʽ
	namespace SocketType
	{
		enum SocketType_t
		{
			TCP=SOCK_STREAM,
			UDP=SOCK_DGRAM
		};
	}
	

	//Э������
	namespace SocketProtocolType
	{
		enum SocketProtocolType_t
		{
			TCP=IPPROTO_TCP,
			UDP=IPPROTO_UDP
		};
	}
	
		 

	//���ݴ���״̬
	/*
	Success �ɹ���������
	PartAll	�����˲��ֻ�����ȫ�������� >0
	Fault	ʧ�� -1 <0
	Interrupt	�жϴ���
	ConnectFault	�������ӳ���������(�Է��Ѿ��ر�������).
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
	

	//�׽���ͨ��
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
