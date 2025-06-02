/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerMessage.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:27:55 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/02 12:56:04 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// ========================================================================== //
//   Method                                                                   //
// ========================================================================== //

void	Server::commandMessage(const std::string &name, const std::string &input, int index)
{
	// Checks if the client has a nickname
	if (name.size() == 0)
	{
		const std::string	errorMessage = "ERROR: You need a nickname to send messages. Use the NICK command!\n";
		send(this->_fds[index].fd, errorMessage.c_str(), errorMessage.size(), 0);
		return ;
	}

	// Ignores empty messages
	if (input.size() == 1)
		return ;

	// Creates the message format
	const std::string	message = name + ": " + input;

	// Sends the message to everyone except for the sender and server
	for (unsigned int i = 0; i < this->_fds.size(); i++)
	{
		if (this->_fds[i].fd != this->_serverSocket)
			send(this->_fds[i].fd, message.c_str(), message.size(), 0);
	}

	// Sends a log to the server
	std::cout << MSG "Received a message from " << name << ": " << input;
}
