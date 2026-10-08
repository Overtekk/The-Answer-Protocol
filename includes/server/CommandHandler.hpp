/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 10:38:54 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 11:12:31 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>

class GasterManager;
class TCPSession;


class CommandHandler {
	private :
		GasterManager&	_manager;

		void handleHandshake(TCPSession& session, const std::string& raw_line);
		void handleGameCommand(TCPSession& session, const std::string& raw_line);

	public :
		// --- CONSTRUCTOR ---
		explicit CommandHandler(GasterManager& manager);
		// --- DESTRUCTOR ---
		~CommandHandler() = default;

		void processCommand(TCPSession& session, const std::string& raw_line);
};
