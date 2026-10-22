/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 10:38:54 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/21 14:59:20 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>

class GasterManager;
class TCPSession;


class CommandHandler {
	private :
		GasterManager&				_manager;

		void handleHandshake(TCPSession& session, const std::string& raw_line);
		void handleGameCommand(TCPSession& session, const std::string& raw_line);

		// COMMANDS
		void	commandUnknown(TCPSession& session, std::string command);
		void	commandConnect(TCPSession& session, std::string argument);
		void	commandQuit(TCPSession& session, std::string argument);
		void	commandWho(TCPSession& session, std::string argument);
		void	commandLook(TCPSession& session, std::string argument);
		void	commandMove(TCPSession& session, std::string argument);
		void	commandTake(TCPSession& session, std::string argument);
		void	commandDrop(TCPSession& session, std::string argument);
		void	commandInventory(TCPSession& session, std::string argument);
		void	commandQuests(TCPSession& session, std::string argument);
		void	commandChat(TCPSession& session, std::string argument);
		void	commandGroupCreate(TCPSession& session, std::string argument);
		void	commandGroupInvite(TCPSession& session, std::string argument);
		void	commandGroupJoin(TCPSession& session, std::string argument);
		void	commandGroupLeave(TCPSession& session, std::string argument);
		void	commandTalk(TCPSession& session, std::string argument);
		void	commandAttack(TCPSession& session, std::string argument);
		void	commandStatus(TCPSession& session, std::string argument);
		void	commandQuest(TCPSession& session, std::string argument);
		void	commandQuestInfo(TCPSession& session, std::string argument);

	public :
		// --- CONSTRUCTOR ---
		explicit CommandHandler(GasterManager& manager);
		// --- DESTRUCTOR ---
		~CommandHandler() = default;

		void	processCommand(TCPSession& session, const std::string& raw_line);

		// --- DEBUG ---
		void	debugTrySimulate(bool try_move);
};
