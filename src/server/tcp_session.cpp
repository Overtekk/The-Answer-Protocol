/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_session.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 13:39:44 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 10:20:49 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cerrno>

# include "server/TCPSession.hpp"
# include "server/TCPTypes.hpp"

namespace { constexpr std::size_t DATA_SIZE = 4096; }

// --- CONSTRUCTOR ---
TCPSession::TCPSession(TCPSocket&& socket, const std::string& ip, std::uint16_t port):
	_socket(std::move(socket)), _ip(ip), _port(port) {}

// --- GETTER ---
const std::string&		TCPSession::getIP() const { return _ip; }
std::uint16_t			TCPSession::getPort() const { return _port; }
int						TCPSession::getSocketDescriptor() const { return _socket.getFD(); }
SessionState			TCPSession::getSessionState() const { return _state; }
const std::string&		TCPSession::getUsername() const { return _username; }
// --- SETTER ---
void			TCPSession::setSessionState(SessionState new_state) { _state = new_state; }

void			TCPSession::setUsername(const std::string& username) { _username = username; }

// --- NETWORK READER ---
// * Read what's on the socket and add it to the buffer. *
OperationState	TCPSession::readData() {
	char buffer[DATA_SIZE];
	ssize_t n = _socket.receiveData(buffer, sizeof(buffer));

	if (n > 0) {
		_read_buffer.append(buffer, static_cast<size_t>(n));
		return OperationState::SUCCESS;
	}
	if (n == 0) {
		return OperationState::PEER_CLOSED;
	}
	// WOULD_BLOCK is not an error: the socket is non-blocking, "nothing to read right now"
	// is a normal answer. EINTR means a signal interrupted the call: just retry later.
	if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
		return OperationState::WOULD_BLOCK;
	}
	return OperationState::FAILURE;
}

// * Get a complete line and return it.
// A complete line is finished by a '\n' like the protocol RFC 42TAP say so. *
// TCP is a byte stream, not a message stream. One recv() can return half a command,
// or three commands at once. So we only extract what is terminated by '\n'
// and leave the incomplete tail in the buffer for the next recv().
// 'start' walks through the buffer; we erase once at the end instead of after every line
// (erase(0, n) shifts the whole buffer, so doing it per line is wasteful).
std::vector<std::string> TCPSession::extractCompleteLines() {
	std::vector<std::string> lines;
	size_t start = 0;
	size_t pos;

	while ((pos = _read_buffer.find('\n', start)) != std::string::npos) {
		size_t end = pos;
		if (end > start && _read_buffer[end - 1] == '\r') {
			--end;
		}
		lines.emplace_back(_read_buffer, start, end - start);
		start = pos + 1;
	}
	_read_buffer.erase(0, start);
	return lines;
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
	if (_out_buffer.empty()) {
		return OperationState::WOULD_BLOCK;
	}
	ssize_t n = _socket.sendData(_out_buffer);
	if (n > 0) {
		_out_buffer.erase(0, static_cast<size_t>(n));
		return OperationState::SUCCESS;
	}
	if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)) {
		return OperationState::WOULD_BLOCK;
	}
	return OperationState::FAILURE;
}

bool TCPSession::inputOverflow() const { return _read_buffer.size() > MAX_LINE_LENGTH; }
