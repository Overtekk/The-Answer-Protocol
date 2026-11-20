/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 10:47:46 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/20 12:00:45 by roandrie         ###   ########.fr       */
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
# include "config/Enums.hpp"
# include "config/config_messages.h"
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

bool	parseHandshakeCommand(const std::string& cmd_str, HandshakeCommand& cmd) {
    static const std::unordered_map<std::string, HandshakeCommand> handshake_map = {
        {"CONNECT",	HandshakeCommand::CONNECT},
        {"QUIT",	HandshakeCommand::QUIT},
		{"HELP",	HandshakeCommand::HELP}
    };

    auto it = handshake_map.find(cmd_str);
    if (it == handshake_map.end()) {
        return false;
    }

    cmd = it->second;
    return true;
}

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
		{"QUESTS",			GameCommand::QUESTS},
		{"EQUIP",			GameCommand::EQUIP},
		{"INFO_ITEM",		GameCommand::INFO_ITEM},
		{"HELP",			GameCommand::HELP}
	};

	auto it = game_map.find(cmd_str);
	if (it == game_map.end()) {
		return false;
	}

	cmd = it->second;
	return true;
}

bool	parseCombatCommand(const std::string& cmd_str, CombatCommand& cmd) {
	static const std::unordered_map<std::string, CombatCommand> combat_map = {
		{"ATTACK",	CombatCommand::ATTACK},
		{"ACT",		CombatCommand::ACT},
		{"ITEM",	CombatCommand::ITEM},
		{"FLEE",	CombatCommand::FLEE},
		{"SPARE",	CombatCommand::SPARE},
		{"CHECK",	CombatCommand::CHECK},
		{"STATUS",	CombatCommand::STATUS},
		{"HELP",	CombatCommand::HELP}
	};

	auto it = combat_map.find(cmd_str);
	if (it == combat_map.end()) {
		return false;
	}

	cmd = it->second;
	return true;
}

bool	parseShopCommand(const std::string& cmd_str, ShopCommand& cmd) {
	static const std::unordered_map<std::string, ShopCommand> shop_map = {
		{"ITEMS",	ShopCommand::ITEMS},
		{"BUY",		ShopCommand::BUY},
		{"QUIT",	ShopCommand::QUIT},
		{"HELP",	ShopCommand::HELP},
	};

	auto it = shop_map.find(cmd_str);
	if (it == shop_map.end()) {
		return false;
	}

	cmd = it->second;
	return true;
}

bool	parseUsernameLoggingCommand(const std::string& cmd_str, UsernameLoggingCommand& cmd) {
    static const std::unordered_map<std::string, UsernameLoggingCommand> command_map = {
        {"CHANGE",	UsernameLoggingCommand::CHANGE},
        {"KEEP",	UsernameLoggingCommand::KEEP},
		{"DELETE",	UsernameLoggingCommand::DELETE},
		{"QUIT",	UsernameLoggingCommand::QUIT},
		{"HELP",	UsernameLoggingCommand::HELP}
    };

    auto it = command_map.find(cmd_str);
    if (it == command_map.end()) {
        return false;
    }

    cmd = it->second;
    return true;
}

void	lower_the_string(std::string& text) {
	for (char& c : text)
		c = std::tolower(static_cast<unsigned char>(c));
}

void	captalize_the_string(std::string& text) {
	for (char& c : text)
		c = std::toupper(static_cast<unsigned char>(c));
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
	// Client is connected but not 'in game'.
	if (session.getSessionState() == SessionState::CONNECTED)
		handleHandshake(session, raw_line);

	// Client is connected but need to do something with the current username
	else if (session.getSessionState() == SessionState::LOGGING)
		handleUsernameLoggingCommand(session, raw_line);

	// Client is 'in game'.
	else if (session.getSessionState() == SessionState::AUTHENTICATED) {
		// Client is in a combat
		if (session.getSubSessionState() == SubSessionState::IN_COMBAT)
			handleCombatCommand(session, raw_line);

		else if (session.getSubSessionState() == SubSessionState::IN_SHOP)
			handleShopCommand(session, raw_line);

		else
			handleGameCommand(session, raw_line);
	}
}

// * Handle the commands typed in the server console. *
void	CommandHandler::processAdminCommand(const std::string& raw_line) {
	std::string raw_command = clean_line(raw_line);

	std::tuple<std::string, std::string> packed_cmd = extract_command_and_args(raw_command);
	std::string command = std::get<0>(packed_cmd);
	std::string& argument = std::get<1>(packed_cmd);

	if (command == "KILL") {
		if (argument.empty()) {
			print_error(ERR_KILL_CMD);
			return;
		}

		ReturnState state = _manager.adminKill(argument);
		if (state == ReturnState::VALID)
			print_success(SuccessAdminKill(argument));
		else
			print_error(errCantKillPlayer(argument));
	}
}

