//============================================================================
// Name        : MMOGen.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <net/TestTCPClient.h>
#include <net/TestTCPServer.h>
#include <iostream>
#include "net/TestTcp.h"

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		TestTCPServer server;
		server.run();
	}
	else
	{
		TestTCPClient client;
		client.start();

		for (;;)
		{
			char data[256];

			std::cout << "message : ";
			std::cin.getline(data, 256);

			client.getManager()->sendMessage(NetworkMessageOut::factory(0, data));

		}
	}

	return 0;
}

