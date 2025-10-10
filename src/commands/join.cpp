#include "Server.hpp"

void	Server::join(Client *client, const std::vector<std::string> &tokens, u32 tokenSize)
{
	if (tokenSize <= 1)
	{
		client->SendMessage(ERR_NEEDMOREPARAMS(tokens[0]));
		return ;
	}

	// First character wrong
	if (tokens[1][0] != '#')
	{
		client->SendMessage(ERR_BADCHANMASK(tokens[1]));
		return ;
	}

	// Try to find an existing channel
	for (u32 i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i]->GetName() == tokens[1])
		{
			_channels[i]->AddMember(client);
			return ;
		}
	}

	// Create channel
	Channel	*channel = (tokens.size() == 3)
		? new Channel(client, tokens[1], tokens[2])
		: new Channel(client, tokens[1]);
	_channels.push_back(channel);
}
