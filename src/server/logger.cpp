/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:44:33 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 15:47:36 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server/logger.hpp"
# include "utils.h"

// * Print a log in the console terminal and save it to the log file.*
void	print_log_message(TCPSession& session, const std::string& log_msg) {
	std::string	formatted_log_msg = "";

	if (session.getUsername().empty()) {
		formatted_log_msg = "[" + session.getIP() + "]: " + log_msg;
	}
	else {
		formatted_log_msg = "[" + session.getIP() + "](" + session.getUsername() + "):" + log_msg;
	}

	// if (_save_log_in_file) {
	// 	// todo: print logs to a file
	// }

	print_log(formatted_log_msg);
}
