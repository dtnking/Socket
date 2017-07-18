#include <WinSock2.h>
#include "client.h"
#include <stdio.h>


int main_client()
{
	//Winsock Startup
	WSADATA wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) //If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	SOCKADDR_IN addr; //Address to be binded to our Connection socket
	int sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Address = localhost (this pc)
	addr.sin_port = htons(1111); //Port = 1111
	addr.sin_family = AF_INET; //IPv4 Socket

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL); //Set Connection socket
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0) //If we are unable to connect...
	{
		MessageBoxA(NULL, "Failed to Connect", "Error", MB_OK | MB_ICONERROR);
		return 0; //Failed to Connect
	}

	printf("connected!!\n" );

	char MOTD[256] = {"POST  HTTP/1.1\n"
                    "Host: 127.0.0.1\n"
                    "Content-Type: application/json\n"
                    "Content-Length: 34\n"
                    "{\n"
                    "\"speed\" : \"20\",\n"
                    "\"angle\" : \"360\"\n"
                    "}\n"
  };
	send(Connection, MOTD, sizeof(MOTD), NULL); //Receive Message of the Day buffer into MOTD array
	printf("String: %s\n",MOTD);
}
