#include<iostream>
#include<winsock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int main()
{
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "加载winsock.dll失败" << endl;
		return 0;
	}


	SOCKET sock_client;
	if ((sock_client = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout << "创建套接字失败，错误代码：" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}

	char ip[20];
	cout << "输入服务器ip地址：";
	cin >> ip;

	struct sockaddr_in server_addr;
	memset((void*)&server_addr,0,sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(65432);
	in_addr a;
	inet_pton(AF_INET,ip,&a); 
	server_addr.sin_addr.s_addr = a.S_un.S_addr;

	if (connect(sock_client, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) != 0)
	{
		cout << "connect连接失败，错误代码：" << WSAGetLastError() << endl;
		closesocket(sock_client);
		WSACleanup();
		return 0;
	}
	else
	{
		cout << "连接成功" << endl;
	}


	//结束处理
	closesocket(sock_client);
	WSACleanup();
	return 0;
}























