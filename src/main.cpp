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

static void	checkArgc(const i32 argc, const i8 **argv)
{
	if (argc != 3)
		throw std::runtime_error("./ircserv <port> <password>");

	if (!argv[1][0])
		throw std::runtime_error("Missing port");

	if (!argv[2][0])
		throw std::runtime_error("Missing password");
}

i32	main(const i32 argc, const i8 **argv)
{
	u16	serverPort;

	try
	{
		checkArgc(argc, argv);
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
