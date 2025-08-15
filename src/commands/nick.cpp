#include "Server.hpp"

static bool	isCharCorrect(const i8 c)
{
	return (isalnum(c) || c == '-' || c == '[' || c == ']' ||
		c == '\\' || c == '`' || c == '^' || c == '{' || c == '}');
}

void	Server::nick(Client *client, const std::string &nickname)
{
	u32	nicknameSize = nickname.size();

	// First character wrong OR nickname too long
	if (!isalpha(nickname[0]) || nickname.size() > 9)
	{
		client->PrintMessage(ERR_ERRONEUSNICKNAME(nickname));
		return ;
	}

	// Any character wrong
	for (u32 i = 1; i < nicknameSize; ++i)
		if (!isCharCorrect(nickname[i]))
		{
			client->PrintMessage(ERR_ERRONEUSNICKNAME(nickname));
			return ;
		}

	// Nickname already used
	for (std::map<i32, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		if (it->second->GetNickname() == nickname)
		{
			client->PrintMessage(ERR_NICKNAMEINUSE(nickname));
			return ;
		}

	client->PrintMessage(NICKNAME_RAW(client->GetNickname(), nickname, client->GetUsername(), client->GetIP()));
	client->SetNickname(nickname);
}
