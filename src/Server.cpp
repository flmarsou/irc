/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:32:57 by flmarsou          #+#    #+#             */
/*   Updated: 2025/05/26 16:16:53 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(unsigned short port)
	:	_port(port)
{
	// Creating the Server Socket
	this->_serverSocket = socket(IPv4, TCP, 0);
	if (this->_serverSocket == -1)
		throw (std::runtime_error(ERROR "Failed to create the server socket!"));

	// Defining Server Address
	this->_serverAddress.sin_family = IPv4;
	this->_serverAddress.sin_port = htons(this->_port);
	this->_serverAddress.sin_addr.s_addr = INADDR_ANY;

	// Binding the Server Socket
	if (bind(this->_serverSocket, (sockaddr *)&this->_serverAddress, sizeof(_serverAddress)) == -1)
		throw (std::runtime_error(ERROR "Failed to bind the server socket!"));

	// Listening for Connections
	if (listen(_serverSocket, 4096) == -1)
		throw (std::runtime_error(ERROR "Failed to listen to server socket!"));

	std::cout << INFO "IRC Server started on port: " << this->_port << std::endl;
}

Server::~Server()
{
	// Closing the Server Socket
	close(this->_serverSocket);
}

int	Server::acceptClient()
{
	// Accepting a Client Connection
	sockaddr_in	clientAddress;
	socklen_t	clientLength = sizeof(clientAddress);
	int			clientSocket;

	clientSocket = accept(this->_serverSocket, (sockaddr *)&clientAddress, &clientLength);
	if (clientSocket == -1)
		throw (std::runtime_error(ERROR "Failed to connect the client socket!"));

	std::cout << INFO "Client IP " << inet_ntoa(clientAddress.sin_addr) << ":" << ntohs(clientAddress.sin_port) << " connected!" << std::endl;
	return (clientSocket);
}

void Server::run()
{
	// Receiving Data from the Client

}
