/*
 * LoginServer.cpp
 *
 *  Created on: 30 janv. 2015
 *      Author: rguyard
 */

#include <net/TestTCPClient.h>
#include <net/TestTCPLoginClient.h>
#include <net/TestTCPServer.h>
#include <iostream>
#include "net/TestTcp.h"
#include "net/UnityPolicyServer.h"

#include "net/game/LoginServer.h"

#include <boost/program_options.hpp>
#include <net/web/WebServer.h>

int main(int argc, char* argv[])
{

	boost::program_options::options_description desc("Allowed options");
	desc.add_options()
	    ("help,h", "produce this help message")
	    ("server,s", "TCP server (default)")
	    ("client,c", "TCP test client")
	    ("UPS", "Unity Policy Server (EXPERIMENTAL)")
	    ("web", "web Server (EXPERIMENTAL)")
	    ("print", "print in game messages")
	    ("web-port", boost::program_options::value<int>()->default_value(8080), "port of the web server")
	    ("port,p", boost::program_options::value<int>()->default_value(12345), "port of the server")
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

	if (vm.count("UPS"))
	{
		UnityPolicyServer ups;
		ups.run();
		return 0;
	}
	if (vm.count("web"))
	{
		WebServer ws(NULL, vm["port"].as<int>());
		ws.run();
		return 0;
	}

	if (!vm.count("client"))
	{
		LoginServer server(vm["port"].as<int>(), vm.count("print"), vm["web-port"].as<int>());
		server.listen();
	}
	else
	{
		TestTCPLoginClient client(vm["host"].as<std::string>(), vm["port"].as<int>());
		client.run();
	}

	return 0;
}

