/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:37:41 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/02 15:59:34 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// ========================================================================== //
//   NICK                                                                     //
// ========================================================================== //

// Returned when a nickname parameter expected for a command and isn't found.
# define ERR_NONICKNAMEGIVEN(nick)	"431 " + nick + " :No nickname given\n"

// Returned after receiving a NICK message which contains characters which do not fall in the defined set.
# define ERR_ERRONEUSNICKNAME(nick)	"432 " + nick + " :Erroneus nickname\n"

// Returned when a NICK message is processed that results in an attempt to change to a currently existing nickname.
# define ERR_NICKNAMEINUSE(nick)	"433 " + nick + " :Nickname is already in use\n"
