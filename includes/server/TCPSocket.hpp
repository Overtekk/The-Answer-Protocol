/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPSocket.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 11:13:36 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/07 13:23:05 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <unistd.h>
# include <fcntl.h>
# include <sys/socket.h>

# include "protocol/TCP_error.hpp"


// * Network communication endpoint enabling the program to exchange
//   bidirectional data streams. *
class TCPSocket {
	private :
		int	_fd = -1;	// file descriptor: '-1' socket not open or cleaned.

		// --- SET NON-BLOCKING MODE ---
		bool setNonBlocking();

	public :
		// --- CONSTRUCTOR ---
		TCPSocket(int fd);
		// --- DESTRUCTOR ---
		virtual ~TCPSocket();
		// prevent copy of the instance
		TCPSocket(const TCPSocket&) = delete;
		TCPSocket& operator=(const TCPSocket&) = delete;

		// --- GETTER ---
		int	getFD() const;

		// --- MOVE LOGIC ---
		TCPSocket(TCPSocket&& other) noexcept;
		TCPSocket& operator=(TCPSocket&& other) noexcept;

		// --- SEND/RECEIVE ---
		ssize_t sendData(const std::string& data);
		ssize_t receiveData(char* buffer, size_t size);
};
