#include "Server.hpp"

// ========================================================================== //
//    Setup                                                                   //
// ========================================================================== //

bool	gIsRunning = true;

static void	interruptHandler(int signum)
{
	(void)signum;
	std::cout << '\n' << WARNING "Interrupt signal (ctrl + c) received" RESET << std::endl;
	gIsRunning = false;
}

Server::Server(const u16 serverPort, const std::string &password)
	:	_port(serverPort)
	,	_password(password)
{
	// ===== Interrupt Signal =====
	signal(SIGINT, interruptHandler);

	// ===== Server Socket =====
	_socket = socket(IPv4, TCP, 0);
	if (_socket == -1)
		throw std::runtime_error("Failed to create the Server Socket");
	std::cout << SUCCESS "Server socket (fd=" << _socket << ") created" RESET << std::endl;

	// ===== Server Address =====
	sockaddr_in	address;
	address.sin_family = IPv4;
	address.sin_port = htons(_port);
	address.sin_addr.s_addr = INADDR_ANY;

	// ===== Bind Socket =====
	if (bind(_socket, (sockaddr *)&address, sizeof(address)) == -1)
	{
		close(_socket);
		throw std::runtime_error("Failed to bind the Server Socket to the port");
	}
	std::cout << SUCCESS "Server bound to port " << _port << RESET << std::endl;

	// ===== Listen Socket =====
	if (listen(_socket, LOG_LIMIT) == -1)
	{
		close(_socket);
		throw std::runtime_error("Failed to listen on Server Socket");
	}
	std::cout << SUCCESS "Server socket is listening with backlog " << LOG_LIMIT << RESET << std::endl;

	// ===== Store Socket =====
	pollfd	pfd;
	pfd.fd = _socket;
	pfd.events = POLLIN;
	pfd.revents = 0;
	_fds.push_back(pfd);

	std::cout << SUCCESS "Server IRC started" RESET << '\n';

	// ===== Init Bot =====
	_bot = new Bot();
	_clients.push_back(_bot);
}

Server::~Server()
{
	// Delete clients
	for (u32 i = 0; i < _clients.size(); ++i)
		delete _clients[i];
	_clients.clear();

	// Delete channels
	for (u32 i = 0; i < _channels.size(); ++i)
		delete _channels[i];
	_channels.clear();

	// Close FDs
	for (u32 i = 0; i < _fds.size(); ++i)
	{
		if (close(_fds[i].fd) == -1)
			throw std::runtime_error("Failed to close a socket");
		std::cout << INFO "Socket (fd=" << _fds[i].fd << ") closed" RESET << std::endl;
	}
}

// ========================================================================== //
//    Loop                                                                    //
// ========================================================================== //

void	Server::Run()
{
	while (gIsRunning)
	{
		// Wait for packets
		if (poll(_fds.data(), _fds.size(), -1) == -1)
		{
			if (!gIsRunning)
			{
				std::cout << INFO "Closing server..." RESET << std::endl;
				return ;
			}
			throw std::runtime_error("Failed to poll");
		}
		// Handle packets
		for (u32 i = 0; i < _fds.size(); ++i)
		{
			if (_fds[i].revents & POLLIN)
			{
				if (_fds[i].fd == _socket)
					acceptClient();
				else
					readClient(i);
			}
		}
	}
}

// ========================================================================== //
//    Methods                                                                 //
// ========================================================================== //

void	Server::acceptClient()
{
	// ===== Client Address =====
	sockaddr_in	clientAddress;
	socklen_t	clientLength = sizeof(clientAddress);

	// ===== Client Socket =====
	i32	clientSocket = accept(_socket, (sockaddr *)&clientAddress, &clientLength);
	if (clientSocket == -1)
		throw std::runtime_error("Failed to accept a new Client Socket");

	// ===== Store Socket =====
	pollfd	pfd;
	pfd.fd = clientSocket;
	pfd.events = POLLIN;
	pfd.revents = 0;
	_fds.push_back(pfd);

	// ===== Store Client =====
	Client	*client = new Client(clientSocket, inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));

	_clients.push_back(client);
}

void	Server::readClient(u32 index)
{
	i8	buffer[BUFFER_LIMIT];
	i32	bytesRead = recv(_fds[index].fd, buffer, BUFFER_LIMIT - 1, 0);

	// ===== Disconnect =====
	if (bytesRead <= 0)
	{
		// 1. Close client socket
		close(_fds[index].fd);

		// 2. Delete client object
		for (size_t i = 0; i < _clients.size(); ++i)
		{
			if (_clients[i]->GetFD() == _fds[index].fd)
			{
				disconnectClient(_clients[i]);	// Notify Others

				delete _clients[i];
				_clients.erase(_clients.begin() + i);

				break ;
			}
		}

		// 3. Remove from pollfd
		_fds.erase(_fds.begin() + index);
	}
	// ===== Receive =====
	else
	{
		buffer[bytesRead] = '\0';

		for (u32 i = 0; i < _clients.size(); ++i)
		{
			if (_clients[i]->GetFD() == _fds[index].fd)
			{
				executeCommand(_clients[i], buffer);
				break ;
			}
		}
	}
}

void	Server::disconnectClient(const Client *client)
{
	for (u32 i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i]->IsInvitee(client->GetNickname()))
			_channels[i]->RemoveInvitee(client->GetNickname());

		if (_channels[i]->IsMember(client->GetNickname()))
		{
			_channels[i]->Broadcast(RAW_QUIT(client->GetNickname(), client->GetUsername(), client->GetIP(), "Client disconnected\r\n"), client->GetNickname());
			if (_channels[i]->IsOperator(client->GetNickname()))
				_channels[i]->RemoveOperator(client, client->GetNickname());
			_channels[i]->RemoveMember(client);
		}
	}
}
