/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:44:30 by flmarsou          #+#    #+#             */
/*   Updated: 2025/05/28 14:06:20 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static bool	checkArgc(const int argc, const char **argv)
{
	if (argc != 3)
	{
		std::cerr << INFO "./ircserv <port> <password>" << std::endl;
		return (false);
	}
	if (!argv[1][0])
	{
		std::cerr << ERROR "Missing Port!" << std::endl;
		return (false);
	}
	if (!argv[2][0])
	{
		std::cerr << ERROR "Missing Password!" << std::endl;
		return (false);
	}
	return (true);
}

static bool	checkPort(const char *argv1, unsigned short &port)
{
	char		*end;
	const int	temp = std::strtol(argv1, &end, 10);

	if (*end != '\0')
	{
		std::cerr << ERROR "Invalid port, must be a number!" << std::endl;
		std::cerr << INFO "Expected a numeric value in the range [1 - 65535]" << std::endl;
		return (false);
	}
	if (temp < 1)
	{
		std::cerr << ERROR "Port too small, must be at least 1!" << std::endl;
		std::cerr << INFO "Valid port range is [1 - 65535]" << std::endl;
		return (false);
	}
	if (temp > 65535)
	{
		std::cerr << ERROR "Port too large, maximum allowed is 65535!" << std::endl;
		std::cerr << INFO "Valid port range is [1 - 65535]" << std::endl;
		return (false);
	}
	port = temp;
	return (true);
}

int	main(const int argc, const char **argv)
{
	unsigned short	port;

	if (!checkArgc(argc, argv) || !checkPort(argv[1], port))
		return (1);

	try
	{
		Server serv(port, std::string(argv[2]));
		serv.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}
