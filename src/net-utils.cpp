#pragma once

/*
	Simple UDP Server
*/

#include <cstdio>
//#include<winsock2.h>

//#include <iostream>
#include "net-utils.h"

int TinyUDPServer()
{
	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	char buf[BUFLEN];

	slen = sizeof(si_other);

//Initialize winsock
#ifdef WIN32
	WSADATA wsa;
	printf("\nInitializing Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialized.\n");
#endif // WIN32
	//Create a socket
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Socket created.\n");

	unsigned short port_num = 0;
	std::cout << "Enter Server port number --> ";
	std::cin >> port_num;
	if (port_num < 6000)
	{
		std::cout << "\nEnter number must > 6000";
		exit(EXIT_FAILURE);
	}

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port_num);

	//Bind
	if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts("Bind done");

	//keep listening for data
	while (true)
	{
		printf("Waiting for data...\n");
		fflush(stdout);

		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//print details of the client/peer and the data received
		// inet_ntop(AF_INET, &p->ai_addr, str1, INET_ADDRSTRLEN);
		printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		strcpy_s(buf, BUFLEN, decode(buf).c_str());
		printf("Data: %s\n", buf);


		std::cout << "Answer : ";
		//std::cin >> message;
		std::cin.getline(buf, BUFLEN);

		//now reply the client with the same data
		if (sendto(s, buf, strlen(buf), 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	closesocket(s);
	WSACleanup();

	return 0;
}


////////////////////////////////////////////
// UDP Client
////////////////////////////////////////////

/*
	Simple udp client
*/

//#define SERVER "127.0.0.1"	//ip address of udp server
//#define PORT 8888	//The port on which to listen for incoming data

int TinyUDPClient(void)
{
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];

#ifdef WIN32
	WSADATA wsa;

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");
#endif //WIN32

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	std::string server_ip;
	unsigned short server_port;
	std::cout << "\nEnter Server IP Address --> ";
	std::cin >> server_ip;

	std::cout << "\nEnter Server port Number --> ";
	std::cin >> server_port;

	if (server_port < 6000)
	{
		std::cout << "\nEnter number > 6000";
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char*)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(server_port);
	si_other.sin_addr.S_un.S_addr = inet_addr(server_ip.c_str());

	fgets(message, BUFLEN - 1, stdin);
	//start communication
	while (true)
	{
		printf("Enter message : ");
		//fflush(stdout);
//		fflush(stdin);
		//std::cin.getline(message, BUFLEN);
//		std::cin >> message;

		fgets(message, BUFLEN-1, stdin);
		strcpy_s(message, BUFLEN, encode(message).c_str());
		//send the message
		if (sendto(s, message, strlen(message), 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			continue;
			//exit(EXIT_FAILURE);
		}

		printf("\nMessage from Server received\n%s\n" , buf) ;
	}

	closesocket(s);
	WSACleanup();

	return 0;
}