// * Make the enemies play and send their messages to the right players. Called by the server loop. *
void	CommandHandler::updateCombats(std::unordered_map<int, std::unique_ptr<TCPSession>>& sessions) {
	std::vector<CombatMessage> messages = _manager.updateCombats();

	for (const CombatMessage& message : messages) {
		// Find the session of the player (the manager only knows names, not sockets)
		for (auto& it : sessions) {
			TCPSession& session = *it.second;
			if (session.getUsername() != message.player_name)
				continue;

			session.add_msg_to_buffer(getTCP_OK_operation(message.text));
			if (message.combat_over)
				session.setSubSessionState(SubSessionState::MOVING);
			break;
		}
	}
}


// ============================================================================
// =========================       PRIVATE      ===============================
// ============================================================================
// * Handling commands before the client is in game. *
void	CommandHandler::handleHandshake(TCPSession& session, const std::string& raw_line) {
	// Clear the line received
	std::string raw_command = clean_line(raw_line);
	print_log_message(session, logCommandEntered(raw_command));

	// Get the command and the arguments
	std::tuple<std::string, std::string> packed_cmd = extract_command_and_args(raw_command);
	std::string command = std::get<0>(packed_cmd);
	std::string& argument = std::get<1>(packed_cmd);

	// Check if command exist
	HandshakeCommand cmd;
	if (!parseHandshakeCommand(command, cmd)) {
		commandUnknown(session, command);
		return;
	}

	// Call the good command
	switch (cmd) {
		case HandshakeCommand::CONNECT:	commandConnect(session, argument);		break;
		case HandshakeCommand::QUIT:	commandQuit(session, argument);			break;
		case HandshakeCommand::HELP:	commandHelpHandShake(session, argument);	break;
		default:						commandUnknown(session, command);
	}

	return;
}

// * Handling commands when the client is in game. *
void	CommandHandler::handleGameCommand(TCPSession& session, const std::string& raw_line) {
	// Clear the line received
	std::string raw_command = clean_line(raw_line);
	print_log_message(session, logCommandEntered(raw_command));

	// Get the command and the arguments
	std::tuple<std::string, std::string> packed_cmd = extract_command_and_args(raw_command);
	std::string command = std::get<0>(packed_cmd);
	std::string& argument = std::get<1>(packed_cmd);

	// Check if command exist (two-words command first, ex: "QUEST INFO [QUEST]")
	GameCommand cmd;
	std::tuple<std::string, std::string> packed_sub_cmd = extract_command_and_args(argument);
	std::string compound_command = command + " " + std::get<0>(packed_sub_cmd);
	if (!argument.empty() && parseGameCommand(compound_command, cmd)) {
		command = compound_command;
		argument = std::get<1>(packed_sub_cmd);
	}
	else if (!parseGameCommand(command, cmd)) {
		commandUnknown(session, command);
		return;
	}

	// Call the good command
	switch (cmd) {
		case GameCommand::QUIT:			commandQuit(session, argument);			break;
		case GameCommand::WHO:			commandWho(session, argument);			break;
		case GameCommand::LOOK:			commandLook(session, argument);			break;
		case GameCommand::MOVE:			commandMove(session, argument);			break;
		case GameCommand::TAKE:			commandTake(session, argument);			break;
		case GameCommand::DROP:			commandDrop(session, argument);			break;
		case GameCommand::INVENTORY:	commandInventory(session, argument);	break;
		case GameCommand::QUESTS:		commandQuests(session, argument);		break;
		case GameCommand::QUEST:		commandQuestInfo(session, argument);	break;
		case GameCommand::TALK:			commandTalk(session, argument);			break;
		case GameCommand::ATTACK:		commandAttack(session, argument);		break;
		case GameCommand::INFO_ITEM:	commandItemStat(session, argument);		break;
		case GameCommand::EQUIP:		commandEquip(session, argument);		break;
		case GameCommand::HELP:			commandHelpGame(session, argument);		break;
		case GameCommand::CHAT:			commandChat(session, argument);			break;
		case GameCommand::GROUP_CREATE:	commandGroupCreate(session, argument);	break;
		case GameCommand::GROUP_INVITE:	commandGroupInvite(session, argument);	break;
		case GameCommand::GROUP_JOIN:	commandGroupJoin(session, argument);	break;
		case GameCommand::GROUP_LEAVE:	commandGroupLeave(session, argument);	break;
		default:						commandUnknown(session, command);
	}

	return;
}

