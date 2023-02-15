#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>
#include <WinSock2.h>	// WinSock�p
#include <iostream>
#include<string>
#include<vector>
#include<set>
#include <algorithm>
#pragma comment( lib, "ws2_32.lib" )

const unsigned short PORT = 8080;	// �T�[�o�̃|�[�g�ԍ�
const char* SERVER_IP_ADDRESS = "127.0.0.1";
std::string message = "";
bool flag = false;


int main()
{
	std::cout << "Client" << std::endl;

	// WinSock�̏�����	WSAStartup()
	WSADATA  wsaData;

	// WinSock2.2 ����������
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		// �G���[����
	}

	SOCKET  sock;

	// UDP�\�P�b�g�̍쐬
	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		// �G���[
	}
	//�m���u���b�L���O�\�P�b�g�ɐݒ�
	u_long arg = 0x01;
	ioctlsocket(sock, FIONBIO, &arg);

	// �T�[�o�̃A�h���X���Z�b�g
	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));							// 0�N���A�ŏ�����
	serverAddr.sin_family = AF_INET;									// IPv4�A�h���X�g�p
	serverAddr.sin_port = htons(PORT);									// �|�[�g�ԍ��w��
	inet_pton(AF_INET, SERVER_IP_ADDRESS, &serverAddr.sin_addr.s_addr);


	// �펞�ғ��Ŗ������[�v
	while (true)
	{
		char buff[1024] = "";
		char ipAddr[256] = "";
		int ret;


		//��M��
		SOCKADDR_IN fromAddr;
		int fromlen = sizeof(fromAddr);

		//�������IP�A�h���X����M
		ret	= recvfrom(sock, (char*)&buff, sizeof(buff), 0, (sockaddr*)&fromAddr, &fromlen);
		ret = recvfrom(sock, (char*)&ipAddr, sizeof(ipAddr), 0, (sockaddr*)&fromAddr, &fromlen);

		if (ret == SOCKET_ERROR)
		{
			// �G���[����
		}

		//���`���ĕ\��
		message.append(ipAddr);
		message.append(":");
		message.append(buff);
		message.append("\r\n");
		std::cout << message << std::endl;
		message = "";


		//���M��
		std::cin >> buff;
		ret = sendto(sock, (char*)&buff, sizeof(buff), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

	}


	// UDP�\�P�b�g�j��
	closesocket(sock);
	// WinSock�I������
	WSACleanup();
	return 0;
}