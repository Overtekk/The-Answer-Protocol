/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 10:47:46 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/19 15:59:14 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>
# include <unordered_map>
# include <cctype>
# include <tuple>

# include "server/CommandHandler.hpp"
# include "server/TCPSession.hpp"
# include "server/TCP_EnumsType.hpp"
# include "server/manager/GasterManager.hpp"
# include "server/logger.hpp"
# include "protocol/TCP_error.hpp"
# include "utils.h"

# define IGNORED_CHARS	" \t\r\n"

// ============================================================================
// =========================       UTILS      =================================
// ============================================================================
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

// * Extract the command and the argument from a raw command string. *
std::tuple<std::string, std::string>	extract_command_and_args(std::string& raw_cmd) {
	// Substring the argument from the command (ex: "'CONNECT' + 'KRIS'")
	std::string command = raw_cmd;
	std::string argument = "";

	// Find the first word (will be the command)
	size_t	index_arg = raw_cmd.find_first_of(' ');
	if (index_arg != std::string::npos) {
		// Extract the command
		command = raw_cmd.substr(0, index_arg);
		// Extract the argument
		argument = clean_line(raw_cmd.substr(index_arg + 1));
	}

	// Capitalize the command
	for (char& c : command) {
		c = std::toupper(static_cast<unsigned char>(c));
	}

	return std::make_tuple(command, argument);
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

// Lower the string send in parameters
void	lower_the_string(std::string& text) {
	for (char& c : text) {
		c = std::tolower(static_cast<unsigned char>(c));
	}
}

// ============================================================================
// =========================       METHODS      ===============================
// ============================================================================
// --- CONSTRUCTOR ---
CommandHandler::CommandHandler(GasterManager& manager): _manager(manager) {}

// ============================================================================
// =========================       PUBLIC      ================================
// ============================================================================
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

// ============================================================================
// =========================       PRIVATE      ===============================
// ============================================================================
// * Handling commands before the client is in game. *
void	CommandHandler::handleHandshake(TCPSession& session, const std::string& raw_line) {
	// Clear the line received
	std::string raw_command = clean_line(raw_line);
	print_log_message(session, "entered command: " + raw_command);

	// Get the command and the arguments
	std::tuple<std::string, std::string> packed_cmd = extract_command_and_args(raw_command);
	std::string command = std::get<0>(packed_cmd);
	std::string argument = std::get<1>(packed_cmd);

	// Check if command exist
	HandshakeCommand cmd;
	if (!parseHandshakeCommand(command, cmd)) {
		commandUnknown(session, command);
		return;
	}

	// Call the good command
	switch (cmd) {
		case HandshakeCommand::CONNECT:	commandConnect(session, argument); break;
		case HandshakeCommand::QUIT:	commandQuit(session, argument); break;
		default:						commandUnknown(session, command);
	}

	return;
}

// * Handling commands when the client is in game. *
void	CommandHandler::handleGameCommand(TCPSession& session, const std::string& raw_line) {
	// Clear the line received
	std::string raw_command = clean_line(raw_line);
	print_log_message(session, "entered command: " + raw_command);

	// Get the command and the arguments
	std::tuple<std::string, std::string> packed_cmd = extract_command_and_args(raw_command);
	std::string command = std::get<0>(packed_cmd);
	std::string argument = std::get<1>(packed_cmd);

	// Check if command exist
	GameCommand cmd;
	if (!parseGameCommand(command, cmd)) {
		commandUnknown(session, command);
		return;
	}

	// Call the good command
	switch (cmd) {
		case GameCommand::QUIT:			commandQuit(session, argument); break;
		case GameCommand::WHO:			commandWho(session, argument); break;
		case GameCommand::LOOK:			commandLook(session, argument); break;
		case GameCommand::MOVE:			commandMove(session, argument); break;
		case GameCommand::TAKE:			commandTake(session, argument); break;
		case GameCommand::DROP:			commandDrop(session, argument); break;
		case GameCommand::INVENTORY:	commandInventory(session, argument); break;
		default:						commandUnknown(session, command);
	}

	return;
}

// ============================================================================
// =========================      COMMANDS      ===============================
// ============================================================================
void	CommandHandler::commandUnknown(TCPSession& session, std::string command) {
	print_log_message(session, "rejected command: '" + command + "'");
	session.add_msg_to_buffer(getTCP_error(TCPErrorCode::COMMAND_NOT_FOUND));
	return;
}

void	CommandHandler::commandConnect(TCPSession& session, std::string argument) {
	if (argument.empty()) {
		session.add_msg_to_buffer(getTCP_error(TCPErrorCode::MISSING_USERNAME));
		print_log_message(session, "error: 203 MISSING_USERNAME");
		return;
	}
	if (argument.length() < 3 || argument.length() > 20) {
		session.add_msg_to_buffer(getTCP_error(TCPErrorCode::INVALID_USERNAME));
		print_log_message(session, "error: 202 INVALID_USERNAME");
		return;
	}
	if (_manager.checkIfUserExist(argument)) {
		session.add_msg_to_buffer(getTCP_error(TCPErrorCode::NAME_IN_USE));
		print_log_message(session, "error: 201 NAME_IN_USE");
		return;
	}

	session.setUsername(argument);
	session.setSessionState(SessionState::AUTHENTICATED);
	session.add_msg_to_buffer(getTCP_OK_operation("CONNECTED"));
	_manager.createPlayer(argument);
	print_log_message(session, "new player created: '" + argument + "'");
	return;
}

void	CommandHandler::commandQuit(TCPSession& session, std::string argument) {
	std::ignore = argument;
	print_log_message(session, "requested graceful disconnect (QUIT).");
	session.setSessionState(SessionState::CLOSING);
	session.add_msg_to_buffer(getTCP_OK_operation("bye"));
	return;
}

void	CommandHandler::commandWho(TCPSession& session, std::string argument) {
	std::ignore = argument;
	session.add_msg_to_buffer(getTCP_OK_operation(_manager.getListOfPlayers()));
	return;
}

void	CommandHandler::commandLook(TCPSession& session, std::string argument) {
	lower_the_string(argument);

	if (argument == "--details") {
		session.add_msg_to_buffer(getTCP_OK_operation(_manager.getRoomData(session.getUsername(), true)));
		return;
	}

	session.add_msg_to_buffer(getTCP_OK_operation(_manager.getRoomData(session.getUsername(), false)));
	return;
}

void	CommandHandler::commandMove(TCPSession& session, std::string argument) {
	// Lower the argument (case-insensitive)
	lower_the_string(argument);

	// Check if argument is either "NORTH", "SOUTH", "EAST" or "WEST"
	if (argument != direction_to_string(Direction::NORTH) &&
		argument != direction_to_string(Direction::SOUTH) &&
		argument != direction_to_string(Direction::EAST) &&
		argument != direction_to_string(Direction::WEST)) {
			session.add_msg_to_buffer(getTCP_error(TCPErrorCode::NO_EXIT));
			print_log_message(session, "error: 301 Invalid movement direction (bad input).");
			return;
		}

	// Check if player can move
	if (!_manager.movePlayer(session.getUsername(), direction_str_to_enum(argument))) {
		session.add_msg_to_buffer(getTCP_error(TCPErrorCode::NO_EXIT));
		print_log_message(session, "error: 301 Invalid movement direction (bad direction).");
		return;
	}

	// Move player
	session.add_msg_to_buffer(getTCP_OK_operation("room=" + _manager.getPlayerRoom(session.getUsername())));
	return;
}

void	CommandHandler::commandTake(TCPSession& session, std::string argument) {
	// Lower the argument (case-insensitive)
	lower_the_string(argument);

	// Take item if possible
	if (!_manager.takeItem(session.getUsername(), argument)) {
		session.add_msg_to_buffer(getTCP_error(TCPErrorCode::ITEM_NOT_FOUND));
		print_log_message(session, "error: 404 Requested item not available in room..");
		return;
	}

	session.add_msg_to_buffer(getTCP_OK_operation("taken=" + argument));
	return;
}

void	CommandHandler::commandDrop(TCPSession& session, std::string argument) {
	// Lower the argument (case-insensitive)
	lower_the_string(argument);

	// Drop item if possible
	if (!_manager.dropItem(session.getUsername(), argument)) {
		session.add_msg_to_buffer(getTCP_error(TCPErrorCode::ITEM_NOT_IN_INVENTORY));
		print_log_message(session, "error: 404 Requested item not in player inventory..");
		return;
	}

	session.add_msg_to_buffer(getTCP_OK_operation("dropped=" + argument));
	return;
}

void	CommandHandler::commandInventory(TCPSession& session, std::string argument) {
	lower_the_string(argument);

	if (argument == "--details") {
		session.add_msg_to_buffer(getTCP_OK_operation(_manager.getPlayerInventory(session.getUsername(), true)));
		return;
	}

	session.add_msg_to_buffer(getTCP_OK_operation(_manager.getPlayerInventory(session.getUsername(), false)));
}

// ============================================================================
// =========================        DEBUG      ================================
// ============================================================================
void	CommandHandler::debugTrySimulate(bool try_move) {
	_manager.debugTrySimulate(try_move);
}
