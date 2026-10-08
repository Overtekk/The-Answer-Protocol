/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPSocket.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 11:13:36 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 09:50:44 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <sys/types.h>


// * Network communication endpoint enabling the program to exchange
//   bidirectional data streams. *
class TCPSocket {
	private :
		int	_fd = -1;	// file descriptor: '-1' socket not open or cleaned.

		// --- SET NON-BLOCKING MODE ---
		bool setNonBlocking();

	public :
		// --- CONSTRUCTOR ---
		explicit TCPSocket(int fd = -1);
		// --- DESTRUCTOR ---
		~TCPSocket();
		// prevent copy of the instance
		TCPSocket(const TCPSocket&) = delete;
		TCPSocket& operator=(const TCPSocket&) = delete;
		TCPSocket(TCPSocket&& other) noexcept;
		TCPSocket& operator=(TCPSocket&& other) noexcept;

		// --- GETTER ---
		int	getFD() const;

		// --- SEND/RECEIVE ---
		ssize_t sendData(const std::string& data);
		ssize_t receiveData(char* buffer, size_t size);
};
