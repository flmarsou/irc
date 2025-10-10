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

void	Channel::AddMember(const Client *client)
{
	if (IsMember(client->GetNickname()))
		return ;

	_members.push_back(client);

	Broadcast(RAW_JOIN(client->GetNickname(), client->GetUsername(), client->GetIP(), _name), client->GetNickname(), true);

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
	{
		if (_members[i]->GetNickname() == nickname)
			return (true);
	}
	return (false);
}

void	Channel::Broadcast(const std::string &message, const std::string &caster, const bool selfSend) const
{
	for (u32 i = 0; i < _members.size(); ++i)
	{
		if (_members[i]->GetNickname() != caster && !selfSend)
			continue ;

		_members[i]->SendMessage(message);
	}
}
