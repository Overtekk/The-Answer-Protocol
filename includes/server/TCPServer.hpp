/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:22:18 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 14:21:38 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <memory>
# include <unordered_map>
# include <vector>
# include <poll.h>
# include <cstdint>
# include <cstring>
# include <netinet/in.h>
# include <arpa/inet.h>

# include "server/TCPSocket.hpp"
# include "server/TCPSession.hpp"

class CommandHandler;


class TCPServer {
	private :
		TCPSocket		_listen_socket;
		CommandHandler&	_cmd_handler;

		std::unordered_map<int, std::unique_ptr<TCPSession>>	_sessions;
		std::vector<struct pollfd>	_poll_fds;

		bool	_is_running;
		bool	_save_log_in_file = false;

		// --- INIT SOCKET ---
		void	init(std::uint16_t port);

		// -- HANDLE NETWORK ---
		void	buildPollFds();
		void	handleNewConnection();
		void	handleClientRead(int fd);
		void	handleClientWrite(int fd);
		void	disconnectedClient(int fd);

	public :
		// --- CONSTRUCTOR ---
		explicit TCPServer(std::uint16_t port, CommandHandler& cmd_handler, bool save_log = false);
		// --- DESTRUCTOR ---
		~TCPServer() = default;

		void	run();
		void	stop();
		void	printLogMessage(TCPSession& session, const std::string& log_msg);
};
