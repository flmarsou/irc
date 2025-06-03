/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:57:01 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/03 13:23:54 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

Client::Client(const int fd, const char *ip, const unsigned short port)
	:	_fd(fd), _ip(ip), _port(port), _nick(""), _user(""), _hasPassword(false)
{
	std::cout << SUCCESS "New client connected!" << std::endl;
	std::cout << INFO "Client FD/IP: (fd=" << this->_fd << ") " << this->_ip << ":" << this->_port << std::endl;
}

// ========================================================================== //
//   Setters & Getters                                                        //
// ========================================================================== //

int					Client::getFD() const						{ return (this->_fd); }
const char			*Client::getIP() const						{ return (this->_ip); }
unsigned short		Client::getPort() const						{ return (this->_port); }

void				Client::setPassword(const bool hasPassword)	{ this->_hasPassword = hasPassword; }
bool				Client::getPassword() const					{ return (this->_hasPassword); }

void				Client::setNick(const std::string &nick)	{ this->_nick = nick; }
const std::string	&Client::getNick() const					{ return (this->_nick); }

void				Client::setUser(const std::string &user)	{ this->_user = user; }
const std::string	&Client::getUser() const					{ return (this->_user); }
