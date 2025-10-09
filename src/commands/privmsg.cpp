#include "Server.hpp"

void	Server::privmsg(Client *client, const std::vector<std::string> &tokens)
{
	std::string	message;

	for (u32 i = 2; i < tokens.size(); ++i)
	{
		message += tokens[i];
		if (i + 1 < tokens.size())
			message += ' ';
	}

	// Send to Client
	if (tokens[1][0] != '#')
	{
		for (std::map<i32, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		{
			if (it->second->GetNickname() == tokens[1])
				it->second->PrintMessage(RAW_PRIVMSG(client->GetNickname(), client->GetIP(), it->second->GetNickname(), message));
		}
	}
	// Broadcast to Channel
	else
	{
		for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		{
			if (it->second->GetName() == tokens[1])
				it->second->Broadcast(*client, message);
		}
	}
}
