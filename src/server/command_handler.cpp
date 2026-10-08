/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 10:47:46 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 14:53:14 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>
# include <unordered_map>

# include "server/CommandHandler.hpp"
# include "server/TCPSession.hpp"
# include "server/TCP_EnumsType.hpp"
# include "server/manager/GasterManager.hpp"
# include "protocol/TCP_error.hpp"
# include "utils.h"

# define IGNORED_CHARS	" \t\r\n"

// ======= UTILS =======
// * Clean the line from spaces, ´\t', '\r' and , '\n'. *
std::string	clean_line(const std::string& raw_line) {
	std::string	ignored_chars = IGNORED_CHARS;

	size_t	begin_index = 0;
	size_t	end_index = 0;
	begin_index = raw_line.find_first_not_of(ignored_chars);
	if (begin_index == std::string::npos) {
		return "";
	}

	end_index = raw_line.find_last_not_of(ignored_chars);

	std::string cleaned_output = raw_line.substr(begin_index, (end_index - begin_index + 1));

	return cleaned_output;
}

// * Check if the command sent is correct. *
bool	parseHandshakeCommand(const std::string& cmd_str, HandshakeCommand& cmd) {
    static const std::unordered_map<std::string, HandshakeCommand> handshake_map = {
        {"CONNECT",	HandshakeCommand::CONNECT},
        {"QUIT",	HandshakeCommand::QUIT}
    };

    auto it = handshake_map.find(cmd_str);
    if (it == handshake_map.end()) {
        return false;
    }

    cmd = it->second;
    return true;
}

// * Check if the command sent is correct. *
bool	parseGameCommand(const std::string& cmd_str, GameCommand& cmd) {
	static const std::unordered_map<std::string, GameCommand> game_map = {
		{"LOOK",			GameCommand::LOOK},
		{"MOVE",			GameCommand::MOVE},
		{"QUIT",			GameCommand::QUIT},
		{"CHAT",			GameCommand::CHAT},
		{"WHO",				GameCommand::WHO},
		{"GROUP_CREATE",	GameCommand::GROUP_CREATE},
		{"GROUP_INVITE",	GameCommand::GROUP_INVITE},
		{"GROUP_JOIN",		GameCommand::GROUP_JOIN},
		{"GROUP_LEAVE",		GameCommand::GROUP_LEAVE},
		{"TAKE",			GameCommand::TAKE},
		{"DROP",			GameCommand::DROP},
		{"INVENTORY",		GameCommand::INVENTORY},
		{"TALK",			GameCommand::TALK},
		{"ATTACK",			GameCommand::ATTACK},
		{"STATUS",			GameCommand::STATUS},
		{"QUEST",			GameCommand::QUEST},
		{"QUESTS",			GameCommand::QUESTS}
	};

	auto it = game_map.find(cmd_str);
	if (it == game_map.end()) {
		return false;
	}

	cmd = it->second;
	return true;
}

// ======= METHODS =======
// --- CONSTRUCTOR ---
CommandHandler::CommandHandler(GasterManager& manager):
	_manager(manager) {}

// ======= PUBLIC =======
// * Check the line of the current session and return the correct command. *
void	CommandHandler::processCommand(TCPSession& session, const std::string& raw_line) {
	// Client is connect but not 'in game'.
	if (session.getSessionState() == SessionState::CONNECTED) {
		handleHandshake(session, raw_line);
	}
	// Client is 'in game'.
	else if (session.getSessionState() == SessionState::AUTHENTICATED) {
		handleGameCommand(session, raw_line);
	}
}

// ======= PRIVATE ======
// * Handling commands before the client is in game. *
void	CommandHandler::handleHandshake(TCPSession& session, const std::string& raw_line) {
	std::string raw_command = clean_line(raw_line);

	if (session.getUsername().empty()) {
		print_log("[" + session.getIP() + "] entered command: " + raw_command);
	}
	else {
		print_log("[" + session.getIP() + "](" + session.getUsername() + ") entered command: " + raw_command);
	}


	// Substring the argument from the command (ex: 'CONNECT KRIS')
	std::string command = raw_command;
	std::string argument = "";

	size_t	index_arg = raw_command.find_first_of(' ');
	if (index_arg != std::string::npos) {
		command = raw_command.substr(0, index_arg);
		argument = clean_line(raw_command.substr(index_arg + 1));;
	}

	// Check if it's the connect command
	HandshakeCommand cmd;
	if (parseHandshakeCommand(command, cmd))
	{
		if (cmd == HandshakeCommand::CONNECT) {
			// No argument provided
			if (argument.empty()) {
				session.add_msg_to_buffer(getTCP_error(TCPErrorCode::MISSING_USERNAME));
				return;
			}
			// Username too short/too long
			if (argument.length() < 3 || argument.length() > 20) {
				session.add_msg_to_buffer(getTCP_error(TCPErrorCode::INVALID_USERNAME));
				return;
			}
			// Duplicated username
			if (_manager.checkIfUserExist(argument)) {
				session.add_msg_to_buffer(getTCP_error(TCPErrorCode::NAME_IN_USE));
				return;
			}
			// GOOD
			session.setUsername(argument);
			session.setSessionState(SessionState::AUTHENTICATED);
			session.add_msg_to_buffer(getTCP_OK_operation("CONNECTED"));
			_manager.create_player(argument);
			print_log("New player created: '" + argument + "'");
			return;
		}
		// Check if it's the quit command
		else if (cmd == HandshakeCommand::QUIT) {
			session.setSessionState(SessionState::CLOSING);
			session.add_msg_to_buffer(getTCP_OK_operation("bye"));
			return;
		}
		// Unkown command
		else {
			session.add_msg_to_buffer(getTCP_error(TCPErrorCode::COMMAND_NOT_FOUND));
			return;
		}
	}
	return;
}

// * Handling commands when the client is in game. *
void	CommandHandler::handleGameCommand(TCPSession& session, const std::string& raw_line) {
	std::ignore = session;
	std::ignore = raw_line;
}
