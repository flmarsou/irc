/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:04:57 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/02 12:33:35 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// ========================================================================== //
//   Method                                                                   //
// ========================================================================== //

void	Server::parse(int index, std::string &input)
{
	const std::map<int, Client>::iterator	it = this->_clients.find(this->_fds[index].fd);

	if (input.substr(0, 4) == "NICK")
		commandNick(it, input);
	else
		commandMessage(it->second.getNick(), input, index);
}
