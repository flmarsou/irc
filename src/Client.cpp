# include "Client.hpp"

// ========================================================================== //
//    Setup                                                                   //
// ========================================================================== //

Client::Client(const i32 fd, const i8 *ip, const u16 port)
	:	_fd(fd)
	,	_ip(ip)
	,	_port(port)
	,	_password(false)
	,	_nickname("")
	,	_username("")
{
	std::cout << "\n" INFO "New client has joined: \n" RESET;
	std::cout << " - FD: " << _fd << '\n';
	std::cout << " - IP: " << _ip << '\n';
	std::cout << " - Port: " << _port << '\n';
	std::cout << std::endl;
}

Client::~Client()
{
	if (_nickname.empty())
		std::cout << INFO "Client (fd=" << _fd << ") left!" << std::endl;
	else
		std::cout << INFO "Client " << _nickname << " (fd=" << _fd << ") left!" << std::endl;
}

// ========================================================================== //
//    Getters & Setters                                                       //
// ========================================================================== //

i32			Client::GetFD() const { return (_fd); }
const i8	*Client::GetIP() const { return (_ip); }
u16			Client::GetPort() const { return (_port); }

bool		Client::GetPassword() const { return (_password); }
void		Client::SetPassword(const bool password) { _password = password; }

std::string	Client::GetNickname() const { return (_nickname); }
void		Client::SetNickname(const std::string &nickname) { _nickname = nickname; }

std::string	Client::GetUsername() const { return (_username); }
void		Client::SetUsername(const std::string &username) { _username = username; }

// ========================================================================== //
//    Methods                                                                 //
// ========================================================================== //

void	Client::PrintMessage(const std::string &message) const
{
	send(_fd, message.c_str(), message.size(), 0);
}

void	Client::PrintWelcome() const
{
	const std::string	buffer = "Welcome to the IRC server, " + _nickname + "\n";

	send(_fd, buffer.c_str(), buffer.size(), 0);
}

bool	Client::IsRegistered() const
{
	return (_password && !_nickname.empty() && !_username.empty());
}
