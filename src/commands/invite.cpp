#include "Server.hpp"

void	Server::invite(Client *client, const std::vector<std::string> &tokens, u32 tokenSize)
{
	if (tokenSize < 3)
	{
		client->SendMessage(ERR_NEEDMOREPARAMS(tokens[0]));
		return ;
	}

	// Look for the channel
	Channel	*channel = NULL;

	for (u32 i = 0; i < _channels.size(); ++i)
	{
		if (tokens[2] == _channels[i]->GetName())
		{
			channel = _channels[i];
			break ;
		}
	}

	// No such channel found
	if (!channel)
	{
		client->SendMessage(ERR_NOSUCHCHANNEL(tokens[2]));
		return ;
	}

	for (u32 i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i]->GetNickname() == tokens[1])
		{
			channel->AddInvitee(client, _clients[i]);
			return ;
		}
	}

	client->SendMessage(ERR_NOSUCHNICK(tokens[1]));
}
