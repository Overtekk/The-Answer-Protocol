/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerLink.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:48:05 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/20 15:24:15 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <poll.h>
# include <csignal>
# include <iostream>
# include <string.h>

# include "server/TCPSocket.hpp"
# include "gui/connection/ServerLink.hpp"
# include "common.h"


ServerLink::ServerLink(
	int argc,
	char** argv
):
	_fd(connect_client_to_tcp(argc, argv)),
	_sock(TCPSocket(this->_fd)),
	_connected(this->_fd != -1)
{}

ServerLink::~ServerLink() {
	this->send_commande("QUIT");
	close(this->_fd);
}

void						ServerLink::send_commande(const std::string &commande)
{
	this->_sock.sendData(commande + "\n");
}

std::vector<std::string> 	ServerLink::recive()
{
	std::vector<std::string>	lines;
	pollfd 						fdp = pollfd {this->_fd, POLLIN, 0};
	size_t						pos;
	
	while (this->_connected and poll(&fdp, 1, 0) > 0)
	{
		if (fdp.revents & (POLLIN | POLLHUP)) {
			char	tmp[this->RECIVE_SIZE];
			ssize_t	bytes_readed;
			bytes_readed = this->_sock.receiveData(tmp, sizeof(tmp));

			if (bytes_readed > 0) {
				this->_buffer.append(tmp);
			}
			// If the server send a shutdown signal, bytes_readed is equal to 0
			else if (bytes_readed == 0)
			{
				this->_connected = false;
			}
		}
	}

	pos = _buffer.find('\n');
	while (pos != std::string::npos)
	{
		lines.push_back(_buffer.substr(0, pos));
		this->_buffer.erase(0, pos + 1);
		pos = _buffer.find('\n');
	}
	return (lines);
}

bool						ServerLink::isConnected() const
{
	return (this->_connected);
}