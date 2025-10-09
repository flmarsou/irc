#include "Server.hpp"

void	Server::part(Client *client, const std::string &channelName, const std::string &command)
{
	if (command == ":Leaving")
		for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
			if (it->second->GetName() == channelName)
				it->second->RemoveMember(*client);
}
