/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:22:18 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 09:31:04 by roandrie         ###   ########.fr       */
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
# include <csignal>

# include "server/TCPSocket.hpp"
# include "server/TCPSession.hpp"


class TCPServer {
	private :
		TCPSocket	_listen_socket;

		std::unordered_map<int, std::unique_ptr<TCPSession>>	_sessions;
		std::vector<struct pollfd>	_poll_fds;
		static volatile std::sig_atomic_t	_stop_requested;

		bool	_is_running;

		// CommandHandler&	_cmd_handler;

		// --- INIT SOCKET ---
		void	init(std::uint16_t port);

		// -- HANDLE NETWORK ---
		void	buildPollFds();
		void	handleNewConnection();
		void	handleClientRead(int fd);
		void	handleClientWrite(int fd);
		void	disconnectedClient(int fd);
		void	reapClosingSessions();

	public :
		// --- CONSTRUCTOR ---
		explicit TCPServer(std::uint16_t port);
		// --- DESTRUCTOR ---
		~TCPServer() = default;

		void	run();
		void	stop();
		static void	requestStop();
};
