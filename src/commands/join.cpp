#include "Server.hpp"

void	Server::join(const Client *client, const std::vector<std::string> &tokens)
{
	if (tokens[1][0] != '#')
	{
		client->PrintMessage(ERR_BADCHANMASK(tokens[1]));
		return ;
	}

	// Try to find an existing channel
	for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (it->second->GetName() == tokens[1])
		{
			it->second->AddMember(*client);
			return ;
		}
	}

	// Create channel
	Channel	*channel = (tokens.size() == 3)
		? new Channel(*client, tokens[1], tokens[2])
		: new Channel(*client, tokens[1]);
	_channels.insert(std::make_pair(channel->GetName(), channel));
}
