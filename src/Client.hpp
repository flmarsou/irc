/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:52:03 by flmarsou          #+#    #+#             */
/*   Updated: 2025/05/28 12:20:45 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "irc.hpp"

class	Client
{
	public:
		Client(const int fd, const char *ip, const unsigned short port);

		int					getFD() const;
		const char			*getIP() const;
		unsigned short		getPort() const;

		void				setNick(const std::string &nick);
		const std::string	&getNick() const;

		void				setUser(const std::string &user);
		const std::string	&getUser() const;

	private:
		const int				_fd;
		const char				*_ip;
		const unsigned short	_port;
		std::string				_nick;
		std::string				_user;
};
