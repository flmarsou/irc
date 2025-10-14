#include "Server.hpp"

/**
 * Usage:
 * - KICK <channel> <nickname> [<comment>]
 */
void	Server::kick(Client *client, const std::vector<std::string> &tokens, u32 tokenSize)
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
		if (tokens[1] == _channels[i]->GetName())
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

	// No permission
	if (!channel->IsOperator(client->GetNickname()))
	{
		client->SendMessage(ERR_CHANOPRIVSNEEDED(channel->GetName()));
		return ;
	}

	std::string comment;

	if (tokenSize >= 4)
	{
		for (u32 i = 3; i < tokens.size(); ++i)
		{
			comment += tokens[i];
			if (i + 1 < tokens.size())
				comment += ' ';
		}
	}
	else
		comment = "Kicked";

	for (u32 i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i]->GetNickname() == tokens[2] && channel->IsMember(_clients[i]->GetNickname()))
		{
			channel->RemoveOperator(client, tokens[2]);
			channel->Broadcast(RPL_KICK(client->GetNickname(), _clients[i]->GetNickname(), channel->GetName(), comment), client->GetNickname());
			channel->RemoveMember(_clients[i]);
			client->SendMessage(RPL_KICK(client->GetNickname(), _clients[i]->GetNickname(), channel->GetName(), comment));
			return ;
		}
	}

	client->SendMessage(ERR_NOSUCHNICK(tokens[2]));
}
