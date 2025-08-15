#include "Server.hpp"

// Example of use: USER flmarsou 0 * : some fancy text
void	Server::user(Client *client, const std::vector<std::string> &tokens)
{
	// Client already registered
	if (!client->GetUsername().empty())
	{
		client->PrintMessage(ERR_ALREADYREGISTRED);
		return ;
	}

	// Wrong arguments
	if (tokens[2] != "0" || tokens[3] != "*" || tokens[4][0] != ':')
	{
		client->PrintMessage(ERR_NEEDMOREPARAMS(tokens[0]));
		return ;
	}

	client->SetUsername(tokens[1]);
}
