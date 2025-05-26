/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:44:30 by flmarsou          #+#    #+#             */
/*   Updated: 2025/05/26 15:46:10 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "Server.hpp"

int	main(const int argc, const char **argv)
{
	unsigned short	port;

	if (!parser(argc, argv, port))
		return (1);

	try
	{
		Server serv(port);
		serv.run();
	}
	catch(const std::exception &exception)
	{
		std::cerr << exception.what() << std::endl;
	}

	return (0);
}
