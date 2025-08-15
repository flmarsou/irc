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
}

Server::~Server()
{
	// Delete clients
	for (std::map<i32, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		delete it->second;

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
	i32	clientSocket = accept(this->_socket, (sockaddr *)&clientAddress, &clientLength);
	if (clientSocket == -1)
		throw std::runtime_error("Failed to accept a new Client Socket");

	// ===== Store Socket =====
	pollfd	pfd;
	pfd.fd = clientSocket;
	pfd.events = POLLIN;
	pfd.revents = 0;
	this->_fds.push_back(pfd);

	// ===== Store Client =====
	Client	*client = new Client(clientSocket, inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));

	this->_clients.insert(std::make_pair(clientSocket, client));
}

void	Server::readClient(u32 index)
{
	i8	buffer[BUFFER_LIMIT];
	i32	bytesRead = recv(this->_fds[index].fd, buffer, BUFFER_LIMIT - 1, 0);

	// ===== Disconnect =====
	if (bytesRead <= 0)
	{
		// 1. Close client socket
		close(this->_fds[index].fd);

		// 2. Delete client object
		const std::map<i32, Client *>::iterator	it = this->_clients.find(this->_fds[index].fd);
		if (it != this->_clients.end())
		{
			delete it->second;
			this->_clients.erase(it);
		}

		// 3. Remove from pollfd
		this->_fds.erase(this->_fds.begin() + index);
	}
	// ===== Receive =====
	else
	{
		buffer[bytesRead] = '\0';

		const std::map<i32, Client *>::iterator	it = this->_clients.find(this->_fds[index].fd);
		executeCommand(it->second, buffer);
	}
}
