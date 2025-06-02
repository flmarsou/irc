/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:27:36 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/02 12:56:17 by flmarsou         ###   ########.fr       */
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
		std::map<int, Client>	_clients;

		void	acceptClient();
		void	readFromClient(unsigned int index);

		void	parse(int index, std::string &input);
		void	commandNick(const std::map<int, Client>::iterator &it, std::string &input);
		void	commandMessage(const std::string &name, const std::string &input, int index);
};
