#pragma once

# include "config.hpp"

class	Client
{
	public:
		// ===== Setup =====

		Client(const i32 fd, const i8 *ip, const u16 port);
		~Client();

		// ===== Getters & Setters =====

		i32			GetFD() const;
		const i8	*GetIP() const;
		u16			GetPort() const;

		bool		GetPassword() const;
		void		SetPassword(const bool password);

		std::string	GetNickname() const;
		void		SetNickname(const std::string &nickname);

		std::string	GetUsername() const;
		void		SetUsername(const std::string &username);

		// ===== Methods =====

		void		SendMessage(const std::string &message) const;
		void		SendWelcome() const;
		bool		IsRegistered() const;

	private:
		// ===== Data =====

		const i32	_fd;
		const i8	*_ip;
		const u16	_port;

		bool		_password;
		std::string	_nickname;
		std::string	_username;
};
