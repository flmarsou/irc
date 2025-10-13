#include "Server.hpp"

static bool	isInt(const std::string &input)
{
	i8	*end;
	const i64	tmp = std::strtol(input.c_str(), &end, 10);

	if (tmp < U32MIN || tmp > U32MAX || *end != '\0')
		return (false);

	return (true);
}

static bool	parser(Client *client, const std::vector<std::string> &tokens, u32 tokenSize, const std::vector<Channel *> channels, Channel *&channel)
{
	if (tokenSize < 3)
	{
		client->SendMessage(ERR_NEEDMOREPARAMS(tokens[0]));
		return (false);
	}

	for (u32 i = 0; i < channels.size(); ++i)
	{
		if (tokens[1] == channels[i]->GetName())
		{
			channel = channels[i];
			break ;
		}
		if (i == channels.size())
		{
			client->SendMessage(ERR_NOSUCHCHANNEL(tokens[1]));
			return (false);
		}
	}

	if (tokens[2][0] != '+' && tokens[2][0] != '-')
	{
		client->SendMessage(ERR_UNKNOWNMODE(tokens[2][0], tokens[1]));
		return (false);
	}

	if (tokens[2].size() < 2)
		return (false);

	if (tokens[2][1] != 'i' && tokens[2][1] != 't' && tokens[2][1] != 'k' && tokens[2][1] != 'o' && tokens[2][1] != 'l')
	{
		client->SendMessage(ERR_UNKNOWNMODE(tokens[2][1], tokens[1]));
		return (false);
	}

	return (true);
}

void	Server::mode(Client *client, const std::vector<std::string> &tokens, u32 tokenSize)
{
	Channel	*channel;

	if (!parser(client, tokens, tokenSize, _channels, channel))
		return ;

	if (!channel->IsOperator(client->GetNickname()))
	{
		client->SendMessage(ERR_CHANOPRIVSNEEDED(tokens[1]));
		return ;
	}

	bool	var = tokens[2][0] == '+' ? true : false;

	switch (tokens[2][1])
	{
		case ('o'):
		{
			if (tokenSize < 4)
			{
				client->SendMessage(ERR_NEEDMOREPARAMS(tokens[0]));
				return ;
			}
			var ? channel->AddOperator(client, tokens[3]) : channel->RemoveOperator(client, tokens[3]);
			break ;
		}
		case ('l'):
		{
			if (var && (tokenSize < 4 || !isInt(tokens[3])))
			{
				client->SendMessage(ERR_NEEDMOREPARAMS(tokens[0]));
				return ;
			}
			if (var)
			{
				channel->SetLimit(std::strtol(tokens[3].c_str(), NULL, 10));
				channel->Broadcast(RAW_MODE(client->GetNickname(), client->GetUsername(), client->GetIP(), tokens[1], "+l", tokens[3]), client->GetNickname());
				client->SendMessage(RAW_MODE(client->GetNickname(), client->GetUsername(), client->GetIP(), tokens[1], "+l", tokens[3]));
				std::cout << MSG << client->GetNickname() << " set channel " << tokens[1] << "'s limit to " << tokens[3] << RESET << std::endl;
			}
			else
			{
				channel->SetLimit(0);
				channel->Broadcast(RAW_MODE(client->GetNickname(), client->GetUsername(), client->GetIP(), tokens[1], "-l", std::string("")), client->GetNickname());
				client->SendMessage(RAW_MODE(client->GetNickname(), client->GetUsername(), client->GetIP(), tokens[1], "-l", std::string("")));
				std::cout << MSG << client->GetNickname() << " removed channel " << tokens[1] << "'s limit" << RESET << std::endl;
			}
			break ;
		}
		case ('t'):
		{
			if (var)
			{
				channel->SetTopicPerm(true);
				channel->Broadcast(RAW_MODE(client->GetNickname(), client->GetUsername(), client->GetIP(), tokens[1], "+t", tokens[3]), client->GetNickname());
				client->SendMessage(RAW_MODE(client->GetNickname(), client->GetUsername(), client->GetIP(), tokens[1], "+t", tokens[3]));
				std::cout << MSG << client->GetNickname() << " set channel " << tokens[1] << "'s topic permissions to operators"  RESET << std::endl;
			}
			else
			{
				channel->SetTopicPerm(false);
				channel->Broadcast(RAW_MODE(client->GetNickname(), client->GetUsername(), client->GetIP(), tokens[1], "-t", std::string("")), client->GetNickname());
				client->SendMessage(RAW_MODE(client->GetNickname(), client->GetUsername(), client->GetIP(), tokens[1], "-t", std::string("")));
				std::cout << MSG << client->GetNickname() << " set channel " << tokens[1] << "'s topic permission to anyone" RESET << std::endl;
			}
		}
		default: break ;
	}
}