// * Handling commands when the client is in combat. *
void	CommandHandler::handleCombatCommand(TCPSession &session, const std::string &raw_line) {
	// Clear the line received
	std::string raw_command = clean_line(raw_line);
	print_log_message(session, logCommandEntered(raw_command));

	// Get the command and the arguments
	std::tuple<std::string, std::string> packed_cmd = extract_command_and_args(raw_command);
	std::string command = std::get<0>(packed_cmd);
	std::string& argument = std::get<1>(packed_cmd);

	// Check if command exist (two-words command first, ex: "ITEM [MOUSE]")
	CombatCommand cmd;
	std::tuple<std::string, std::string> packed_sub_cmd = extract_command_and_args(argument);
	std::string compound_command = command + " " + std::get<0>(packed_sub_cmd);
	if (!argument.empty() && parseCombatCommand(compound_command, cmd)) {
		command = compound_command;
		argument = std::get<1>(packed_sub_cmd);
	}
	else if (!parseCombatCommand(command, cmd)) {
		commandUnknown(session, command);
		return;
	}
	else if (!manageCombatTurn(session))
		return;

	// Call the good command
	switch (cmd) {
		case CombatCommand::ATTACK:			commandCombatAttack(session, argument);	break;
		case CombatCommand::STATUS:			commandCombatStatus(session, argument);	break;
		case CombatCommand::ACT:			commandCombatAct(session, argument);	break;
		case CombatCommand::CHECK:			commandCombatCheck(session, argument);	break;
		case CombatCommand::FLEE:			commandCombatFlee(session, argument);	break;
		case CombatCommand::SPARE:			commandCombatSpare(session, argument);	break;
		case CombatCommand::ITEM:			commandCombatItem(session, argument);	break;
		case CombatCommand::HELP:			commandHelpCombat(session, argument);	break;
		default:							commandUnknown(session, command);
	}

	return;
}

// * Handling commands when the client is in a shop. *
void	CommandHandler::handleShopCommand(TCPSession &session, const std::string &raw_line) {
	// Clear the line received
	std::string raw_command = clean_line(raw_line);
	print_log_message(session, logCommandEntered(raw_command));

	// Get the command and the arguments
	std::tuple<std::string, std::string> packed_cmd = extract_command_and_args(raw_command);
	std::string command = std::get<0>(packed_cmd);
	std::string& argument = std::get<1>(packed_cmd);

	// Check if command exist (two-words command first, ex: "ITEM [MOUSE]")
	ShopCommand cmd;
	std::tuple<std::string, std::string> packed_sub_cmd = extract_command_and_args(argument);
	std::string compound_command = command + " " + std::get<0>(packed_sub_cmd);
	if (!argument.empty() && parseShopCommand(compound_command, cmd)) {
		command = compound_command;
		argument = std::get<1>(packed_sub_cmd);
	}
	else if (!parseShopCommand(command, cmd)) {
		commandUnknown(session, command);
		return;
	}

	// Call the good command
	switch (cmd) {
		case ShopCommand::ITEMS:	commandShopItems(session, argument);	break;
		case ShopCommand::BUY:		commandShopBuy(session, argument);		break;
		case ShopCommand::QUIT:		commandShopQuit(session, argument);		break;
		case ShopCommand::HELP:		commandShopHelp(session, argument);		break;
		default:					commandUnknown(session, command);
	}

	return;
}

// * Handling commands when the client have the same username than an existing player. *
void	CommandHandler::handleUsernameLoggingCommand(TCPSession &session, const std::string &raw_line) {
	std::string raw_command = clean_line(raw_line);
	print_log_message(session, logCommandEntered(raw_command));

	// Get the command and the arguments
	std::tuple<std::string, std::string> packed_cmd = extract_command_and_args(raw_command);
	std::string command = std::get<0>(packed_cmd);
	std::string& argument = std::get<1>(packed_cmd);

	// Check if command exist
	UsernameLoggingCommand cmd;
	if (!parseUsernameLoggingCommand(command, cmd)) {
		commandUnknown(session, command);
		return;
	}

	switch (cmd) {
		case UsernameLoggingCommand::CHANGE:	commandLoggingUsernameChange(session, argument);	break;
		case UsernameLoggingCommand::KEEP:		commandLoggingUsernameKeep(session, argument);		break;
		case UsernameLoggingCommand::DELETE:	commandLoggingUsernameErase(session, argument);		break;
		case UsernameLoggingCommand::QUIT:		commandQuit(session, argument);						break;
		case UsernameLoggingCommand::HELP:		commandHelpLogging(session, argument);				break;
		default:								commandUnknown(session, command);
	}
}

// ============================================================================
// =========================      COMMANDS      ===============================
// ============================================================================
// === UNKOWN ===
void	CommandHandler::commandUnknown(TCPSession& session, std::string& command) {
	print_log_message(session, logCommandRejected(command));
	session.add_msg_to_buffer(getTCP_error(TCPErrorCode::COMMAND_NOT_FOUND));
	return;
}

// === COMMON COMMANDS ===
void	CommandHandler::commandQuit(TCPSession& session, std::string& argument) {
	std::ignore = argument;
	print_log_message(session, LOG_QUIT_REQUEST);

	// disconnect the player from the world
	_manager.disconnectPlayer(session.getUsername());

	session.setSessionState(SessionState::CLOSING);
	session.add_msg_to_buffer(getTCP_OK_operation(SERVER_BYE));
	return;
}

void	CommandHandler::commandCombatStatus(TCPSession &session, std::string& argument) {
	std::ignore = argument;

	session.add_msg_to_buffer(getTCP_OK_operation(_manager.getCombatStatus(session.getUsername())));
}


