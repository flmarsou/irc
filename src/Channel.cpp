#include "Channel.hpp"

// ========================================================================== //
//    Setup                                                                   //
// ========================================================================== //

Channel::Channel(const Client &creator, const std::string &name)
	:	_name(name)
{
	std::cout << INFO "Channel " << _name << " created by " << creator.GetNickname() << RESET << std::endl;

	_members.insert(std::make_pair(creator.GetFD(), &creator));

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

	_members.insert(std::make_pair(creator.GetFD(), &creator));

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

bool		Channel::GetMode(const Modes mode) const { return (_modes[mode]); }
void		Channel::SetMode(const Modes mode, const bool set) { _modes[mode] = set; }

// ========================================================================== //
//    Methods                                                                 //
// ========================================================================== //

bool	Channel::IsMember(const Client &client) const
{
	return (_members.find(client.GetFD()) != _members.end());
}

void	Channel::AddMember(const Client &client)
{
	if (!IsMember(client))
		_members.insert(std::make_pair(client.GetFD(), &client));
}
