/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:45:17 by flmarsou          #+#    #+#             */
/*   Updated: 2025/05/28 12:08:41 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "debug.hpp"

# include <cstdlib>
# include <cstring>

# include <sys/stat.h>		// fstat
# include <sys/socket.h>	// socket, setsockopt, getsockname, bind, connect, listen, accept, recv, send
# include <fcntl.h>			// fcntl
# include <poll.h>			// poll
# include <netinet/in.h>	// htons, htonl, ntohs, ntohl, sockaddr_in
# include <arpa/inet.h>		// inet_addr, inet_ntoa
# include <netdb.h>			// getprotobyname, gethostbyname, getaddrinfo, freeaddrinfo
# include <unistd.h>		// close, lseek
# include <csignal>			// signal, sigaction
# include <errno.h>			// error in poll handler

bool	parser(const int argc, const char **argv, unsigned short &port);
