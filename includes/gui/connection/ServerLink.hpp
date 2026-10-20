/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerLink.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:48:34 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/20 15:13:02 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <poll.h>
# include <csignal>
# include <iostream>
# include <string>
# include <vector>

# include "server/TCPSocket.hpp"
# include "common.h"

class ServerLink
{
    private:
        int			_fd;
		TCPSocket	_sock;
		bool		_connected;
		std::string	_buffer;
		int			RECIVE_SIZE = 1024;
	public:
        ServerLink(int argc, char** argv);
        ~ServerLink();

		// send a specific commande manually
		// \n is automatically added
		void						send_commande(const std::string &commande);

		std::vector<std::string> 	recive();

		bool						isConnected() const;
};
