#include "Server.hpp"

void	Server::pass(Client *client, const std::string &password)
{
	// Client already registered
	if (client->GetPassword())
	{
		client->PrintMessage(ERR_ALREADYREGISTRED);
		return ;
	}

	// Wrong password
	if (password != _password)
	{
		client->PrintMessage(ERR_PASSWDMISMATCH);
		return ;
	}

	client->SetPassword(true);
}
