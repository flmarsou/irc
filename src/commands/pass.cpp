#include "Server.hpp"

void	Server::pass(Client *client, const std::vector<std::string> &tokens, u32 tokenSize)
{
	if (tokenSize <= 1)
	{
		client->SendMessage(ERR_NEEDMOREPARAMS(tokens[0]));
		return ;
	}

	// Client already registered
	if (client->GetPassword())
	{
		client->SendMessage(ERR_ALREADYREGISTRED);
		return ;
	}

	// Wrong password
	if (tokens[1] != _password)
	{
		client->SendMessage(ERR_PASSWDMISMATCH);
		return ;
	}

	client->SetPassword(true);
}
