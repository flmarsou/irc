#include "Server.hpp"

/**
 * Usage:
 * - USER <username> 0 * :<realname>
 * 
 * If not enough arguments are given, throw `ERR_NEEDMOREPARAMS`.
 * If the client is already registered, throw `ERR_ALREADYREGISTRED`.
 * If the arguments are wrong, throw `ERR_NEEDMOREPARAMS`.
 * 
 * Note:
 * - Only <username> is useful and must be stored, <realname> doesn't serve any purpose.
 */
void	Server::user(Client *client, const std::vector<std::string> &tokens, u32 tokenSize)
{
	// Missing arguments
	if (tokenSize <= 4)
	{
		client->SendMessage(ERR_NEEDMOREPARAMS(tokens[0]));
		return ;
	}

	// Client already registered
	if (!client->GetUsername().empty())
	{
		client->SendMessage(ERR_ALREADYREGISTRED);
		return ;
	}

	// Wrong arguments
	if (tokens[2] != "0" || tokens[3] != "*" || tokens[4][0] != ':')
	{
		client->SendMessage(ERR_NEEDMOREPARAMS(tokens[0]));
		return ;
	}

	client->SetUsername(tokens[1]);
}
