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
	// HexChat Auth
	if (tokens[0] == "CAP")
		return ;

	// Commands
	if (tokens[0] == "PASS")
		pass(client, tokens, tokenSize);
	else if (tokens[0] == "NICK")
		nick(client, tokens, tokenSize);
	else if (tokens[0] == "USER")
		user(client, tokens, tokenSize);
	else
		client->SendMessage(ERR_NOTREGISTERED);

	// Auth Successful
	if (client->IsRegistered())
		client->SendWelcome();
}

void	Server::executeCommandRegistered(Client *client, const std::vector<std::string> &tokens, u32 tokenSize)
{
	// Forbidden Commands
	// ==================
	if (tokens[0] == "PASS" || tokens[0] == "USER")
	{
		client->SendMessage(ERR_ALREADYREGISTRED);
		return ;
	}

	// Unknown Commands
	// ================
	if (tokens[0] != "PRIVMSG" && tokens[0] != "JOIN" && tokens[0] != "TOPIC" && tokens[0] != "KICK"
		&& tokens[0] != "NICK" && tokens[0] != "MODE" && tokens[0] != "INVITE" && tokens[0] != "PART")
	{
		client->SendMessage(ERR_UNKNOWNCOMMAND(tokens[0]));
		return ;
	}

	// Allowed Commands
	// ================
	if (tokens[0] == "NICK")
		nick(client, tokens, tokenSize);
	else if (tokens[0] == "JOIN")
		join(client, tokens, tokenSize);
	else if (tokens[0] == "PRIVMSG")
		privmsg(client, tokens, tokenSize);
	else if (tokens[0] == "MODE")
		mode(client, tokens, tokenSize);
	else if (tokens[0] == "TOPIC")
		topic(client, tokens, tokenSize);
	else if (tokens[0] == "INVITE")
		invite(client, tokens, tokenSize);
}
