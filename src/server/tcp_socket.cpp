/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_socket.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 11:23:08 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 13:28:36 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server/TCPSocket.hpp"

// --- CONSTRUCTOR ---
TCPSocket::TCPSocket(int fd): _fd(fd) {
	if (fd != -1) {
		setNonBlocking();
	}
}

// --- DESTRUCTOR ---
TCPSocket::~TCPSocket() {
	if (_fd != -1) {
		close(_fd);
	}
}

// --- GETTER ---
int	TCPSocket::getFD() const { return _fd; }

// --- MOVE LOGIC ---
TCPSocket::TCPSocket(TCPSocket&& other) noexcept {
	_fd = other._fd;
	other._fd = -1;
}

TCPSocket&	TCPSocket::operator=(TCPSocket&& other) noexcept {
	if (this == &other) {
		return *this;
	}

	if (this->_fd != -1) {
		close(_fd);
	}
	_fd = other._fd;
	other._fd = -1;

	return *this;
}

// --- SEND/RECEIVE ---
ssize_t	TCPSocket::sendData(const std::string& data) {
	return send(_fd, data.data(), data.size(), MSG_NOSIGNAL);
}

ssize_t	TCPSocket::receiveData(char* buffer, size_t size) {
	return recv(_fd, buffer, size, 0);
}

// --- SET NON-BLOCKING MODE ---
bool	TCPSocket::setNonBlocking() {
	int flags = fcntl(_fd, F_GETFL, 0);	// get the flags of the socket
	if (flags == -1) {
		std::cout << getTCP_error(TCPErrorCode::SYSTEM_ERROR);
		return false;
	}
	int return_flag = fcntl(_fd, F_SETFL, flags | O_NONBLOCK);	// apply the flag '0_NONBLOCK' without erase other flags
	if (return_flag == -1) {
		std::cout << getTCP_error(TCPErrorCode::SYSTEM_ERROR);
		return false;
	}
	return true;
}
