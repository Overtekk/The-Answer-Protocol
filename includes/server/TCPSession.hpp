/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPSession.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 13:39:18 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/07 15:11:28 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>

# include "server/TCPSocket.hpp"
# include "config/Enums.hpp"


// * Listen to a socket and respond. *
class TCPSession {
	private :
		TCPSocket	_socket;
		// Network information
		std::string	_ip;
		uint16_t	_port;

		// Protocol status
		SessionState	_state = SessionState::CONNECTED;

		// Data buffers
		std::string			_read_buffer;
		std::string			_out_buffer;

		// Client ID
		std::string	_username = "";

	public :
		// --- CONSTRUCTOR ---
		TCPSession(TCPSocket&& socket, const std::string& ip, uint16_t port);
		// --- DESTRUCTOR ---
		virtual ~TCPSession() = default;
		// prevent copy of the instance
		TCPSession(const TCPSession&) = delete;
		TCPSession& operator=(const TCPSession&) = delete;

		// --- GETTER ---
		std::string		getIP() const;
		uint16_t		getPort() const;
		int				getSocketDescriptor() const;
		SessionState	getSessionState() const;
		std::string		getUsername() const;
		// --- SETTER ---
		void			setSessionState(SessionState new_state);
		void			setUsername(const std::string& username);

		// --- NETWORK READER ---
		OperationState				readData();
		std::vector<std::string>	extractCompleteLines();
		void						add_msg_to_buffer(const std::string& msg);
		bool						hasDataToSend() const;
		OperationState				sendPendingData();
};
