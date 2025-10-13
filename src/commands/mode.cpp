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

	bool	var = tokens[2][0] == '+' ? true : false;

	switch (tokens[2][1])
	{
		case ('o'): 
			if (tokenSize < 4)
			{
				client->SendMessage(ERR_NEEDMOREPARAMS(tokens[0]));
				return ;
			}
			var ? channel->AddOperator(client, tokens[3]) : channel->RemoveOperator(client, tokens[3]);
			break ;
		case ('l'):
			if (var && (tokenSize < 4 || !isInt(tokens[4])))
			{
				client->SendMessage(ERR_NEEDMOREPARAMS(tokens[0]));
				return ;
			}
			var ? channel->SetLimit(std::strtol(tokens[4].c_str(), NULL, 10)) : channel->SetLimit(0);
			break ;
	}
	
}
