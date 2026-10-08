/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPSession.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 13:39:18 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 10:26:14 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include <cstdint>
# include <string>
# include <utility>

# include "server/TCPSocket.hpp"
# include "server/TCPTypes.hpp"


// * Listen to a socket and respond. *
class TCPSession {
	private :
		TCPSocket	_socket;
		// Network information
		std::string	_ip;
		std::uint16_t	_port;

		// Protocol status
		SessionState	_state = SessionState::CONNECTED;

		// Data buffers
		std::string			_read_buffer;
		std::string			_out_buffer;

		// Client ID
		std::string	_username = "";

	public :
		static constexpr std::size_t	MAX_LINE_LENGTH = 1024;

		// --- CONSTRUCTOR ---
		TCPSession(TCPSocket&& socket, const std::string& ip, std::uint16_t port);
		// --- DESTRUCTOR ---
		~TCPSession() = default;
		// prevent copy of the instance
		TCPSession(const TCPSession&) = delete;
		TCPSession& operator=(const TCPSession&) = delete;

		// --- GETTER ---
		const std::string&	getIP() const;
		std::uint16_t		getPort() const;
		int					getSocketDescriptor() const;
		SessionState		getSessionState() const;
		const std::string&	getUsername() const;
		// --- SETTER ---
		void			setSessionState(SessionState new_state);
		void			setUsername(const std::string& username);

		// --- NETWORK READER ---
		OperationState				readData();
		std::vector<std::string>	extractCompleteLines();
		void						add_msg_to_buffer(const std::string& msg);
		bool						hasDataToSend() const;
		OperationState				sendPendingData();

		bool	inputOverflow() const;
};