// === HANDSHAKE COMMANDS ===
void	CommandHandler::commandConnect(TCPSession& session, std::string& argument) {
	if (argument.empty()) {
		session.add_msg_to_buffer(getTCP_error(TCPErrorCode::MISSING_USERNAME));
		print_log_message(session, ERR_LOG_MISSING_USERNAME);
		return;
	}
	if (argument.length() < 3 || argument.length() > 20) {
		session.add_msg_to_buffer(getTCP_error(TCPErrorCode::INVALID_USERNAME));
		print_log_message(session, ERR_LOG_INVALID_USERNAME);
		return;
	}
	if (_manager.checkIfUserExist(argument)) {
		session.add_msg_to_buffer(getTCP_error(TCPErrorCode::NAME_IN_USE));
		print_log_message(session, ERR_LOG_NAME_IN_USE);
		return;
	}
	if (_manager.checkIfPlayerExist(argument)) {
		session.add_msg_to_buffer(userAlreadyExist(argument));
		session.setSessionState(SessionState::LOGGING);
		session.setTmpUsername(argument);
		return;
	}

	session.setUsername(argument);
	session.setSessionState(SessionState::AUTHENTICATED);
	session.add_msg_to_buffer(getTCP_OK_operation(SERVER_OK_CONNECTED));
	_manager.createPlayer(argument);
	print_log_message(session, SuccessNewPlayerCreated(argument));
	return;
}

void	CommandHandler::commandHelpHandShake(TCPSession &session, std::string &argument) {
	// No argument: show the general list
	if (argument.empty()) {
		session.add_msg_to_buffer(getTCP_OK_operation(okHelpHandshakeCommand));
		return;
	}

	captalize_the_string(argument);

	// Unknown command: show the general list
	HandshakeCommand	help_cmd;
	if (!parseHandshakeCommand(argument, help_cmd)) {
		session.add_msg_to_buffer(getTCP_OK_operation(okHelpHandshakeCommand));
		return;
	}

	switch (help_cmd) {
		case HandshakeCommand::CONNECT:	session.add_msg_to_buffer(getTCP_OK_operation(helpConnectCommand));	break;
		case HandshakeCommand::QUIT:	session.add_msg_to_buffer(getTCP_OK_operation(helpQuitCommand));	break;
		case HandshakeCommand::HELP:	session.add_msg_to_buffer(getTCP_OK_operation(helpHelpCommand));	break;
	}
	return;
}

// === GAME COMMANDS ===
void	CommandHandler::commandLook(TCPSession& session, std::string& argument) {
	lower_the_string(argument);

	if (argument == "--details") {
		session.add_msg_to_buffer(getTCP_OK_operation(_manager.getRoomData(session.getUsername(), true)));
		return;
	}

	session.add_msg_to_buffer(getTCP_OK_operation(_manager.getRoomData(session.getUsername(), false)));
	return;
}

void	CommandHandler::commandMove(TCPSession& session, std::string& argument) {
	// Lower the argument (case-insensitive)
	lower_the_string(argument);

	// Check if argument is either "NORTH", "SOUTH", "EAST" or "WEST"
	if (argument != direction_to_string(Direction::NORTH) &&
		argument != direction_to_string(Direction::SOUTH) &&
		argument != direction_to_string(Direction::EAST) &&
		argument != direction_to_string(Direction::WEST)) {
			session.add_msg_to_buffer(getTCP_error(TCPErrorCode::NO_EXIT));
			print_log_message(session, ERR_LOG_BAD_DIRECTION);
			return;
		}

	// Check if player can move
	ReturnState command_state = _manager.movePlayer(session.getUsername(), direction_str_to_enum(argument));
	if (command_state != ReturnState::VALID) {
		sendErrorToUser(session, command_state);
		return;
	}

	// Move player
	session.add_msg_to_buffer(getTCP_OK_operation(okRoom(_manager.getPlayerRoom(session.getUsername()))));
	return;
}

void	CommandHandler::commandWho(TCPSession& session, std::string& argument) {
	std::ignore = argument;
	session.add_msg_to_buffer(getTCP_OK_operation(_manager.getListOfPlayers()));
	return;
}

void	CommandHandler::commandTake(TCPSession& session, std::string& argument) {
	// Lower the argument (case-insensitive)
	lower_the_string(argument);

	// Take item if possible
	ReturnState command_state = _manager.takeItem(session.getUsername(), argument);
	if (command_state != ReturnState::VALID) {
		sendErrorToUser(session, command_state);
		return;
	}

	session.add_msg_to_buffer(getTCP_OK_operation(okTaken(argument)));
	return;
}

void	CommandHandler::commandDrop(TCPSession& session, std::string& argument) {
	// Lower the argument (case-insensitive)
	lower_the_string(argument);

	// Drop item if possible
	ReturnState command_state =_manager.dropItem(session.getUsername(), argument);
	if (command_state != ReturnState::VALID) {
		sendErrorToUser(session, command_state);
		return;
	}

	session.add_msg_to_buffer(getTCP_OK_operation(okDropped(argument)));
	return;
}

void	CommandHandler::commandInventory(TCPSession& session, std::string& argument) {
	lower_the_string(argument);

	if (argument == "--details") {
		session.add_msg_to_buffer(getTCP_OK_operation(_manager.getPlayerInventory(session.getUsername(), true)));
		return;
	}

	session.add_msg_to_buffer(getTCP_OK_operation(_manager.getPlayerInventory(session.getUsername(), false)));
	return;
}

