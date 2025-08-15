#pragma once

# include "config.hpp"

# include "Client.hpp"
# include "Channel.hpp"

# define IPv4			AF_INET
# define TCP			SOCK_STREAM
# define LOG_LIMIT		16
# define BUFFER_LIMIT	4096

class	Server
{
	public:
		// ===== Setup =====

		Server(const u16 serverPort, const std::string &password);
		~Server();

		// ===== Loop =====

		void	Run();

	private:
		// ===== Settings =====

		const u16			_port;
		const std::string	_password;
		i32					_socket;

		// ===== Data =====

		std::vector<pollfd>					_fds;
		std::map<i32, Client *>				_clients;
		std::map<std::string, Channel *>	_channels;

		// ===== Methods =====

		void	acceptClient();
		void	readClient(u32 index);

		void	executeCommand(Client *client, const i8 *buffer);
		void	executeCommandNonRegistered(Client *client, const std::vector<std::string> &tokens, u32 tokenSize);
		void	executeCommandRegistered(Client *client, const std::vector<std::string> &tokens, u32 tokenSize);

		void	pass(Client *client, const std::string &password);
		void	nick(Client *client, const std::string &nickname);
		void	user(Client *client, const std::vector<std::string> &tokens);
};
