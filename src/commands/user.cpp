/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:38:16 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/03 15:30:25 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

static void					debug(const std::map<int, Client *>::iterator &it, const std::string &newUsername, const std::string &newRealname)
{
	std::cout << CMD(std::string("USER")) << "Client (fd=" << it->first << ") " << it->second->getIP() << ":" << it->second->getPort() << " => ";

	if (it->second->getUsername().empty() || it->second->getRealname().empty())
		std::cout << "Changed their username to \"" << newUsername << "\" and their realname to \"" << newRealname << "\"!" << std::endl;
	else
		std::cout << "Changed their username from \"" << it->second->getUsername() << "\" to \"" << newUsername << "\" and their realname from \"" << it->second->getRealname() << "\" to \"" << newRealname << "\"!" << std::endl;
}

static bool					checkInput(const std::string &input)
{
	unsigned int	foundRealname = 0;

	for (unsigned int i = 0; input[i]; i++)
	{
		if (input[i] && input[i + 1])
			if (input[i] == ' ' && input[i + 1] == ':')
				foundRealname++;
	}

	if (foundRealname != 1)
		return (false);

	return (true);
}

static const std::string	trimUsername(const std::string &input)
{
	std::string	username;

	for (unsigned int i = 0; input[i]; i++)
	{
		if (input[i] == ' ')
			break ;
		username += input[i];
	}

	return (username);
}

static const std::string	trimRealname(const std::string &input)
{
	unsigned int	i = 0;
	std::string		realname;

	while (input[i])
	{
		if (input[i] == ':')
		{
			i++;
			break ;
		}
		i++;
	}

	while (input[i])
	{
		realname += input[i];
		i++;
	}

	return (realname);
}

// ========================================================================== //
//   Method                                                                   //
// ========================================================================== //

void	Server::commandUser(const std::map<int, Client *>::iterator &it, const std::string &input)
{
	// Checks if the input is valid
	if (!checkInput(input))
	{
		const std::string	numerical = ERR_NEEDMOREPARAMS(std::string("USER"));
		send(it->first, numerical.c_str(), numerical.size(), 0);
		const std::string	usage = "/USER <nickname> <hostname>(skipped) <servername>(skipped) <:realname>\n";
		send(it->first, usage.c_str(), usage.size(), 0);
		return ;
	}

	const std::string	username = trimUsername(input);
	const std::string	realname = trimRealname(input);

	// Sends confirmation message to the server
	debug(it, username, realname);

	// Changes the client username and realname
	it->second->setUsername(username);
	it->second->setRealname(realname);
}
