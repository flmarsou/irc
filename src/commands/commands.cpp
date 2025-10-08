#include "Server.hpp"

#include <sstream>

void	Server::executeCommand(Client *client, const i8 *buffer)
{
	// ===== Split buffer into lines =====
	std::string			input(buffer);
	std::istringstream	lineStream(input);
	std::string			line;

	while (std::getline(lineStream, line, '\n'))	// Split on LF
	{
		// Strip CR
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		if (line.empty())
			continue ;

		// ===== Lexer =====
		std::vector<std::string>	tokens;
		std::istringstream			tokenStream(line);
		std::string					token;

		while (tokenStream >> token)
			tokens.push_back(token);

		// ===== Parser =====
		u32	tokenSize = tokens.size();

		if (tokenSize == 0)
			return ;

		if (!client->IsRegistered())
			executeCommandNonRegistered(client, tokens, tokenSize);
		else
			executeCommandRegistered(client, tokens, tokenSize);
	}
}

void	Server::executeCommandNonRegistered(Client *client, const std::vector<std::string> &tokens, u32 tokenSize)
{
	if (tokens[0] == "CAP")
		return ;

	if (tokenSize == 1)
	{
		if (tokens[0] == "PASS" || tokens[0] == "USER")
			client->PrintMessage(ERR_NEEDMOREPARAMS(tokens[0]));
		else if (tokens[0] == "NICK")
			client->PrintMessage(ERR_NONICKNAMEGIVEN);
		else
			client->PrintMessage(ERR_NOTREGISTERED);
		return ;
	}

	if (tokens[0] == "PASS")
		pass(client, tokens[1]);
	else if (tokens[0] == "NICK")
		nick(client, tokens[1]);
	else if (tokens[0] == "USER")
	{
		if (tokenSize < 5)
		{
			client->PrintMessage(ERR_NEEDMOREPARAMS(tokens[0]));
			return ;
		}
		user(client, tokens);
	}
	else
		client->PrintMessage(ERR_NOTREGISTERED);

	if (client->IsRegistered())
		client->PrintWelcome();
}

void	Server::executeCommandRegistered(Client *client, const std::vector<std::string> &tokens, u32 tokenSize)
{
	if (tokens[0] == "PASS" || tokens[0] == "USER")
		client->PrintMessage(ERR_ALREADYREGISTRED);
	else if (tokenSize == 1)
	{
		if (tokens[0] == "NICK")
			client->PrintMessage(ERR_NONICKNAMEGIVEN);
		else if (tokens[0] != "PRIVMSG" && tokens[0] != "JOIN" && tokens[0] != "TOPIC" && tokens[0] != "KICK" && tokens[0] != "NICK" && tokens[0] != "MODE")
			client->PrintMessage(ERR_UNKNOWNCOMMAND(tokens[0]));
		else
			client->PrintMessage(ERR_NEEDMOREPARAMS(tokens[0]));
		return ;
	}
	else if (tokens[0] == "NICK")
		nick(client, tokens[1]);
	else if (tokens[0] == "PRIVMSG")
	{
		if (tokenSize <= 2)
		{
			client->PrintMessage(ERR_NEEDMOREPARAMS(tokens[0]));
			return ;
		}
		else
			privmsg(client, tokens);
	}
	else if (tokens[0] == "JOIN")
		join(client, tokens);
}
