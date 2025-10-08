#pragma once

# define SUCCESS	"\e[32m[v] "
# define INFO		"\e[36m[i] "
# define WARNING	"\e[35m[!] "
# define ERROR		"\e[31m[x] "
# define MSG		"\e[33m[#] "
# define RESET		"\e[0m"

// ========================================================================== //
//     MISC                                                                   //
// ========================================================================== //

# define ERR_UNKNOWNCOMMAND(command)	"421 " + command + " :Unknown command\r\n"
# define ERR_NEEDMOREPARAMS(command)	"461 " + command + " :Not enough parameters\r\n"

// ========================================================================== //
//     PASS                                                                   //
// ========================================================================== //

# define ERR_NOTREGISTERED		"451 :You have not registered\r\n"
# define ERR_ALREADYREGISTRED	"462 :You may not reregister\r\n"
# define ERR_PASSWDMISMATCH		"464 :Password incorrect\r\n"

// ========================================================================== //
//     NICK                                                                   //
// ========================================================================== //

# define ERR_NONICKNAMEGIVEN			"431 :No nickname given\r\n"
# define ERR_ERRONEUSNICKNAME(nickname)	"432 " + nickname + " :Erroneus nickname\r\n"
# define ERR_NICKNAMEINUSE(nickname)	"433 " + nickname + " :Nickname is already in use\r\n"

# define NICKNAME_RAW(oldNick, newNick, username, hostname)	":" + oldNick + "!" + username + "@" + hostname + " NICK :" + newNick + "\r\n"

// ========================================================================== //
//     JOIN                                                                   //
// ========================================================================== //

# define ERR_BADCHANMASK(channel)	"476 " + channel + " :Bad Channel Mask\r\n"

# define JOIN_RAW(nickname, username, hostname, channelName)	":" + nickname + "!~" + username + "@" + hostname + " JOIN :" + channelName + "\r\n"

// ========================================================================== //
//     PRIVMSG                                                                //
// ========================================================================== //

# define PRIVMSG_RAW(sender, hostname, receiver, message) ":" + sender + "!~" + sender + "@" + hostname + " PRIVMSG " + receiver + " :" + message + "\r\n"
