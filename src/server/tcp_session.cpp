/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_session.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 13:39:44 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/07 15:21:05 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server/TCPSession.hpp"

# define DATA_SIZE 4096

// --- CONSTRUCTOR ---
TCPSession::TCPSession(TCPSocket&& socket, const std::string& ip, uint16_t port):
	_socket(std::move(socket)), _ip(ip), _port(port) {}

// --- GETTER ---
std::string		TCPSession::getIP() const { return _ip; }
uint16_t		TCPSession::getPort() const { return _port; }
int				TCPSession::getSocketDescriptor() const { return _socket.getFD(); }
SessionState	TCPSession::getSessionState() const { return _state; }
std::string		TCPSession::getUsername() const { return _username; }
// --- SETTER ---
void			TCPSession::setSessionState(SessionState new_state) { _state = new_state; }

void			TCPSession::setUsername(const std::string& username) { _username = username; }

// --- NETWORK READER ---
// * Read what's on the socket and add it to the buffer. *
OperationState	TCPSession::readData() {
	char	buffer[DATA_SIZE] = {0};

	ssize_t data = _socket.receiveData(buffer, DATA_SIZE);

	if (data == 0) {
		return OperationState::DECONNEXION;
	}
	else if (data == -1) {
		if (errno == EAGAIN || errno == EWOULDBLOCK) {
			return OperationState::WAITING;
		}
		return OperationState::NETWORK_ERROR;
	}

	_read_buffer.append(buffer, data);
	return OperationState::SUCCESS;
}

// * Get a complete line and return it.
//   A complete line is finished by a '\n' like the protocol RFC 42TAP say so. *
std::vector<std::string>	TCPSession::extractCompleteLines() {
	std::vector<std::string>	lines_list = {};
	std::string					sub_line = "";
	size_t						pos = 0;

	while ((pos = _read_buffer.find('\n')) != std::string::npos){
		sub_line = _read_buffer.substr(0, pos + 1);
		lines_list.push_back(sub_line);
		_read_buffer.erase(0, pos + 1);
	}

	return lines_list;
}

// * Add the message in paramaters to the output buffer. Add a new line if there is not. *
void	TCPSession::add_msg_to_buffer(const std::string& msg) {
	if (msg.empty()) {
		return;
	}

	_out_buffer += msg;
	if (msg.back() != '\n') {
		_out_buffer += '\n';
	}
}

// * Check if the output buffer is empty (false) or contains something (true). *
bool	TCPSession::hasDataToSend() const { return !_out_buffer.empty(); }

// * Send the output buffer to the socket. *
OperationState	TCPSession::sendPendingData() {
	if (!hasDataToSend()) {
		return OperationState::WAITING;
	}

	ssize_t return_value = _socket.sendData(_out_buffer);

	if (return_value > 0) {
		_out_buffer.erase(0, return_value);
	}
	else if (return_value == -1) {
		if (errno == EAGAIN || errno == EWOULDBLOCK) {	// buffer full, waiting
			return OperationState::SUCCESS;
		}
		return OperationState::ERROR;
	}
	else if (return_value == 0) {
		return OperationState::WAITING;
	}

	return OperationState::SUCCESS;
}
