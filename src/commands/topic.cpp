#include "Server.hpp"

/**
 * Usage:
 * - TOPIC <#channel> [<topic>]
 */
void	Server::topic(Client *client, const std::vector<std::string> &tokens, u32 tokenSize)
{
	// Missing channel name
	if (tokenSize < 2)
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
		client->SendMessage(ERR_NOSUCHCHANNEL(tokens[1]));
		return ;
	}

	// Send Topic
	if (tokenSize == 2)
	{
		if (channel->GetTopic().empty())
			client->SendMessage(RPL_NOTOPIC(client->GetNickname(), channel->GetName()));
		else
			client->SendMessage(RPL_TOPIC(client->GetNickname(), channel->GetName(), channel->GetTopic()));
		return ;
	}

	// Set Topic & Permission Check
	if (channel->GetTopicPerm() && !channel->IsOperator(client->GetNickname()))
	{
		client->SendMessage(ERR_CHANOPRIVSNEEDED(tokens[1]));
		return ;
	}

	// Concatenate new topic from remaining tokens
	std::string	topicMessage;

	for (u32 i = 2; i < tokens.size(); ++i)
	{
		topicMessage += tokens[i];
		if (i + 1 < tokens.size())
			topicMessage += ' ';
	}

	// Update Topic & Notify Topic & Debug
	channel->SetTopic(topicMessage);

	const std::string	&rawTopic = RAW_TOPIC(client->GetNickname(), client->GetUsername(), client->GetIP(), channel->GetName(), channel->GetTopic());
	channel->Broadcast(rawTopic, client->GetNickname());
	client->SendMessage(rawTopic);

	std::cout << MSG << client->GetNickname() << " changed " << channel->GetName() << "'s topic to \"" << channel->GetTopic() << "\"" << RESET << std::endl;
}
