/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:57:01 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/03 14:38:00 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

// ========================================================================== //
//   Constructors                                                             //
// ========================================================================== //

Client::Client(const int fd, const char *ip, const unsigned short port)
	:	_fd(fd), _ip(ip), _port(port), _hasPassword(false), _nickname(""), _username(""), _realname("")
{
	std::cout << SUCCESS "!" << std::endl;
	std::cout << INFO "New client (fd=" << this->_fd << ") " << this->_ip << ":" << this->_port << " connected!" << std::endl;
}

Client::~Client()
{
	if (this->_nickname.empty())
		std::cout << INFO "Client (fd=" << this->_fd << ") deleted!" << std::endl;
	else
		std::cout << INFO "Client " << this->_nickname << " (fd=" << this->_fd << ") deleted!" << std::endl;
}

// ========================================================================== //
//   Setters & Getters                                                        //
// ========================================================================== //

int					Client::getFD() const								{ return (this->_fd); }
const char			*Client::getIP() const								{ return (this->_ip); }
unsigned short		Client::getPort() const								{ return (this->_port); }

void				Client::setPassword(const bool hasPassword)			{ this->_hasPassword = hasPassword; }
bool				Client::getPassword() const							{ return (this->_hasPassword); }

void				Client::setNickname(const std::string &nickname)	{ this->_nickname = nickname; }
const std::string	&Client::getNickname() const						{ return (this->_nickname); }

void				Client::setUsername(const std::string &username)	{ this->_username = username; }
const std::string	&Client::getUsername() const						{ return (this->_username); }

void				Client::setRealname(const std::string &realname)	{ this->_realname = realname; }
const std::string	&Client::getRealname() const						{ return (this->_realname); }
