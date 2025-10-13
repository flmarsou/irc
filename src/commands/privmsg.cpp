#include "Server.hpp"

/**
 * Usage:
 * - PRIVMSG <nickname> <message>
 * - PRIVMSG <#channel> <message>
 * 
 * If no receiver or message given, throw `ERR_NEEDMOREPARAMS`.
 * If a Client is found, send `RAW_PRIVMSG` to the client.
 * If a Channel is found, broadcast `RAW_PRIVMSG` to all its members.
 * If nothing is found, doesn't do anything.
 */
void	Server::privmsg(Client *client, const std::vector<std::string> &tokens, u32 tokenSize)
{
	if (tokenSize < 3)
	{
		client->SendMessage(ERR_NEEDMOREPARAMS(tokens[0]));
		return ;
	}

	std::string	message;

	for (u32 i = 2; i < tokens.size(); ++i)
	{
		message += tokens[i];
		if (i + 1 < tokens.size())
			message += ' ';
	}

	// Private Message to Client
	// =========================
	if (tokens[1][0] != '#')
	{
		for (u32 i = 0; i < _clients.size(); ++i)
		{
			if (_clients[i]->GetNickname() == tokens[1])
			{
				_clients[i]->SendMessage(RAW_PRIVMSG(client->GetNickname(), client->GetIP(), _clients[i]->GetNickname(), message));
				std::cout << MSG << client->GetNickname() << " -> " << _clients[i]->GetNickname() << " " RESET << message << std::endl;
				return ;
			}
		}
	}
	// Private Message to Channel
	// ==========================
	else
	{
		for (u32 i = 0; i < _channels.size(); ++i)
		{
			if (_channels[i]->GetName() == tokens[1])
			{
				_channels[i]->Broadcast(RAW_PRIVMSG(client->GetNickname(), client->GetIP(), tokens[1], message), client->GetNickname());
				std::cout << MSG << client->GetNickname() << " -> " << _channels[i]->GetName() << " " RESET << message << std::endl;
				return ;
			}
		}
	}
}
