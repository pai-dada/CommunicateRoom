#include<iostream>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include<thread>
#include<Windows.h>
#pragma warning(disable:4996)
using namespace std;


void sendMessage(SOCKET clientSock)
{
	while (1)
	{
		char buff[1024] = ("你好，我是服务器");
		send(clientSock, buff, sizeof(buff), 0);
		Sleep(1000);
	}
}

void rcvMessage(SOCKET clientSock)
{
	while (1)
	{
		cout << "等待接收信息" << endl;
		Sleep(1000);
	}
}

void MakeCommunicate(SOCKET clienSocket)
{
	thread send(sendMessage,clienSocket);
	thread rcv(rcvMessage,clienSocket);
}


int main()
{
	SOCKET sock_server;
	struct sockaddr_in addr, client_addr;
	int addr_len = sizeof(struct sockaddr_in);
	SOCKET newsock;

	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
	{
		cout << "加载winsock链接库失败" << endl;
		return 0;
	}
	sock_server = socket(AF_INET, SOCK_STREAM, 0);
	memset((void*)&addr, 0, addr_len);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(65432);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(sock_server, (struct sockaddr*)&addr, sizeof(addr));

	listen(sock_server, 5);
	cout << "listening..." << endl;


	while (1)
	{

		if ((newsock = accept(sock_server, (struct sockaddr*)&client_addr, &addr_len)) == INVALID_SOCKET)
		{
			cout << "accept函数调用失败,失败代码" << GetLastError() << endl;
		}
		else
		{
			cout << "收到一个来自" << inet_ntoa(client_addr.sin_addr) << "的连接请求" << endl;
			thread t1(MakeCommunicate, newsock);
			t1.detach();

		}

	}
	
	

}


//如何回收线程资源
