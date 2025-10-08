#include "config.hpp"

#include "Server.hpp"

static void	checkPort(const i8 *str, u16 &port)
{
	i8			*end;
	const i32	nbr = std::strtol(str, &end, 10);

	if (*end)
		throw std::runtime_error("Invalid port, must only contain digits");

	if (nbr < 1)
		throw std::runtime_error("Port too small, must be greater than 0");

	if (nbr > 65535)
		throw std::runtime_error("Port too large, must be lower than 65535");

	port = nbr;
}

i32	main(const i32 argc, const i8 **argv)
{
	u16	serverPort;

	if (argc != 3)
	{
		std::cout << ERROR "./ircserv <port> <password>" RESET << std::endl;
		return (1);
	}

	try
	{
		checkPort(argv[1], serverPort);

		Server	server(serverPort, std::string(argv[2]));

		server.Run();
	}
	catch (const std::exception &e)
	{
		std::cerr << ERROR << e.what() << RESET << std::endl;
		return (1);
	}
}
