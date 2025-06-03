/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:04:57 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/03 15:00:27 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

static const std::string	trimInput(std::string input)
{
	// Removes all the starting spaces
	for (unsigned int i = 0; input[i] == ' ';)
		input.erase(i, 1);

	// Removes all the whitespaces
	for (unsigned int i = 0; input[i];)
	{
		if (input[i] == '\n' || input[i] == '\r')
			input.erase(i, 1);
		else
			i++;
	}

	return (input);
}

// ========================================================================== //
//   Method                                                                   //
// ========================================================================== //

void	Server::commands(int index, std::string &input)
{
	const std::map<int, Client *>::iterator	it = this->_clients.find(this->_fds[index].fd);

	if (!it->second->getPassword())
	{
		if (input.substr(0, 5) == "PASS ")
			commandPass(it, trimInput(input.substr(5)));
		else
			send(it->first, ERR_NOTREGISTERED, std::strlen(ERR_NOTREGISTERED), 0);
		return ;
	}

	if (input.substr(0, 5) == "NICK ")
		commandNick(it, trimInput(input.substr(5)));
	else if (input.substr(0, 5) == "USER ")
		commandUser(it, trimInput(input.substr(5)));
	else if (input.substr(0, 5) == "PASS ")
		commandPass(it, trimInput(input.substr(5)));
}
