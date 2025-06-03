/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:38:38 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/03 12:55:43 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

static void	debug(const std::map<int, Client>::const_iterator &it, const std::string &input)
{
	std::cout << CMD(std::string("NICK")) << "Client (fd=" << it->first << ") " << it->second.getIP() << ":" << it->second.getPort() << " => ";

	if (it->second.getNick().empty())
		std::cout << "Changed their nickname to \"" << input << "\"!" << std::endl;
	else
		std::cout << "Changed their nickname from \"" << it->second.getNick() << "\" to \"" << input << "\"!" << std::endl;
}

static bool	checkNick(const std::string &nick)
{
	for (unsigned int i = 0; i < nick.size(); i++)
	{
		if (!isalnum(nick[i]) && nick[i] != '_')
			return (false);
	}
	return (true);
}

// ========================================================================== //
//   Method                                                                   //
// ========================================================================== //

void	Server::commandNick(const std::map<int, Client>::iterator &it, const std::string &input)
{
	// Checks if the input isn't empty
	if (input.empty())
	{
		const std::string	numerical = ERR_NONICKNAMEGIVEN(input);
		send(it->first, numerical.c_str(), numerical.size(), 0);
		return ;
	}

	// Checks if the input is valid
	if (!checkNick(input))
	{
		const std::string	numerical = ERR_ERRONEUSNICKNAME(input);
		send(it->first, numerical.c_str(), numerical.size(), 0);
		return ;
	}

	// Checks if the input doesn't exist
	for (std::map<int, Client>::const_iterator c_it = this->_clients.begin(); c_it != this->_clients.end(); c_it++)
	{
		if (input == c_it->second.getNick())
		{
			const std::string	numerical = ERR_NICKNAMEINUSE(input);
			send(it->first, numerical.c_str(), numerical.size(), 0);
			return ;
		}
	}

	// Sends confirmation message to the server
	debug(it, input);

	// Changes the client nickname
	it->second.setNick(input);

	// Sends confirmation message to the client
	const std::string	buffer = "Your nickname has been changed to: \"" + input + "\"!\n";
	send(it->first, buffer.c_str(), buffer.size(), 0);
}
