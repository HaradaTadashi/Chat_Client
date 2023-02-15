#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>
#include <WinSock2.h>	// WinSock用
#include <iostream>
#include<string>
#include<vector>
#include<set>
#include <algorithm>
#pragma comment( lib, "ws2_32.lib" )

const unsigned short PORT = 8080;	// サーバのポート番号
const char* SERVER_IP_ADDRESS = "127.0.0.1";
std::string message = "";
bool flag = false;


int main()
{
	std::cout << "Client" << std::endl;

	// WinSockの初期化	WSAStartup()
	WSADATA  wsaData;

	// WinSock2.2 初期化処理
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		// エラー処理
	}

	SOCKET  sock;

	// UDPソケットの作成
	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		// エラー
	}
	//ノンブロッキングソケットに設定
	u_long arg = 0x01;
	ioctlsocket(sock, FIONBIO, &arg);

	// サーバのアドレス情報セット
	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));							// 0クリアで初期化
	serverAddr.sin_family = AF_INET;									// IPv4アドレス使用
	serverAddr.sin_port = htons(PORT);									// ポート番号指定
	inet_pton(AF_INET, SERVER_IP_ADDRESS, &serverAddr.sin_addr.s_addr);


	// 常時稼働で無限ループ
	while (true)
	{
		char buff[1024] = "";
		char ipAddr[256] = "";
		int ret;


		//受信部
		SOCKADDR_IN fromAddr;
		int fromlen = sizeof(fromAddr);

		//文字列とIPアドレスを受信
		ret	= recvfrom(sock, (char*)&buff, sizeof(buff), 0, (sockaddr*)&fromAddr, &fromlen);
		ret = recvfrom(sock, (char*)&ipAddr, sizeof(ipAddr), 0, (sockaddr*)&fromAddr, &fromlen);

		if (ret == SOCKET_ERROR)
		{
			// エラー処理
		}

		//整形して表示
		message.append(ipAddr);
		message.append(":");
		message.append(buff);
		message.append("\r\n");
		std::cout << message << std::endl;
		message = "";


		//送信部
		std::cin >> buff;
		ret = sendto(sock, (char*)&buff, sizeof(buff), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

	}


	// UDPソケット破棄
	closesocket(sock);
	// WinSock終了処理
	WSACleanup();
	return 0;
}