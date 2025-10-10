#include "Channel.hpp"

// ========================================================================== //
//    Setup                                                                   //
// ========================================================================== //

Channel::Channel(const Client &creator, const std::string &name)
	:	_name(name)
{
	std::cout << INFO "Channel " << _name << " created by " << creator.GetNickname() << RESET << std::endl;

	AddMember(creator);

	_modes[INVITE_MODE] = false;
	_modes[TOPIC_MODE] = false;
	_modes[KEY_MODE] = false;
	_modes[OPERATOR_MODE] = false;
	_modes[LIMIT_MODE] = false;
}

Channel::Channel(const Client &creator, const std::string &name, const std::string &key)
	:	_name(name)
	,	_key(key)
{
	std::cout << INFO "Channel " << _name << " created by " << creator.GetNickname() << RESET << std::endl;

	AddMember(creator);

	_modes[INVITE_MODE] = false;
	_modes[TOPIC_MODE] = false;
	_modes[KEY_MODE] = false;
	_modes[OPERATOR_MODE] = false;
	_modes[LIMIT_MODE] = false;
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

bool				Channel::GetMode(const Modes mode) const { return (_modes[mode]); }
void				Channel::SetMode(const Modes mode, const bool set) { _modes[mode] = set; }

const i32			Channel::GetLimit() const { return (_limit); };
void				Channel::SetLimit(const i32 limit) { _limit = limit; };

// ========================================================================== //
//    Methods                                                                 //
// ========================================================================== //

bool	Channel::IsMember(const Client &client) const
{
	return (_members.find(client.GetFD()) != _members.end());
}

void	Channel::AddMember(const Client &client)
{
	if (IsMember(client))
		return ;

	_members.insert(std::make_pair(client.GetFD(), &client));

	// Send join message to everyone
	for (std::map<i32, const Client *>::iterator it = _members.begin(); it != _members.end(); ++it)
		it->second->PrintMessage(RAW_JOIN(client.GetNickname(), client.GetUsername(), client.GetIP(), _name));

	std::string	nicknameList;
	for (std::map<i32, const Client *>::const_iterator it = _members.begin(); it != _members.end(); ++it)
	{
		if (!nicknameList.empty())
			nicknameList += " ";
		nicknameList += it->second->GetNickname();
	}

	// Refresh members list
	client.PrintMessage(RPL_NAMREPLY("ft_irc.serv", client.GetNickname(), _name, nicknameList));
	client.PrintMessage(RPL_ENDOFNAMES("ft_irc.serv", client.GetNickname(), _name));
}

void	Channel::RemoveMember(const Client &client)
{
	if (!IsMember(client))
		return ;

	std::map<i32, const Client *>::iterator	it = _members.find(client.GetFD());

	// Send part message to everyone
	for (std::map<i32, const Client *>::iterator it = _members.begin(); it != _members.end(); ++it)
		it->second->PrintMessage(RAW_PART(client.GetNickname(), client.GetUsername(), client.GetIP(), _name, "Leaving"));

	_members.erase(it);
}

void	Channel::AddOperator(const Client &receiver, const Client &sender)
{
	if (!IsMember(receiver))
	{
		receiver.PrintMessage(ERR_NOSUCHNICK(receiver.GetNickname()));
		return ;
	}

	for (std::vector<std::string>::iterator it = _operators.begin(); it != _operators.end(); ++it)
	{
		if (*it == receiver.GetNickname())
			return ;
	}

	_operators.push_back(receiver.GetNickname());
	receiver.PrintMessage(RAW_MODE_ADDOP(sender.GetNickname(), sender.GetUsername(), sender.GetIP(), _name, receiver.GetNickname()));
}

void	Channel::RemoveOperator(const Client &receiver, const Client &sender)
{
 	if (!IsMember(receiver))
	{
		receiver.PrintMessage(ERR_NOSUCHNICK(receiver.GetNickname()));
		return ;
	}

	for (std::vector<std::string>::iterator it = _operators.begin(); it != _operators.end(); ++it)
	{
		if (*it == receiver.GetNickname())
		{
			_operators.erase(it);
			receiver.PrintMessage(RAW_MODE_REMOP(sender.GetNickname(), sender.GetUsername(), sender.GetIP(), _name, receiver.GetNickname()));
			return ;
		}
	}
}

void	Channel::Broadcast(const Client &sender, const std::string &message)
{
	for (std::map<i32, const Client *>::iterator it = _members.begin(); it != _members.end(); ++it)
	{
		if (it->second->GetFD() == sender.GetFD())
			continue ;
		it->second->PrintMessage(RAW_BROADCAST(sender.GetNickname(), sender.GetUsername(), sender.GetIP(), _name, message));
	}
}
