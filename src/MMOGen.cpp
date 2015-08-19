/*
 * LoginServer.cpp
 *
 *  Created on: 30 janv. 2015
 *      Author: rguyard
 */

#include <net/tests/TestTCPClient.h>
#include <net/tests/TestTCPLoginClient.h>
#include <net/tests/TestTCPServer.h>
#include <iostream>
#include "net/tests/TestTcp.h"
#include "net/Unity/UnityPolicyServer.h"

#include "net/game/LoginServer.h"

#include <boost/program_options.hpp>
#include <common/Constants.h>
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
	    ("print", "print in-game messages")
	    ("exit-as-soon-as-you-can", "the server will exit as soon it will not disturb any client")
	    ("max-game", boost::program_options::value<int>()->default_value(500), "max game before the server start discard new connection")
	    ("name", boost::program_options::value<std::string>()->default_value(""), "my name")
	    ("duel-name", boost::program_options::value<std::string>()->default_value(""), "name of the person you want to play with")
	    ("web-port", boost::program_options::value<int>()->default_value(8080), "port of the web server")
	    ("port,p", boost::program_options::value<int>()->default_value(12345), "port of the server")
	    ("host", boost::program_options::value<std::string>()->default_value("127.0.0.1"), "host of the server (only in client mode)")
	;

	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
	boost::program_options::notify(vm);

	Constants::get()->add("exit-as-soon-as-you-can", (bool) vm.count("exit-as-soon-as-you-can"));
	Constants::get()->add("max-game", (int) vm.count("max-game"));

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
		client.setDuelName(vm["duel-name"].as<std::string>());
		client.setName(vm["name"].as<std::string>());
		client.run();
	}

	return 0;
}

