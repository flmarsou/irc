/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:52:03 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/03 14:37:00 by flmarsou         ###   ########.fr       */
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

		void				setNickname(const std::string &nickname);
		const std::string	&getNickname() const;

		void				setUsername(const std::string &username);
		const std::string	&getUsername() const;

		void				setRealname(const std::string &realname);
		const std::string	&getRealname() const;

	private:
		const int		_fd;
		const char		*_ip;
		unsigned short	_port;
		bool			_hasPassword;
		std::string		_nickname;
		std::string		_username;
		std::string		_realname;

};
