/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerLink.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:48:34 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/18 10:37:53 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <poll.h>
# include <csignal>
# include <string>
# include <queue>
# include <vector>

# include "server/TCPSocket.hpp"

enum class Commande {
	CONNECT,
	LOOK,
	MOVE,
	QUIT
};


class ServerLink
{
    private:
        int						_fd;
		TCPSocket				_sock;
		bool					_connected;
		std::string				_buffer;
		int						RECIVE_SIZE = 1024;

		std::vector<Commande>	_commande_log;
	public:
		std::queue<std::string>	lines;
		bool					debug;

        ServerLink(int argc, char** argv, bool debug = false);
        ~ServerLink();

		// send a specific commande manually
		// \n is automatically added
		void	send_commande(const std::string &commande, Commande type);

		// recive all data sent by the server
		void 	recive();

	//=========================================================================
	//=============================   SEND   ==================================
	//=========================================================================

	//=========================================================================
	//=============================   GET   ===================================
	//=========================================================================
	const std::string				extractLine(Commande type);
	
	
	const std::string				getConnectReply(const std::string &user_name);

	// return server LOOK reply
	const std::string				getLookReply();
	// return server MOVE reply
	const std::string				getMoveReply();

	bool							connect(const std::string &user_name, bool keep = true);
	
	// send LOOK commande on the first call and retrun the reply when it arrive.
	// in the meantime, it returns an empty string
	const std::string				look();

	// send MOVE commande on the first call and retrun the reply when it arrive.
	// in the meantime, it returns an empty string
	const std::string				move(const std::string &direction);
	
	bool							isConnected() const;
};
