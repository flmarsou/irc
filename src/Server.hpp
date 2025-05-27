/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:27:36 by flmarsou          #+#    #+#             */
/*   Updated: 2025/05/27 16:36:16 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "irc.hpp"

# include <vector>

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

		void	acceptClient();
		void	readFromClient(unsigned int index);
};