void	CommandHandler::commandItemStat(TCPSession &session, std::string& argument) {
	lower_the_string(argument);

	if (argument.empty()) {
		session.add_msg_to_buffer(getTCP_error(TCPErrorCode::MISSING_ITEM));
		print_log_message(session, getTCP_error(TCPErrorCode::MISSING_ITEM));
		return;
	}

	std::string result = _manager.getItemStat(session.getUsername(), argument);
	if (result.empty()) {
		sendErrorToUser(session, ReturnState::ITEM_NOT_FOUND);
		return;
	}
	session.add_msg_to_buffer(getTCP_OK_operation(result));
	return;
}

void	CommandHandler::commandQuests(TCPSession& session, std::string& argument) {
	std::ignore = argument;

	session.add_msg_to_buffer(getTCP_OK_operation(_manager.getPlayerQuests(session.getUsername())));
	return;
}

void	CommandHandler::commandQuestInfo(TCPSession& session, std::string& argument) {
	lower_the_string(argument);

	session.add_msg_to_buffer(getTCP_OK_operation(_manager.getQuestDescription(session.getUsername(), argument)));
	return;
}

void	CommandHandler::commandTalk(TCPSession& session, std::string& argument) {
	lower_the_string(argument);

	TalkResult result = _manager.getDialogue(session.getUsername(), argument);
	if (result.status == TalkStatus::NOT_FOUND) {
		session.add_msg_to_buffer(getTCP_error(TCPErrorCode::NPC_NOT_FOUND));
		print_log_message(session, ERR_LOG_NPC_NOT_FOUND);
		return;
	}
	else if (result.status == TalkStatus::NO_DIALOGUE) {
		session.add_msg_to_buffer(getTCP_error(TCPErrorCode::NPC_NO_DIALOGUE));
		print_log_message(session, ERR_LOG_NPC_NO_DIALOGUE);
		return;
	}
	else if (result.status == TalkStatus::OPEN_SHOP) {
		session.add_msg_to_buffer(getTCP_OK_operation(logEnterShop(result.entity_name)));
		session.add_msg_to_buffer(getTCP_OK_operation(_manager.enterShop(session.getUsername(), result.entity_id)));
		print_log_message(session, SuccessPlayerEnteredShop(session.getUsername(), result.entity_name));
		session.setSubSessionState(SubSessionState::IN_SHOP);
		return;
	}

	session.add_msg_to_buffer(getTCP_OK_operation(okTalk(result.entity_name, result.text)));
	return;
}

void	CommandHandler::commandEquip(TCPSession &session, std::string& argument) {
	lower_the_string(argument);

	ReturnState command_state = _manager.equipNewWeapon(session.getUsername(), argument);
	if (command_state == ReturnState::VALID)
		session.add_msg_to_buffer(getTCP_OK_operation(okEquipped(argument)));
	else
		sendErrorToUser(session, command_state);
	return;
}

void	CommandHandler::commandAttack(TCPSession &session, std::string& argument) {
	lower_the_string(argument);

	if (argument.empty()) {
		session.add_msg_to_buffer(getTCP_error(TCPErrorCode::MISSING_NPC));
		print_log_message(session, ERR_LOG_MISSING_NPC);
		return;
	}

	ReturnState command_state = _manager.isEnemyType(session.getUsername(), argument);
	if (command_state == ReturnState::VALID) {
		session.add_msg_to_buffer(getTCP_OK_operation(_manager.initCombat(session.getUsername())));
		commandCombatStatus(session, argument);
		session.setSubSessionState(SubSessionState::IN_COMBAT);
	}
	else
		sendErrorToUser(session, command_state);
	return;
}

void	CommandHandler::commandChat(TCPSession &session, std::string &argument) {
	std::ignore = argument;
	session.add_msg_to_buffer("Not implemented yet.");
	return;
}

void	CommandHandler::commandGroupCreate(TCPSession &session, std::string &argument) {
	std::ignore = argument;
	session.add_msg_to_buffer("Not implemented yet.");
	return;
}

void	CommandHandler::commandGroupInvite(TCPSession &session, std::string &argument) {
	std::ignore = argument;
	session.add_msg_to_buffer("Not implemented yet.");
	return;
}

void	CommandHandler::commandGroupJoin(TCPSession &session, std::string &argument) {
	std::ignore = argument;
	session.add_msg_to_buffer("Not implemented yet.");
	return;
}

void	CommandHandler::commandGroupLeave(TCPSession &session, std::string &argument) {
	std::ignore = argument;
	session.add_msg_to_buffer("Not implemented yet.");
	return;
}

