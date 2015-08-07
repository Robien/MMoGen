//============================================================================
// Name        : MMOGen.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <net/TestTCPClient.h>
#include <net/TestTCPLoginClient.h>
#include <net/TestTCPServer.h>
#include <iostream>
#include "net/TestTcp.h"

#include "net/game/LoginServer.h"

#include <boost/program_options.hpp>

int main(int argc, char* argv[])
{

	// Declare the supported options.
	boost::program_options::options_description desc("Allowed options");
	desc.add_options()
	    ("help", "produce help message")
	    ("server", "TCP server (default)")
	    ("client", "TCP test client")
	    ("port", boost::program_options::value<int>()->default_value(12345), "port of the server (default 12345)")
	    ("host", boost::program_options::value<std::string>()->default_value("127.0.0.1"), "host of the server (only in client mode)")
	;

	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
	boost::program_options::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 1;
	}

	if (!vm.count("client"))
	{
		LoginServer server(vm["port"].as<int>());
		server.listen();
	}
	else
	{
		TestTCPLoginClient client(vm["host"].as<std::string>(), vm["port"].as<int>());
		client.run();
	}

	return 0;
}

