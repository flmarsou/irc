/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:27:36 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/03 14:39:33 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Client.hpp"

# include <vector>
# include <map>

# define IPv4			AF_INET
# define TCP			SOCK_STREAM
# define LOG_LIMIT		16
# define BUFFER_LIMIT	4096

class	Server
{
	public:
		Server(const unsigned short port, const std::string &password);
		~Server();

		void	run();

	private:
		const unsigned short	_port;
		const std::string		_password;
		int						_serverSocket;
		std::vector<pollfd>		_fds;
		std::map<int, Client *>	_clients;

		void	acceptClient();
		void	readFromClient(unsigned int index);

		void	commands(int index, std::string &input);
		void	commandPass(const std::map<int, Client *>::iterator &it, const std::string &input);
		void	commandNick(const std::map<int, Client *>::iterator &it, const std::string &input);
		void	commandUser(const std::map<int, Client *>::iterator &it, const std::string &input);
};