void	CommandHandler::commandHelpGame(TCPSession &session, std::string &argument) {
	// No argument: show the general list
	if (argument.empty()) {
		session.add_msg_to_buffer(getTCP_OK_operation(okHelpGameCommand));
		return;
	}

	captalize_the_string(argument);

	// Unknown command: show the general list
	GameCommand	help_cmd;
	if (!parseGameCommand(argument, help_cmd)) {
		session.add_msg_to_buffer(getTCP_OK_operation(okHelpGameCommand));
		return;
	}

	switch (help_cmd) {
		case GameCommand::LOOK:			session.add_msg_to_buffer(getTCP_OK_operation(helpLookCommand));		break;
		case GameCommand::MOVE:			session.add_msg_to_buffer(getTCP_OK_operation(helpMoveCommand));		break;
		case GameCommand::CHAT:			session.add_msg_to_buffer(getTCP_OK_operation(helpChatCommand));		break;
		case GameCommand::WHO:			session.add_msg_to_buffer(getTCP_OK_operation(helpWhoCommand));			break;
		case GameCommand::GROUP_CREATE:	session.add_msg_to_buffer(getTCP_OK_operation(helpGroupCreateCommand));	break;
		case GameCommand::GROUP_INVITE:	session.add_msg_to_buffer(getTCP_OK_operation(helpGroupInviteCommand));	break;
		case GameCommand::GROUP_JOIN:	session.add_msg_to_buffer(getTCP_OK_operation(helpGroupJoinCommand));	break;
		case GameCommand::GROUP_LEAVE:	session.add_msg_to_buffer(getTCP_OK_operation(helpGroupLeaveCommand));	break;
		case GameCommand::TAKE:			session.add_msg_to_buffer(getTCP_OK_operation(helpTakeCommand));		break;
		case GameCommand::DROP:			session.add_msg_to_buffer(getTCP_OK_operation(helpDropCommand));		break;
		case GameCommand::INVENTORY:	session.add_msg_to_buffer(getTCP_OK_operation(helpInventoryCommand));	break;
		case GameCommand::TALK:			session.add_msg_to_buffer(getTCP_OK_operation(helpTalkCommand));		break;
		case GameCommand::ATTACK:		session.add_msg_to_buffer(getTCP_OK_operation(helpAttackCommand));		break;
		case GameCommand::STATUS:		session.add_msg_to_buffer(getTCP_OK_operation(helpStatusCommand));		break;
		case GameCommand::QUEST:		session.add_msg_to_buffer(getTCP_OK_operation(helpQuestCommand));		break;
		case GameCommand::QUESTS:		session.add_msg_to_buffer(getTCP_OK_operation(helpQuestsCommand));		break;
		case GameCommand::EQUIP:		session.add_msg_to_buffer(getTCP_OK_operation(helpEquipCommand));		break;
		case GameCommand::INFO_ITEM:	session.add_msg_to_buffer(getTCP_OK_operation(helpInfoItemCommand));	break;
		case GameCommand::HELP:			session.add_msg_to_buffer(getTCP_OK_operation(helpHelpCommand));		break;
		case GameCommand::QUIT:			session.add_msg_to_buffer(getTCP_OK_operation(helpQuitCommand));		break;
	}
	return;
}

// === COMBAT COMMANDS ===
void	CommandHandler::commandCombatAttack(TCPSession &session, std::string& argument) {
	std::ignore = argument;

	session.add_msg_to_buffer(getTCP_OK_operation( _manager.combatPlayerAttack(session.getUsername())));

	CombatStatus result = _manager.checkCombatStatus(session.getUsername());
	manageCombatResult(session, result, argument);
	return;
}

void	CommandHandler::commandCombatFlee(TCPSession &session, std::string& argument) {
	std::ignore = argument;

	bool result = _manager.tryFlee(session.getUsername());
	if (result) {
		session.add_msg_to_buffer(getTCP_OK_operation(ACT_SUCCESS_FLEE));
		print_log(SuccessPlayerFled(session.getUsername()));
		manageCombatFinish(session);
		return;
	}

	session.add_msg_to_buffer(getTCP_OK_operation(ACT_FAILED_FLEE));
	session.add_msg_to_buffer(getTCP_OK_operation(_manager.changeCombatWhoTurn(session.getUsername(), CombatTurn::ENTITY)));
	return;
}

void	CommandHandler::commandCombatAct(TCPSession &session, std::string& argument) {
	std::ignore = argument;
	session.add_msg_to_buffer("Not implemented yet.");
	return;
}

void	CommandHandler::commandCombatCheck(TCPSession &session, std::string& argument) {
	std::ignore = argument;

	const std::string result = _manager.combatCheck(session.getUsername());
	if (result.empty())
		return;

	session.add_msg_to_buffer(getTCP_OK_operation(result));
}

void	CommandHandler::commandCombatSpare(TCPSession &session, std::string &argument) {
	std::ignore = argument;

	bool result = _manager.trySpare(session.getUsername());
	if (result) {
		session.add_msg_to_buffer(getTCP_OK_operation(ACT_SUCCESS_SPARE));
		manageCombatFinish(session);
		return;
	}

	session.add_msg_to_buffer(getTCP_OK_operation(ACT_FAILED_SPARE));
	session.add_msg_to_buffer(getTCP_OK_operation(_manager.changeCombatWhoTurn(session.getUsername(), CombatTurn::ENTITY)));
	return;
}

