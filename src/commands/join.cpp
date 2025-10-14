#include "Server.hpp"

/**
 * Usage:
 * - JOIN <#channel>
 */
void	Server::join(Client *client, const std::vector<std::string> &tokens, u32 tokenSize)
{
	if (tokenSize < 2)
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
			if (!_channels[i]->GetKey().empty())
			{
				if (tokenSize < 3)
				{
					client->SendMessage(ERR_);
					return ;
				}
				if (_channels[i]->GetKey() != tokens[2])
				{
					client->SendMessage(ERR_)
					return ;
				}
			}
			_channels[i]->AddMember(client);
			return ;
		}
	}


	// Create channel
	Channel	*channel = new Channel(client, tokens[1]);
	_channels.push_back(channel);
}
