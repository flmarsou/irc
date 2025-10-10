#pragma once

# include "config.hpp"

# include "Client.hpp"

class	Channel
{
	public:
		// ===== Setup =====

		Channel(const Client *creator, const std::string &name);
		Channel(const Client *creator, const std::string &name, const std::string &key);
		~Channel();

		// ===== Getters & Setters =====

		const std::string	GetName() const;

		const std::string	GetKey() const;
		void				SetKey(const std::string &key);

		const std::string	GetTopic() const;
		void				SetTopic(const std::string &topic);

		// ===== Methods =====

		void	AddMember(const Client *client);
		void	RemoveMember(const Client *client);
		bool	IsMember(const std::string &nickname);

		void	Broadcast(const std::string &message, const std::string &caster, const bool selfSend) const;

	private:
		// ===== Data =====

		std::vector<const Client *>	_members;
		std::vector<std::string>	_operators;

		const std::string		_name;
		std::string				_key;
		std::string				_topic;
		i32						_limit;
};
