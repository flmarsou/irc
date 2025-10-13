#include "Channel.hpp"

// ========================================================================== //
//    Setup                                                                   //
// ========================================================================== //

Channel::Channel(const Client *creator, const std::string &name)
	:	_name(name)
	,	_limit(0)
{
	std::cout << INFO "Channel " << _name << " created by " << creator->GetNickname() << RESET << std::endl;

	AddMember(creator);
	AddOperator(creator, creator->GetNickname());
}

Channel::Channel(const Client *creator, const std::string &name, const std::string &key)
	:	_name(name)
	,	_key(key)
	,	_limit(0)
{
	std::cout << INFO "Channel " << _name << " created by " << creator->GetNickname() << RESET << std::endl;

	AddMember(creator);
	AddOperator(creator, creator->GetNickname());
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

bool				Channel::GetTopicPerm() const { return (_topicPerm); };
void				Channel::SetTopicPerm(const bool topicPerm) {_topicPerm = topicPerm; }

u32					Channel::GetLimit() const { return (_limit); }
void				Channel::SetLimit(const u32 limit) { _limit = limit; }

// ========================================================================== //
//    Methods                                                                 //
// ========================================================================== //

//    Members                            //
// ===================================== //
void	Channel::AddMember(const Client *client)
{
	if (IsMember(client->GetNickname()))
		return ;

	if (_limit != 0 && _members.size() >= _limit)
	{
		std::cout << INFO << client->GetNickname() << " tried to join channel " << _name << " with limit " << _limit << RESET << std::endl;
		client->SendMessage(ERR_CHANNELISFULL(_name));
		return ;
	}

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
	client->SendMessage(RPL_NAMREPLY(client->GetNickname(), _name, nicknameList));
	client->SendMessage(RPL_ENDOFNAMES(client->GetNickname(), _name));

	std::cout << MSG << client->GetNickname() << " joined " << _name << RESET << std::endl;
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
	// Not a member
	if (!IsMember(nickname))
	{
		client->SendMessage(ERR_NOSUCHNICK(nickname));
		return ;
	}

	// Already an operator
	for (u32 i = 0; i < _operators.size(); ++i)
		if (_operators[i] == nickname)
			return ;

	// Add operator
	_operators.push_back(nickname);

	Broadcast(RAW_MODE_ADDOP(client->GetNickname(), client->GetUsername(), client->GetIP(), _name, nickname), client->GetNickname());
	client->SendMessage(RAW_MODE_ADDOP(client->GetNickname(), client->GetUsername(), client->GetIP(), _name, nickname));

	std::cout << MSG << client->GetNickname() << " added " << nickname << " from operators" RESET << std::endl;
}

void	Channel::RemoveOperator(const Client *client, const std::string &nickname)
{
	// Not a member
	if (!IsMember(nickname))
	{
		client->SendMessage(ERR_NOSUCHNICK(nickname));
		return ;
	}

	// Add operator
	for (u32 i = 0; i < _operators.size(); ++i)
	{
		if (_operators[i] == nickname)
		{
			_operators.erase(_operators.begin() + i);
			Broadcast(RAW_MODE_REMOP(client->GetNickname(), client->GetUsername(), client->GetIP(), _name, nickname), client->GetNickname());
			client->SendMessage(RAW_MODE_REMOP(client->GetNickname(), client->GetUsername(), client->GetIP(), _name, nickname));

			std::cout << MSG << client->GetNickname() << " removed " << nickname << " from operators" RESET << std::endl;
			break ;
		}
	}
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

		_members[i]->SendMessage(message);
	}
}
