/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:27:36 by flmarsou          #+#    #+#             */
/*   Updated: 2025/05/26 16:01:24 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "irc.hpp"

# define IPv4	AF_INET
# define TCP	SOCK_STREAM

class	Server
{
	public:
		Server(unsigned short port);
		~Server();

		void	run();

	private:
		unsigned short	_port;
		int				_serverSocket;
		sockaddr_in		_serverAddress;

		int	acceptClient();
};
