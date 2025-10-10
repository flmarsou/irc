#include "Server.hpp"

static bool	isCharCorrect(const i8 c)
{
	return (isalnum(c) || c == '-' || c == '[' || c == ']' ||
		c == '\\' || c == '`' || c == '^' || c == '{' || c == '}');
}

void	Server::nick(Client *client, const std::vector<std::string> &tokens, u32 tokenSize)
{
	// Missing arguments
	if (tokenSize <= 1)
	{
		client->SendMessage(ERR_NONICKNAMEGIVEN);
		return ;
	}

	u32	nicknameSize = tokens[1].size();

	// First character wrong OR nickname too long
	if (!isalpha(tokens[1][0]) || nicknameSize > 9)
	{
		client->SendMessage(ERR_ERRONEUSNICKNAME(tokens[1]));
		return ;
	}

	// Any character wrong
	for (u32 i = 1; i < nicknameSize; ++i)
		if (!isCharCorrect(tokens[1][i]))
		{
			client->SendMessage(ERR_ERRONEUSNICKNAME(tokens[1]));
			return ;
		}

	// Nickname already used
	for (u32 i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i]->GetNickname() == tokens[1])
		{
			client->SendMessage(ERR_NICKNAMEINUSE(tokens[1]));
			return ;
		}
	}

	// DOES NOT WORK
	// Send changes to all channel members
	for (u32 i = 0; i < _channels.size(); ++i)
		if (_channels[i]->IsMember(client->GetNickname()))
			_channels[i]->Broadcast(RAW_NICKNAME(client->GetNickname(), tokens[1], client->GetUsername(), client->GetIP()), client->GetNickname(), false);

	client->SendMessage(RAW_NICKNAME(client->GetNickname(), tokens[1], client->GetUsername(), client->GetIP()));
	client->SetNickname(tokens[1]);
}
