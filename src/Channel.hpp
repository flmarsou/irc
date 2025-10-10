#pragma once

# include "config.hpp"

# include "Client.hpp"

enum	Modes
{
	INVITE_MODE,
	TOPIC_MODE,
	KEY_MODE,
	OPERATOR_MODE,
	LIMIT_MODE
};

class	Channel
{
	public:
		// ===== Setup =====

		Channel(const Client &creator, const std::string &name);
		Channel(const Client &creator, const std::string &name, const std::string &key);
		~Channel();

		// ===== Getters & Setters =====

		const std::string	GetName() const;

		const std::string	GetKey() const;
		void				SetKey(const std::string &key);

		const std::string	GetTopic() const;
		void				SetTopic(const std::string &topic);

		const i32			GetLimit() const;
		void				SetLimit(const i32 limit);

		bool				GetMode(const Modes mode) const;
		void				SetMode(const Modes mode, const bool set);

		// ===== Methods =====

		bool	IsMember(const Client &client) const;

		void	AddMember(const Client &client);
		void	RemoveMember(const Client &client);

		void	AddOperator(const Client &receiver, const Client &sender);
		void	RemoveOperator(const Client &receiver, const Client &sender);

		void	Broadcast(const Client &sender, const std::string &message);

	private:
		// ===== Data =====

		std::map<i32, const Client *>	_members;
		std::vector<std::string>		_operators;

		const std::string		_name;
		std::string				_key;
		std::string				_topic;
		i32						_limit;

		bool					_modes[5];
};
