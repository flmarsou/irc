/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:08:04 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/03 13:35:14 by flmarsou         ###   ########.fr       */
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
		send(it->first, ERR_ALREADYREGISTRED, std::strlen(ERR_ALREADYREGISTRED), 0);
		return ;
	}

	// Checks if the password matches
	if (input != this->_password)
	{
		send(it->first, ERR_PASSWDMISMATCH, std::strlen(ERR_PASSWDMISMATCH), 0);
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
