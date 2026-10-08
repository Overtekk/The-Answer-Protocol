/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_socket.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 11:23:08 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 09:49:55 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <utility>
# include <unistd.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <cstring>
# include <cerrno>
# include "server/TCPSocket.hpp"
# include "utils.h"

// --- CONSTRUCTOR ---
TCPSocket::TCPSocket(int fd): _fd(fd) {
	// -1 means "no socket yet": nothing to configure.
	if (fd != -1) {
		setNonBlocking();
	}
}

// std::exchange(a, b): returns the old value of 'a' AND sets 'a' to 'b' in one expression.
// Here: we steal the fd from 'other' and leave it with -1, so its destructor won't close it.
TCPSocket::TCPSocket(TCPSocket&& other) noexcept
	: _fd(std::exchange(other._fd, -1)) {}

// Move assignment: we may already own an fd, so we must close it before taking the new one.
// The 'this != &other' check protects against 'a = std::move(a)'.
TCPSocket&	TCPSocket::operator=(TCPSocket&& other) noexcept {
	if (this != &other) {
		if (_fd != -1) {
			close(_fd);
		}
		_fd = std::exchange(other._fd, -1);
	}
	return *this;
}

// --- DESTRUCTOR ---
TCPSocket::~TCPSocket() {
	if (_fd != -1) {
		close(_fd);
	}
}

// --- GETTER ---
int	TCPSocket::getFD() const { return _fd; }

// --- SEND/RECEIVE ---
ssize_t	TCPSocket::sendData(const std::string& data) {
	// MSG_NOSIGNAL: without it, writing to a closed connection raises SIGPIPE and kills the server.
	return send(_fd, data.data(), data.size(), MSG_NOSIGNAL);
}

ssize_t	TCPSocket::receiveData(char* buffer, size_t size) {
	return recv(_fd, buffer, size, 0);
}

// --- SET NON-BLOCKING MODE ---
bool	TCPSocket::setNonBlocking() {
	int flags = fcntl(_fd, F_GETFL, 0);	// get the flags of the socket
	if (flags == -1) {
		print_error("fcntl(F_GETFL): " + std::string(std::strerror(errno)));
		return false;
	}
	int return_flag = fcntl(_fd, F_SETFL, flags | O_NONBLOCK);	// apply the flag '0_NONBLOCK' without erase other flags
	if (return_flag == -1) {
		print_error("fcntl: " + std::string(std::strerror(errno)));
		return false;
	}
	return true;
}
