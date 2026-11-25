/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerLink.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:48:05 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/25 14:20:44 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
# include <poll.h>
# include <csignal>
#include <pstl/glue_algorithm_defs.h>
# include <string.h>
# include <queue>
# include <string>
# include <utility>

# include "server/TCPSocket.hpp"
# include "gui/connection/ServerLink.hpp"
# include "common.h"


ServerLink::ServerLink(
	int argc,
	char** argv,
	bool debug
):
	_fd(connect_client_to_tcp(argc, argv)),
	_sock(TCPSocket(this->_fd)),
	_connected(this->_fd != -1),
	debug(debug)
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
			char	tmp[RECIVE_SIZE];
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
			// skip this usless line send automaticaly by the server
			if (sub_str != "Use \"connect [USERNAME]\" to launch the game") {
				// std::cout << "DEBUG = [" << sub_str << "]\n";
				this->lines.push(sub_str);
			}
		}
			this->_buffer.erase(0, pos + 1);
			pos = this->_buffer.find('\n');
	}
}

const std::string	ServerLink::extractLine(Commande type) {
	// get the commande result and pop it
	std::string line = std::move(this->lines.front());
	this->lines.pop();

	// remove the commande from the commande_log to recall it later if needed
	_commande_log.erase(std::remove(_commande_log.begin(), _commande_log.end(), type), _commande_log.end());

	return (line);
}

//=============================================================================
//============================= CONNECT  ======================================
//=============================================================================

const std::string	ServerLink::getConnectReply(const std::string &user_name) {
	if (this->lines.empty() == true) { return ("");}

	// if the commande is not the success connect response
	if (this->lines.front().find("OK CONNECTED") != 0) {
		// and if it's not the keep or delet option
		if (this->lines.front().find("\"" + user_name + "\" already exist.") != 0){
			// this is not our msg
			return ("");
		}
	}

	if (this->debug == true) {std::cout << "[DEBUG] Look responce = [" << this->lines.front() << "]\n"; }

	return (this->extractLine(Commande::CONNECT));
}

bool				ServerLink::connect(const std::string &user_name, bool keep) {
	std::string line;
	if (std::count(_commande_log.begin(), _commande_log.end(), Commande::CONNECT) <= 0) {
		// std::cout << "COMMAND_LOG BEFOR SENDING = [" << this->_commande_log.size() << "]\n";
		this->send_commande("CONNECT " + user_name, Commande::CONNECT);
	}

	line = this->getConnectReply(user_name);
	// handle the case where the name was arlready used
	if (line.find("\"" + user_name + "\" already exist.") == 0) {
		std::cout << "== PLAYER ALREADY USED ==\n";
		if (keep == true) {this->send_commande("keep " + user_name, Commande::CONNECT); }
		else {this->send_commande("delete " + user_name, Commande::CONNECT); }
		return false;
	}
	
	// return true when connected
	if (line.find("OK CONNECTED") == 0) {std::cout << "CONNECTED !\n"; return (true); }

	// return false otherwise
	return false;
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

	if (this->debug == true) {std::cout << "[DEBUG] Look responce = [" << this->lines.front() << "]\n"; }

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
		if (this->lines.front().find("ERR 404") == std::string::npos) { // <-- npos is the returned value when find() found nothing
			// this is not our message
			return ("") ;
		}
	}

	if (this->debug == true) {std::cout << "[DEBUG] Move responce = [" << this->lines.front() << "]\n"; }

	// get the commande result and pop it
	std::string line = std::move(this->lines.front());
	this->lines.pop();

	// remove the commande MOVE from the commande_log to recall it later if needed
	_commande_log.erase(std::remove(_commande_log.begin(), _commande_log.end(), Commande::MOVE), _commande_log.end());

	return (line);
}

const std::string	ServerLink::getTakeReply() {
	if (this->lines.empty() == true) { return ("");}

	// if the commande is not the take response
	if (this->lines.front().find("OK taken=") != 0) {
		// and if there is no movement error msg
		if (this->lines.front().find("ERR 408") == std::string::npos) {
			// this is not our message
			return ("");
		}
	}

	if (this->debug == true) {std::cout << "[DEBUG] Take responce = [" << this->lines.front() << "]\n"; }

	// get the command result ad pop it
	std::string line = move(this->lines.front());
	this->lines.pop();

	// remove the commande TAKE from the commande_log to recall it later if needed
	_commande_log.erase(std::remove(_commande_log.begin(), _commande_log.end(), Commande::TAKE), _commande_log.end());
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
		this->send_commande("MOVE " + direction, Commande::MOVE);
	}
	return (this->getMoveReply());
}

const std::string	ServerLink::take(const std::string &item_id) {
	// if take was already sent by someone we will wait the next call
	if (std::count(_commande_log.begin(), _commande_log.end(), Commande::TAKE) <= 0) {
		this->send_commande("TAKE " + item_id, Commande::TAKE);
	}
	return (this->getTakeReply());
}

bool				ServerLink::isConnected() const
{
	return (this->_connected);
}
