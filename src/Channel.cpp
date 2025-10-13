#include "Channel.hpp"

// ========================================================================== //
//    Setup                                                                   //
// ========================================================================== //

Channel::Channel(const Client *creator, const std::string &name)
	:	_name(name)
{
	std::cout << INFO "Channel " << _name << " created by " << creator->GetNickname() << RESET << std::endl;

	AddMember(creator);
}

Channel::Channel(const Client *creator, const std::string &name, const std::string &key)
	:	_name(name)
	,	_key(key)
{
	std::cout << INFO "Channel " << _name << " created by " << creator->GetNickname() << RESET << std::endl;

	AddMember(creator);
}

Channel::~Channel()
{
	std::cout << INFO "Channel " << _name << " destroyed" RESET << std::endl;
}

// ========================================================================== //
//    Getters & Setters                                                       //
// ========================================================================== //

const std::string	Channel::GetName() const { return (_name); }

const std::string	Channel::GetKey() const { return (_key); }
void				Channel::SetKey(const std::string &key) { _key = key; }

const std::string	Channel::GetTopic() const { return (_topic); }
void				Channel::SetTopic(const std::string &topic) { _topic = topic; }

// ========================================================================== //
//    Methods                                                                 //
// ========================================================================== //

//    Members                            //
// ===================================== //
void	Channel::AddMember(const Client *client)
{
	if (IsMember(client->GetNickname()))
		return ;

	_members.push_back(client);

	Broadcast(RAW_JOIN(client->GetNickname(), client->GetUsername(), client->GetIP(), _name), client->GetNickname());
	client->SendMessage(RAW_JOIN(client->GetNickname(), client->GetUsername(), client->GetIP(), _name));

	std::string	nicknameList;
	for (u32 i = 0; i < _members.size(); ++i)
	{
		if (!nicknameList.empty())
			nicknameList += " ";
		nicknameList += _members[i]->GetNickname();
	}

	// Refresh members list
	client->SendMessage(RPL_NAMREPLY("ft_irc.serv", client->GetNickname(), _name, nicknameList));
	client->SendMessage(RPL_ENDOFNAMES("ft_irc.serv", client->GetNickname(), _name));
}

void Channel::RemoveMember(const Client *client)
{
	for (u32 i = 0; i < _members.size(); ++i)
	{
		if (_members[i] == client)
		{
			_members.erase(_members.begin() + i);
			break ;
		}
	}
}

bool	Channel::IsMember(const std::string &nickname)
{
	for (u32 i = 0; i < _members.size(); ++i)
		if (_members[i]->GetNickname() == nickname)
			return (true);
	return (false);
}

//    Operators                          //
// ===================================== //

void	Channel::AddOperator(const Client *client, const std::string &nickname)
{
	if (!IsMember(nickname))
	{
		client->SendMessage(ERR_NOSUCHNICK(nickname));
		return ;
	}

	_operators.push_back(nickname);

	Broadcast(RAW_MODE_ADDOP(client->GetNickname(), client->GetUsername(), client->GetIP(), _name, nickname), client->GetNickname());
	client->SendMessage(RAW_MODE_ADDOP(client->GetNickname(), client->GetUsername(), client->GetIP(), _name, nickname));
}

void	Channel::RemoveOperator(const Client *client, const std::string &nickname)
{
	if (!IsMember(nickname))
	{
		client->SendMessage(ERR_NOSUCHCHANNEL(nickname));
		return ;
	}

	for (u32 i = 0; i < _operators.size(); ++i)
	{
		if (_operators[i] == nickname)
		{
			_operators.erase(_operators.begin() + i);
			break ;
		}
	}

	Broadcast(RAW_MODE_REMOP(client->GetNickname(), client->GetUsername(), client->GetIP(), _name, nickname), client->GetNickname());
	client->SendMessage(RAW_MODE_REMOP(client->GetNickname(), client->GetUsername(), client->GetIP(), _name, nickname));
}

bool	Channel::IsOperator(const std::string &nickname)
{
	for (u32 i = 0; i < _operators.size(); ++i)
		if (_operators[i] == nickname)
			return (true);
	return (false);
}

//    Utils                              //
// ===================================== //
void	Channel::Broadcast(const std::string &message, const std::string &caster) const
{
	for (u32 i = 0; i < _members.size(); ++i)
	{
		if (_members[i]->GetNickname() == caster)
			continue ;

		std::cout << _members[i]->GetNickname() << std::endl;
		_members[i]->SendMessage(message);
	}
}