void	CommandHandler::commandCombatItem(TCPSession &session, std::string &argument) {
	std::ignore = argument;
	session.add_msg_to_buffer("Not implemented yet.");
	return;
}

void	CommandHandler::commandHelpCombat(TCPSession &session, std::string &argument) {
	// No argument: show the general list
	if (argument.empty()) {
		session.add_msg_to_buffer(getTCP_OK_operation(okHelpCombatCommand));
		return;
	}

	captalize_the_string(argument);

	// Unknown command: show the general list
	CombatCommand	help_cmd;
	if (!parseCombatCommand(argument, help_cmd)) {
		session.add_msg_to_buffer(getTCP_OK_operation(okHelpCombatCommand));
		return;
	}

	switch (help_cmd) {
		case CombatCommand::ATTACK:	session.add_msg_to_buffer(getTCP_OK_operation(helpCombatAttackCommand));	break;
		case CombatCommand::ACT:	session.add_msg_to_buffer(getTCP_OK_operation(helpCombatActCommand));	break;
		case CombatCommand::ITEM:	session.add_msg_to_buffer(getTCP_OK_operation(helpCombatItemCommand));	break;
		case CombatCommand::SPARE:	session.add_msg_to_buffer(getTCP_OK_operation(helpCombatSpareCommand));	break;
		case CombatCommand::FLEE:	session.add_msg_to_buffer(getTCP_OK_operation(helpCombatFleeCommand));	break;
		case CombatCommand::CHECK:	session.add_msg_to_buffer(getTCP_OK_operation(helpCombatCheckCommand));	break;
		case CombatCommand::STATUS:	session.add_msg_to_buffer(getTCP_OK_operation(helpStatusCommand));	break;
		case CombatCommand::HELP:	session.add_msg_to_buffer(getTCP_OK_operation(helpHelpCommand));	break;
	}
	return;
}

// === HANDSHAKE COMMANDS ===
void	CommandHandler::commandShopItems(TCPSession &session, std::string &argument) {
	std::ignore = argument;
	session.add_msg_to_buffer("Not implemented yet.");
	return;
}

void	CommandHandler::commandShopBuy(TCPSession &session, std::string &argument) {
	std::ignore = argument;
	session.add_msg_to_buffer("Not implemented yet.");
	return;
}

void	CommandHandler::commandShopQuit(TCPSession &session, std::string &argument) {
	std::ignore = argument;

	session.add_msg_to_buffer(getTCP_OK_operation(_manager.leaveShop(session.getUsername())));
	session.add_msg_to_buffer(getTCP_OK_operation(logLeaveShop));
	session.setSubSessionState(SubSessionState::MOVING);
	print_log_message(session, SuccessPlayerLeavedShop(session.getUsername()));
	return;
}

void	CommandHandler::commandShopHelp(TCPSession &session, std::string &argument) {
	// No argument: show the general list
	if (argument.empty()) {
		session.add_msg_to_buffer(getTCP_OK_operation(okHelpShopCommmand));
		return;
	}

	captalize_the_string(argument);

	// Unknown command: show the general list
	ShopCommand	help_cmd;
	if (!parseShopCommand(argument, help_cmd)) {
		session.add_msg_to_buffer(getTCP_OK_operation(okHelpShopCommmand));
		return;
	}

	switch (help_cmd) {
		case ShopCommand::ITEMS:	session.add_msg_to_buffer(getTCP_OK_operation(helpShopItemsCommand));	break;
		case ShopCommand::BUY:		session.add_msg_to_buffer(getTCP_OK_operation(helpShopBuyCommand));		break;
		case ShopCommand::QUIT:		session.add_msg_to_buffer(getTCP_OK_operation(helpShopQuitCommand));	break;
		case ShopCommand::HELP:		session.add_msg_to_buffer(getTCP_OK_operation(helpHelpCommand));		break;
	}
	return;
}

// === LOGGING COMMANDS ===
void	CommandHandler::commandLoggingUsernameChange(TCPSession& session, std::string& argument) {
	commandConnect(session, argument);
	return;
}

void	CommandHandler::commandLoggingUsernameKeep(TCPSession& session, std::string& argument) {
	std::ignore = argument;
	std::string wanted_name = session.getTmpUsername();

	 if (!_manager.reconnectPlayer(wanted_name)) {
		session.setSessionState(SessionState::CONNECTED);
		session.add_msg_to_buffer(ERR_CONNECTION_FAILED);
		return;
	 }

	session.setUsername(wanted_name);
	session.setSessionState(SessionState::AUTHENTICATED);
	session.add_msg_to_buffer(getTCP_OK_operation(SERVER_OK_CONNECTED));
	return;
}

void	CommandHandler::commandLoggingUsernameErase(TCPSession& session, std::string& argument) {
	std::ignore = argument;
	std::string wanted_name = session.getTmpUsername();

	if (!_manager.deletePlayer(wanted_name)) {
		session.setSessionState(SessionState::CONNECTED);
		session.add_msg_to_buffer(ERR_CONNECTION_FAILED);
		return;
	}

	commandConnect(session, wanted_name);
	return;
}

