/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerNick.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:38:38 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/02 12:07:43 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

static const std::string	trimNick(std::string &input)
{
	for (unsigned int i = 4; i < input.size();)
	{
		if (input[i] == '\n' || input[i] == '\r')
			input.erase(i, 1);
		else
			i++;
	}

	return (input.substr(5));
}

static bool					checkNick(const std::string &nick)
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

void	Server::commandNick(const std::map<int, Client>::iterator &it, std::string &input)
{
	// Removes "NICK ", '\n', and '\r' from the input
	const std::string	nick = trimNick(input);

	// Checks if the nickname is valid
	if (!checkNick(nick))
	{
		std::string	errorMessage = "ERROR: Invalid username!\n";
		send(it->first, errorMessage.c_str(), errorMessage.size(), 0);
		return ;
	}

	// Changes the client nickname
	it->second.setNick(input.substr(5));

	// Sends confirmation message to the client
	const std::string	buffer = "Your username has been changed to: \"" + it->second.getNick() + "\"!\n";

	send(it->first, buffer.c_str(), buffer.size(), 0);
}
