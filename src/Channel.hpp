#pragma once

# include "config.hpp"

# include "Client.hpp"

class	Channel
{
	public:
		// ===== Setup =====

		Channel(const Client *creator, const std::string &name);
		~Channel();

		// ===== Getters & Setters =====

		const std::string	GetName() const;

		const std::string	GetKey() const;
		void				SetKey(const std::string &key);

		const std::string	GetTopic() const;
		void				SetTopic(const std::string &topic);

		bool				GetTopicPerm() const;
		void				SetTopicPerm(const bool topicPerm);

		u32					GetLimit() const;
		void				SetLimit(const u32 limit);

		bool				GetInvitePerm() const;
		void				SetInvitePerm(const bool inviteOnly);

		// ===== Methods =====

		void	AddMember(const Client *client);
		void	RemoveMember(const Client *client);
		bool	IsMember(const std::string &nickname);

		void	AddOperator(const Client *client, const std::string &nickname);
		void	RemoveOperator(const Client *client, const std::string &nickname);
		bool	IsOperator(const std::string &nickname);
		void	EditOperator(const std::string &oldNickname, const std::string &newNickname);

		void	AddInvitee(const Client *client, const Client *invitee);
		void	RemoveInvitee(const Client *client, const std::string &nickname);
		bool	IsInvitee(const std::string &nickname);
		void	EditInvitee(const std::string &oldNickname, const std::string &newNickname);

		void	Broadcast(const std::string &message, const std::string &caster) const;

	private:
		// ===== Data =====

		std::vector<const Client *>	_members;
		std::vector<std::string>	_operators;
		std::vector<std::string>	_invitees;

		const std::string		_name;
		std::string				_key;
		bool					_topicPerm;
		std::string				_topic;
		u32						_limit;
		bool					_inviteOnly;
};
