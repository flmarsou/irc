/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:52:03 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/03 13:36:22 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "irc.hpp"

class	Client
{
	public:
		Client(const int fd, const char *ip, const unsigned short port);
		~Client();

		int					getFD() const;
		const char			*getIP() const;
		unsigned short		getPort() const;

		void				setPassword(const bool hasPassword);
		bool				getPassword() const;

		void				setNick(const std::string &nick);
		const std::string	&getNick() const;

		void				setUser(const std::string &user);
		const std::string	&getUser() const;

	private:
		const int		_fd;
		const char		*_ip;
		unsigned short	_port;
		bool			_hasPassword;
		std::string		_nick;
		std::string		_user;
};
