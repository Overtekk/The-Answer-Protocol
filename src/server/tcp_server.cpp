/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_server.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:22:45 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/07 16:54:08 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server/TCPServer.hpp"

// --- CONSTRUCTOR ---
TCPServer::TCPServer(std::uint16_t port) :
	_listen_socket(-1),
	_is_running(false)
{
	init(port);
}

// * Run the server. *
void	TCPServer::run() {
	_is_running = true;

	while (_is_running) {
		buildPollFds();

		int return_value = poll(_poll_fds.data(), _poll_fds.size(), 100);
		if (return_value == -1) {
			// ctrl + c
			if (errno == EINTR) {
				continue;
			}
			std::cerr << "poll error: " << std::strerror(errno) << '\n';
		}
		// timeout
		else if (return_value == 0) {
			continue;
		}

		for (auto& pfd : _poll_fds) {
			int fd = pfd.fd;
			short revents = pfd.revents;
			// nothing
			if (revents == 0) {
				continue;
			}
			// new client
			else if (fd == _listen_socket.getFD() && revents & POLLIN) {
				handleNewConnection();
			}
			// client wants to disconnected
			else if (revents & (POLLERR | POLLHUP | POLLNVAL)) {
				disconnectedClient(fd);
			}
			// read client message
			else if (revents & POLLIN) {
				handleClientRead(fd);
			}
			// send buffered client data
			else if (revents & POLLOUT) {
				handleClientWrite(fd);
			}
		}
	}
}

// * Stop the server. *
void	TCPServer::stop() { _is_running = false; }

// ==== PRIVATE ===
// --- INIT SOCKET ---
// * Init the server with the port in argument. *
void	TCPServer::init(std::uint16_t port) {
	// AF_INET = Address Family: Internet (protocol IPv4).
	// SOCK_STREAM = TCP protocol (packages arrives in order, no duplicated, no loses).
	// 0 = let the system choose which protocol to use by default.
	int	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1) {
		std::cout << getTCP_error(TCPErrorCode::SYSTEM_ERROR, true);
		throw std::system_error();
	}

	// SOL_SOCKET = set option at the socket API level.
	// SO_REUSEADDR = allows immediate reuse of local address/port.
	int opt = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	// htons() = Host To Network Short (converts 16-bit integer from host byte order to network byte order)
	addr.sin_port = htons(port);
	// INADDR_ANY = accept all connexions (localhost + local ip)
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// attach the socket to the machine IP and port (error if -1).
	if (bind(fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) == -1) {
    	close(fd);
		std::cout << getTCP_error(TCPErrorCode::SYSTEM_ERROR, true);
		throw std::system_error();
	}
	// put the socket in passive mode to accept incoming client connections.
	// SOMAXCONN = (Socket Maximum Connections) use max queue allowed by the OS.
	if (listen(fd, SOMAXCONN) == -1) {
    	close(fd);
		std::cout << getTCP_error(TCPErrorCode::SYSTEM_ERROR, true);
		throw std::system_error();
	}

	// Transfert fd to the class socket.
	_listen_socket = TCPSocket(fd);
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
		client_pfd.events = POLLIN;
		if (session->hasDataToSend()) {
			client_pfd.events |= POLLOUT;
		}
		client_pfd.revents = 0;
		_poll_fds.push_back(client_pfd);
	}

}

// * Connect a client to the server. *
void	TCPServer::handleNewConnection() {
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int client_fd = accept(
		_listen_socket.getFD(), reinterpret_cast<struct sockaddr*>(&client_addr), &client_len);

	if (client_fd == -1) {
		std::cout << getTCP_error(TCPErrorCode::CONNECTION_FAILED, true);
		return;
	}

	// INET_ADDRSTRLEN = the maximum number of characters needed to hold an IPv4 address string in presentation format.
	// Get client IP and port
	char ip_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &client_addr.sin_addr, ip_str, sizeof(ip_str));
	uint16_t client_port = ntohs(client_addr.sin_port);

	TCPSocket client_socket(client_fd);
	_sessions[client_fd] = std::make_unique<TCPSession>(std::move(client_socket), ip_str, client_port);
}

// * Read incoming data from a client. *
void	TCPServer::handleClientRead(int fd) {
	// Find the client
	auto it = _sessions.find(fd);
	if (it == _sessions.end()) {
		return;
	}

	// Read the message
	OperationState state = it->second->readData();
	if (state == OperationState::DECONNEXION || state == OperationState::NETWORK_ERROR) {
		disconnectedClient(fd);
		std::cout << getTCP_error(TCPErrorCode::CONNEXION_ERROR, true);
		return;
	}

	// Extract the lines
	auto lines = it->second->extractCompleteLines();

	// TEST. COMMANDHANDLER NEED TO DO THAT
	for (const auto& line : lines) {
		std::cout << line;
	}
}

// * Empty the buffer of the client when socket is ready to be written (POLLOUT). *
void	TCPServer::handleClientWrite(int fd) {
	// Find the client
	auto it = _sessions.find(fd);
	if (it == _sessions.end()) {
		return;
	}

	//
	OperationState state = it->second->sendPendingData();
	if (state == OperationState::ERROR) {
		disconnectedClient(fd);
		std::cout << getTCP_error(TCPErrorCode::CONNEXION_ERROR, true);
		return;
	}
}

// * Disconnect a client. *
void	TCPServer::disconnectedClient(int fd) { _sessions.erase(fd); }
