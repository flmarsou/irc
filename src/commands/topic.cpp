#include "Server.hpp"

/**
 * Usage:
 * - TOPIC <#channel> <topic>
 */
void	Server::topic(Client *client, const std::vector<std::string> &tokens, u32 tokenSize)
{
	if (tokenSize < 2)
	{
		client->SendMessage(ERR_NEEDMOREPARAMS(tokens[0]));
		return ;
	}

	Channel	*channel;
	for (u32 i = 0; i < _channels.size(); ++i)
	{
		if (tokens[1] == _channels[i]->GetName())
		{
			channel = _channels[i];
			break ;
		}
		if (i == _channels.size())
		{
			client->SendMessage(ERR_NOSUCHCHANNEL(tokens[1]));
			return ;
		}
	}

	if (tokenSize == 2)
	{
		if (channel->GetTopic().empty())
			client->SendMessage(RPL_NOTOPIC(client->GetNickname(), channel->GetName()));
		else
			client->SendMessage(RPL_TOPIC(client->GetNickname(), channel->GetName(), channel->GetTopic()));
		return ;
	}

	if (channel->GetTopicPerm() && !channel->IsOperator(client->GetNickname()))
	{
		client->SendMessage(ERR_CHANOPRIVSNEEDED(tokens[1]));
		return ;
	}

	std::string	topicMessage;

	for (u32 i = 2; i < tokens.size(); ++i)
	{
		topicMessage += tokens[i];
		if (i + 1 < tokens.size())
			topicMessage += ' ';
	}

	channel->SetTopic(topicMessage);
	channel->Broadcast(RAW_TOPIC(client->GetNickname(), client->GetUsername(), client->GetIP(), channel->GetName(), channel->GetTopic()), client->GetNickname());
	client->SendMessage(RAW_TOPIC(client->GetNickname(), client->GetUsername(), client->GetIP(), channel->GetName(), channel->GetTopic()));
	std::cout << MSG << client->GetNickname() << " changed " << channel->GetName() << "'s topic to \"" << channel->GetTopic() << "\"" << RESET << std::endl;
}
