/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:08:04 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/03 13:25:39 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// ========================================================================== //
//   Utils                                                                    //
// ========================================================================== //

static void	debug(const std::map<int, Client>::const_iterator &it)
{
	std::cout << CMD(std::string("PASS")) << "Client (fd=" << it->first << ") " << it->second.getIP() << ":" << it->second.getPort()
		<< " => Successfully logged in!" << std::endl;
}

// ========================================================================== //
//   Method                                                                   //
// ========================================================================== //

void	Server::commandPass(const std::map<int, Client>::iterator &it, const std::string &input)
{
	// Checks if already logged in
	if (it->second.getPassword())
	{
		const std::string	numerical = ERR_ALREADYREGISTRED;
		send(it->first, numerical.c_str(), numerical.size(), 0);
		return ;
	}

	// Checks if the password matches
	if (input != this->_password)
	{
		const std::string	numerical = ERR_PASSWDMISMATCH;
		send(it->first, numerical.c_str(), numerical.size(), 0);
		return ;
	}
	// Sends confirmation message to the client
	else
	{
		debug(it);
		it->second.setPassword(true);

		const std::string	buffer = "Welcome to the server!\n";
		send(it->first, buffer.c_str(), buffer.size(), 0);
	}
}
