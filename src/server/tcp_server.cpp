/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_server.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:22:45 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 10:25:29 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <cerrno>
# include <cstring>
# include <system_error>
# include <sys/socket.h>

# include "server/TCPServer.hpp"
# include "protocol/TCP_error.hpp"
# include "utils.h"


volatile std::sig_atomic_t TCPServer::_stop_requested = 0;

// --- CONSTRUCTOR ---
TCPServer::TCPServer(std::uint16_t port) :
	_listen_socket(-1),
	_is_running(false)
{
	init(port);
}

// * Run the server. *
// 'revents' is a BIT MASK: several events can be set at once (e.g. POLLIN | POLLHUP when a
// client sends "QUIT\n" then closes). That's why these are independent 'if', not 'else if'.
// POLLHUP is handled like POLLIN: recv() still returns the pending bytes, then 0.
// After handleClientRead() the session may have been destroyed, hence the _sessions.count(fd).
void	TCPServer::run() {
	_is_running = true;

	while (_is_running && !_stop_requested) {
		buildPollFds();

		int ret = poll(_poll_fds.data(), _poll_fds.size(), 100);
		if (ret == -1) {
			if (errno == EINTR) {
				continue;
			}
			print_error(std::string("poll: ") + std::strerror(errno));
			break;
		}
		if (ret == 0) {
			continue;
		}

		for (const auto& pfd : _poll_fds) {
			const int   fd = pfd.fd;
			const short ev = pfd.revents;
			if (ev == 0) {
				continue;
			}
			if (fd == _listen_socket.getFD()) {
				if (ev & POLLIN) {
					handleNewConnection();
				}
				continue;
			}
			if (ev & (POLLERR | POLLNVAL)) {
				disconnectedClient(fd);
				continue;
			}
			if (ev & (POLLIN | POLLHUP)) {
				handleClientRead(fd);
			}
			if ((ev & POLLOUT) && _sessions.count(fd)) {
				handleClientWrite(fd);
			}
		}
		reapClosingSessions();
	}
}

// * Stop the server. *
void	TCPServer::stop() { _is_running = false; }

// * Request to stop the server. *
void TCPServer::requestStop() { _stop_requested = 1; }

