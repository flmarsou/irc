#include "Bot.hpp"

Bot::Bot(i32 fd)
	: Client(fd, "127.0.0.1", 0)
{
	SetNickname("Bot");
	SetUsername("bot");

	std::cout << INFO "Bot initialized!" << RESET << std::endl;
}
