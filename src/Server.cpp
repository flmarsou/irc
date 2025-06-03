/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:32:57 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/03 13:26:56 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool	isRuning = true;

static void	signalHandler(int signum)
{
	(void)signum;
    std::cout << "\n" WARNING "Interrupt signal (ctrl + c) received." << std::endl;
	isRuning = false;
}

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

Server::Server(const unsigned short port, const std::string &password)
	:	_port(port), _password(password)
{
	// Creating the Server Socket
	this->_serverSocket = socket(IPv4, TCP, 0);
	if (this->_serverSocket == -1)
		throw (std::runtime_error(ERROR "Failed to create the Server Socket!"));
	else
		std::cout << SUCCESS "Server Socket (fd=" << this->_serverSocket << ") created!" << std::endl;

	// Defining Server Address
	sockaddr_in	serverAddress;
	serverAddress.sin_family = IPv4;
	serverAddress.sin_port = htons(this->_port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	// Binding the Server Socket
	if (bind(this->_serverSocket, (sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
		throw (std::runtime_error(ERROR "Failed to bind the Server Socket to the port!"));
	else
		std::cout << SUCCESS "Server Socket (fd=" << this->_serverSocket << ") bound to port <" << this->_port << ">!" << std::endl;

	// Listening for Connections
	if (listen(_serverSocket, LOG_LIMIT) == -1)
		throw (std::runtime_error(ERROR "Failed to listen on Server Socket!"));
	else
		std::cout << SUCCESS "Server Socket (fd=" << this->_serverSocket << ") is now listeing with backlog " << LOG_LIMIT << "!" << std::endl;

	// Add Server Socket to the List of FDs
	pollfd	pfd;
	pfd.fd = this->_serverSocket;
	pfd.events = POLL_IN;
	pfd.revents = 0;
	this->_fds.push_back(pfd);

	std::cout << INFO "IRC Server Started!\n" << INFO "Port: " << this->_port << "\n" << INFO "Password: " << this->_password << std::endl;
}

Server::~Server()
{
	// Close all the Sockets
	for (unsigned int i = 0; i < this->_fds.size(); i++)
	{
		if (close(this->_fds[i].fd) == -1)
			throw (std::runtime_error(ERROR "Failed to close a Socket!"));
		else
			std::cout << SUCCESS "Socket (fd=" << this->_fds[i].fd << ") closed!" << std::endl;
	}
}

// ========================================================================== //
//   Methods                                                                  //
// ========================================================================== //

void	Server::acceptClient()
{
	// Defining Client Address
	sockaddr_in	clientAddress;
	socklen_t	clientLength = sizeof(clientAddress);

	// Creating the Client Socket
	int			clientSocket = accept(this->_serverSocket, (sockaddr *)&clientAddress, &clientLength);
	if (clientSocket == -1)
	{
		std::cerr << WARNING "Failed to accept a new Client Socket (fd=" << clientSocket << ")!" << std::endl;
		return ;
	}

	// Add Client Socket to the FD Vector
	pollfd	pfd;
	pfd.fd = clientSocket;
	pfd.events = POLL_IN;
	pfd.revents = 0;
	this->_fds.push_back(pfd);

	// Add Client to the Client Map
	this->_clients.insert(std::make_pair(clientSocket, Client(clientSocket, inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port))));
}

void	Server::readFromClient(unsigned int index)
{
	char	buffer[BUFFER_LIMIT];

	int	bytesRead = recv(this->_fds[index].fd, buffer, BUFFER_LIMIT - 1, 0);
	// Disconnected
	if (bytesRead <= 0)
	{
		std::cout << INFO "Client (fd=" << this->_fds[index].fd << ") disconnected!" << std::endl;
		close(this->_fds[index].fd);
		this->_fds.erase(this->_fds.begin() + index);
		return ;
	}
	// Success
	else
	{
		buffer[bytesRead] = '\0';
		std::string	input(buffer);

		commands(index, input);
	}
}

void	Server::run()
{
	signal(SIGINT, signalHandler);

	while (isRuning)
	{
		if (poll(this->_fds.data(), this->_fds.size(), -1) == -1)
		{
			if (errno == EINTR)
				continue ;
			throw (std::runtime_error(ERROR "Failed to Poll!"));
		}
		for (unsigned int i = 0; i < this->_fds.size(); i++)
		{
			if (this->_fds[i].revents & POLL_IN)
			{
				if (this->_fds[i].fd == this->_serverSocket)
					acceptClient();
				else
					readFromClient(i);
			}
		}
	}
}