// ==== PRIVATE ===
// --- INIT SOCKET ---
// * Init the server with the port in argument. *
void	TCPServer::init(std::uint16_t port) {
	// AF_INET = Address Family: Internet (protocol IPv4).
	// SOCK_STREAM = TCP protocol (packages arrives in order, no duplicated, no loses).
	// 0 = let the system choose which protocol to use by default.
	TCPSocket sock(socket(AF_INET, SOCK_STREAM, 0));
	if (sock.getFD() == -1) {
		throw std::system_error(errno, std::generic_category(), "socket");
	}

	// SOL_SOCKET = set option at the socket API level.
	// SO_REUSEADDR = allows immediate reuse of local address/port.
	int opt = 1;
	if (setsockopt(sock.getFD(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
		throw std::system_error(errno, std::generic_category(), "setsockopt");
	}

	sockaddr_in addr{};

	addr.sin_family = AF_INET;
	// htons() = Host To Network Short (converts 16-bit integer from host byte order to network byte order)
	addr.sin_port = htons(port);
	// INADDR_ANY = accept all connexions (localhost + local ip)
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// attach the socket to the machine IP and port (error if -1).
	if (bind(sock.getFD(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1) {
		throw std::system_error(errno, std::generic_category(), "bind");
	}
	// put the socket in passive mode to accept incoming client connections.
	// SOMAXCONN = (Socket Maximum Connections) use max queue allowed by the OS.
	if (listen(sock.getFD(), SOMAXCONN) == -1) {
		throw std::system_error(errno, std::generic_category(), "listen");
	}

	// Transfert fd to the class socket.
	_listen_socket = std::move(sock);
}

// -- HANDLE NETWORK ---
// * Populate the pollfd vector with descriptors and monitored events. *
void	TCPServer::buildPollFds() {
	_poll_fds.clear();

	// Add listen socket
	struct pollfd listen_pdf;
	listen_pdf.events = POLLIN;	// tell when a new client wants to connect
	listen_pdf.revents = 0;
	listen_pdf.fd = _listen_socket.getFD();
	_poll_fds.push_back(listen_pdf);

	// Add each client session
	for (const auto& [fd, session] : _sessions) {
		struct pollfd client_pfd;
		client_pfd.fd = fd;
		// A closing session only needs to flush its output: we stop listening to it.
		// poll() still reports POLLERR/POLLHUP even when 'events' is 0.
		client_pfd.events = (session->getSessionState() == SessionState::CLOSING) ? 0 : POLLIN;
		if (session->hasDataToSend()) {
			client_pfd.events |= POLLOUT;
		}
		client_pfd.revents = 0;
		_poll_fds.push_back(client_pfd);
	}

}

// * Connect a client to the server. *
void	TCPServer::handleNewConnection() {
	int client_fd = accept(_listen_socket.getFD(), reinterpret_cast<sockaddr*>(&client_addr), &client_len);
	if (client_fd == -1) {
		if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) {
			print_error(std::string("accept: ") + std::strerror(errno));
		}
		return;
	}

	auto session = std::make_unique<TCPSession>(TCPSocket(client_fd), ip_str, client_port);
	session->add_msg_to_buffer("OK hello proto=1");     // RFC 3.2
	_sessions[client_fd] = std::move(session);
	print_log(std::string(ip_str) + ":" + std::to_string(client_port) + " connected");
}

// * Read incoming data from a client. *
void	TCPServer::handleClientRead(int fd) {
	auto it = _sessions.find(fd);
	if (it == _sessions.end()) {
		return;
	}
	TCPSession& session = *it->second;

	switch (session.readData()) {
		case OperationState::PEER_CLOSED:
			print_log(session.getIP() + " disconnected");
			disconnectedClient(fd);
			return;
		case OperationState::FAILURE:
			print_error(session.getIP() + ": network error");
			disconnectedClient(fd);
			return;
		case OperationState::WOULD_BLOCK:
			return;
		case OperationState::SUCCESS:
			break;
	}

	bool too_long = false;
	for (const auto& line : session.extractCompleteLines()) {
		if (line.size() > TCPSession::MAX_LINE_LENGTH) {
			too_long = true;
			break;
		}
		if (line.empty()) { continue; }
		print_log("recv: " + line);   // later: _handler->onLine(fd, line);
	}

	// Two cases: a complete line that is too long (checked above),
	// or an unfinished line that keeps growing without any '\n' (checked here).
	if (too_long || session.inputOverflow()) {
		session.add_msg_to_buffer(getTCP_error(TCPErrorCode::LINE_TOO_LONG));
		session.setSessionState(SessionState::CLOSING);   // flushed, then closed by reapClosingSessions()
	}
}

// * Handle the data from a client. *
void	TCPServer::handleClientWrite(int fd) {
	auto it = _sessions.find(fd);
	if (it == _sessions.end()) {
		return;
	}
	if (it->second->sendPendingData() == OperationState::FAILURE) {
		disconnectedClient(fd);
	}
}

// * Empty the buffer of the client when socket is ready to be written (POLLOUT). *
void	TCPServer::handleNewConnection() {
	sockaddr_in client_addr{};
	socklen_t   client_len = sizeof(client_addr);   // in/out: accept() writes the real size back

	int client_fd = accept(_listen_socket.getFD(),
		reinterpret_cast<sockaddr*>(&client_addr), &client_len);
	if (client_fd == -1) {
		// The listen socket is non-blocking: EAGAIN just means "nobody is waiting anymore".
		if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) {
			print_error(std::string("accept: ") + std::strerror(errno));
		}
		return;
	}

	char ip_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &client_addr.sin_addr, ip_str, sizeof(ip_str));
	const std::uint16_t client_port = ntohs(client_addr.sin_port);   // network -> host byte order

	auto session = std::make_unique<TCPSession>(TCPSocket(client_fd), ip_str, client_port);
	session->add_msg_to_buffer("OK hello proto=1");   // RFC 3.2
	_sessions[client_fd] = std::move(session);
	print_log(std::string(ip_str) + ":" + std::to_string(client_port) + " connected");
}

// * Disconnect a client. *
void	TCPServer::disconnectedClient(int fd) { _sessions.erase(fd); }

// * Closing client session. *
void	TCPServer::reapClosingSessions() {
	for (auto it = _sessions.begin(); it != _sessions.end(); ) {
		if (it->second->getSessionState() == SessionState::CLOSING
			&& !it->second->hasDataToSend()) {
			it = _sessions.erase(it);
		}
		else {
			++it;
		}
	}
}
