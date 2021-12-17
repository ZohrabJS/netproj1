#ifndef NET_UTILS_H_123456_Z
#define NET_UTILS_H_123456_Z

#pragma once

/*
	Simple UDP Server
*/

#include<stdio.h>
#include<winsock2.h>
#include<iostream>
#include <string>
using namespace std;
//#include "Code.cpp"
#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUFLEN 1024	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data

#ifndef WIN32
#define WSAGetLastError() 1
#define WSACleanup();
#endif //WIN32

int TinyUDPServer(void);
int TinyUDPClient(void);
string encode(string str);
string decode(string str);
#endif //NET_UTILS_H_123456_Z
