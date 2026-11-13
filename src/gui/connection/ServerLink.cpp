/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerLink.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:48:05 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/13 14:02:24 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
# include <poll.h>
# include <csignal>
# include <string.h>
# include <queue>
#include <string>
#include <type_traits>
#include <utility>

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
	this->send_commande("QUIT", Commande::QUIT);
	close(this->_fd);
}

void	ServerLink::recive() {
	pollfd 						fdp = pollfd {this->_fd, POLLIN, 0};
	size_t						pos;
	
	while (this->_connected and poll(&fdp, 1, 0) > 0)
	{
		if (fdp.revents & (POLLIN | POLLHUP)) {
			char	tmp[this->RECIVE_SIZE];
			ssize_t	bytes_readed;
			bytes_readed = this->_sock.receiveData(tmp, sizeof(tmp));

			if (bytes_readed > 0) {
				this->_buffer.append(tmp, bytes_readed);
			}
			// If the server send a shutdown signal, bytes_readed is equal to 0
			else if (bytes_readed == 0)
			{
				this->_connected = false;
			}
		}
	}

	pos = this->_buffer.find('\n');
	while (pos != std::string::npos)
	{
		const std::string &sub_str = _buffer.substr(0, pos);

		if (sub_str.length() > 0) {
			this->lines.push(sub_str);
		}
			this->_buffer.erase(0, pos + 1);
			pos = this->_buffer.find('\n');
	}
}

//=============================================================================
//=============================   SEND   ======================================
//=============================================================================

void				ServerLink::send_commande(const std::string &commande, Commande type)
{
	this->_sock.sendData(commande + "\n");
	this->_commande_log.push_back(type);
}

//=============================================================================
//=============================   GET   =======================================
//=============================================================================

const std::string	ServerLink::getLookReply() {
	if (this->lines.empty() == true) { return (""); }
	if (this->lines.front().find("OK { \"room\"") != 0) { return (""); }

	// get the commande result and pop it
	std::string line = std::move(this->lines.front());
	this->lines.pop();
	
	// remove the commande LOOK from the commande_log to recall it later if needed
	_commande_log.erase(std::remove(_commande_log.begin(), _commande_log.end(), Commande::LOOK), _commande_log.end());

	return (line);
}

const std::string	ServerLink::getMoveReply() {
	if (this->lines.empty() == true) { return ("");}

	// if the commande is not the move response
	if (this->lines.front().find("OK room=") != 0) {
		// and if there is no movement error msg
		if (this->lines.front().find("Invalid movement direction.") != std::string::npos) { // <-- npos is the returned value when find() found nothing
			// this is not our message
			return ("") ;
		}
	}

	// get the commande result and pop it
	std::string line = std::move(this->lines.front());
	this->lines.pop();

	// remove the commande LOOK from the commande_log to recall it later if needed
	_commande_log.erase(std::remove(_commande_log.begin(), _commande_log.end(), Commande::MOVE), _commande_log.end());
	
	return (line);
}

const std::string	ServerLink::look() {
	// if look was already sent by someone we will wait the next call
	if (std::count(_commande_log.begin(), _commande_log.end(), Commande::LOOK) <= 0) {
		// std::cout << "COMMAND_LOG BEFOR SENDING = [" << this->_commande_log.size() << "]\n";
		this->send_commande("LOOK --details", Commande::LOOK);
	}
	return (this->getLookReply());
}

const std::string	ServerLink::move(const std::string &direction) {
	// if move was already sent by someone we will wait the next call
	if (std::count(_commande_log.begin(), _commande_log.end(), Commande::MOVE) <= 0) {
		this->send_commande("MOVE " + direction, Commande::LOOK);
	}
	return (this->getMoveReply());
}

bool				ServerLink::isConnected() const
{
	return (this->_connected);
}