void	CommandHandler::commandHelpLogging(TCPSession &session, std::string &argument) {
	// No argument: show the general list
	if (argument.empty()) {
		session.add_msg_to_buffer(getTCP_OK_operation(okHelpLoggingCommand));
		return;
	}

	captalize_the_string(argument);

	// Unknown command: show the general list
	UsernameLoggingCommand	help_cmd;
	if (!parseUsernameLoggingCommand(argument, help_cmd)) {
		session.add_msg_to_buffer(getTCP_OK_operation(okHelpLoggingCommand));
		return;
	}

	switch (help_cmd) {
		case UsernameLoggingCommand::DELETE:	session.add_msg_to_buffer(getTCP_OK_operation(helpDeleteCommand));	break;
		case UsernameLoggingCommand::KEEP:		session.add_msg_to_buffer(getTCP_OK_operation(helpKeepCommand));	break;
		case UsernameLoggingCommand::CHANGE:	session.add_msg_to_buffer(getTCP_OK_operation(helpChangeCommand));	break;
		case UsernameLoggingCommand::QUIT:		session.add_msg_to_buffer(getTCP_OK_operation(helpQuitCommand));	break;
		case UsernameLoggingCommand::HELP:		session.add_msg_to_buffer(getTCP_OK_operation(helpHelpCommand));	break;
	}
	return;
}

// ============================================================================
// ======================       MANAGEMENTS      ==============================
// ============================================================================
bool	CommandHandler::manageCombatTurn(TCPSession& session) {
	if (_manager.getCombatWhoTurn(session.getUsername()) == CombatTurn::NONE) {
		session.add_msg_to_buffer(getTCP_error(TCPErrorCode::NOT_IN_COMBAT));
		return false;
	}

	if (_manager.getCombatWhoTurn(session.getUsername()) == CombatTurn::PLAYER)
		return true;

	session.add_msg_to_buffer(getTCP_error(TCPErrorCode::NOT_YOUR_TURN));
	return false;
}

void	CommandHandler::manageCombatResult(TCPSession &session, CombatStatus& result, std::string& argument) {
	if (result == CombatStatus::PLAYER_LOSE) {
		session.add_msg_to_buffer(getTCP_OK_operation(ACT_COMBAT_WON));
		session.setSubSessionState(SubSessionState::MOVING);
		return;
	}
	else if (result == CombatStatus::ENTITY_LOSE) {
		session.add_msg_to_buffer(getTCP_OK_operation(ACT_COMBAT_LOSE));
		session.setSubSessionState(SubSessionState::MOVING);
		return;
	}
	commandCombatStatus(session, argument);
	session.add_msg_to_buffer(getTCP_OK_operation(_manager.changeCombatWhoTurn(session.getUsername(), CombatTurn::ENTITY)));
	return;
}

void	CommandHandler::manageCombatFinish(TCPSession &session) {
	_manager.finishCombat(session.getUsername());
	session.setSubSessionState(SubSessionState::MOVING);
}

// ============================================================================
// =========================        ERRORS      ===============================
// ============================================================================
void	CommandHandler::sendErrorToUser(TCPSession& session, ReturnState return_error) {
	std::string error_msg = "";

	switch (return_error) {
		case ReturnState::ENTITY_NOT_ENEMY:				error_msg = getTCP_error(TCPErrorCode::NPC_NOT_HOSTILE);			break;
		case ReturnState::PLAYER_NOT_FOUND:				error_msg = getTCP_error(TCPErrorCode::PLAYER_NOT_FOUND);			break;
		case ReturnState::ENTITY_NOT_FOUND:				error_msg = getTCP_error(TCPErrorCode::NPC_NOT_FOUND);			break;
		case ReturnState::ROOM_NOT_FOUND:				error_msg = getTCP_error(TCPErrorCode::ROOM_NOT_FOUND);			break;
		case ReturnState::ITEM_NOT_FOUND:				error_msg = getTCP_error(TCPErrorCode::ITEM_NOT_FOUND);			break;
		case ReturnState::QUEST_NOT_FOUND:				error_msg = getTCP_error(TCPErrorCode::QUEST_NOT_FOUND);			break;
		case ReturnState::ENTITY_NOT_IN_PLAYER_ROOM:	error_msg = getTCP_error(TCPErrorCode::NPC_NOT_IN_ROOM);			break;
		case ReturnState::ITEM_NOT_IN_PLAYER_ROOM:		error_msg = getTCP_error(TCPErrorCode::ITEM_NOT_IN_ROOM); 		break;
		case ReturnState::ITEM_NOT_IN_PLAYER_INVENTORY:	error_msg = getTCP_error(TCPErrorCode::ITEM_NOT_IN_INVENTORY);	break;
		case ReturnState::ITEM_NOT_WEAPON:				error_msg = getTCP_error(TCPErrorCode::ITEM_NOT_WEAPON);			break;
		case ReturnState::VALID:						error_msg = "That shoud'nt be an error.";							break;
		default:										error_msg = "Unknown error";										break;
	}

	session.add_msg_to_buffer(error_msg);
}
