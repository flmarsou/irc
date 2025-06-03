/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:37:41 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/03 13:31:08 by flmarsou         ###   ########.fr       */
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

// ========================================================================== //
//   PASS                                                                     //
// ========================================================================== //

// Returned by the server to indicate that the client must be registered before the server will allow it to be parsed in detail.
# define ERR_NOTREGISTERED		"451 :You have not registered\n"

// Returned by the server to any link which tries to change part of the registered details.
# define ERR_ALREADYREGISTRED	"462 :You may not reregister\n"

// Returned to indicate a failed attempt at registering a connection for which a password was required and was either not given or incorrect.
# define ERR_PASSWDMISMATCH		"464 :Password incorrect\n"
