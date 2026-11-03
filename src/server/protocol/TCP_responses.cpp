/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_responses.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 15:01:39 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/03 09:31:48 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "protocol/TCP_error.hpp"

namespace {
	struct ErrorInfo { int code; const char* name; const char* description; };

	ErrorInfo getErrorInfo(TCPErrorCode e) {
		switch (e) {
			case TCPErrorCode::COMMAND_NOT_FOUND:		return {127, "COMMAND_NOT_FOUND",		"This command doesn't exist."};
			case TCPErrorCode::NAME_IN_USE:				return {201, "NAME_IN_USE",				"Requested username already taken."};
			case TCPErrorCode::INVALID_USERNAME:		return {202, "INVALID_USERNAME",		"Username length is 3-20 characters."};
			case TCPErrorCode::MISSING_USERNAME:		return {203, "MISSING_USERNAME",		"Username is missing after the command."};
			case TCPErrorCode::MISSING_NPC:				return {204, "MISSING_NPC",				"NPC is missing after the command."};
			case TCPErrorCode::MISSING_ITEM:			return {205, "MISSING_ITEM",			"Item is missing after the command."};
			case TCPErrorCode::NO_EXIT:					return {301, "NO_EXIT",					"Invalid movement direction."};
			case TCPErrorCode::NOT_IN_GROUP:			return {401, "NOT_IN_GROUP",			"Group operation requires group membership."};
			case TCPErrorCode::ALREADY_IN_GROUP:		return {402, "ALREADY_IN_GROUP",		"Player already belongs to a group."};
			case TCPErrorCode::ITEM_NOT_FOUND:			return {404, "ITEM_NOT_FOUND",			"Requested item not available in room."};
			case TCPErrorCode::ITEM_NOT_IN_INVENTORY:	return {404, "ITEM_NOT_IN_INVENTORY",	"Requested item not in player inventory."};
			case TCPErrorCode::NPC_NOT_FOUND:			return {404, "NPC_NOT_FOUND",			"Requested NPC not present in room."};
			case TCPErrorCode::PLAYER_NOT_FOUND:		return {404, "PLAYER_NOT_FOUND",		"The player can't be found."};
			case TCPErrorCode::ROOM_NOT_FOUND:			return {404, "ROOM_NOT_FOUND",			"The room can't be found."};
			case TCPErrorCode::QUEST_NOT_FOUND:			return {404, "QUEST_NOT_FOUND",			"The requested quest can't be found."};
			case TCPErrorCode::NPC_NOT_HOSTILE:			return {405, "NPC_NOT_HOSTILE",			"NPC cannot be attacked (not an enemy)."};
			case TCPErrorCode::NO_QUEST_AVAILABLE:		return {406, "NO_QUEST_AVAILABLE",		"NPC has no quests or quest already completed."};
			case TCPErrorCode::NPC_NO_DIALOGUE:			return {407, "NPC_NO_DIALOGUE",			"It doesn't want to speak."};
			case TCPErrorCode::NPC_NOT_IN_ROOM:			return {408, "NPC_NOT_IN_ROOM",			"The requested NPC is not in the same room as you."};
			case TCPErrorCode::ITEM_NOT_IN_ROOM:		return {408, "ITEM_NOT_IN_ROOM",		"Item not in the same room as you."};
			case TCPErrorCode::ITEM_NOT_WEAPON:			return {409, "ITEM_NOT_WEAPON",			"Item requested is not a weapon."};
			case TCPErrorCode::CONNECTION_FAILED:		return {900, "CONNECTION_FAILED",		"Connection establishment failed."};
			case TCPErrorCode::CONNEXION_ERROR:			return {900, "CONNEXION ERROR",			"You have been disconnected."};
			case TCPErrorCode::SEND_FAILED:				return {901, "SEND_FAILED",				"Message transmission failed."};
			case TCPErrorCode::SYSTEM_ERROR:			return {904, "SYSTEM_ERROR",			"Server can't be opened due to system error. Please retry."};
		}
		return {999, "UNKNOWN_ERROR", "Unknown error code"};
	}
}

// ===== PUBLIC =====
// * Return the error and the description to the client. *
std::string getTCP_error(TCPErrorCode e) {
	ErrorInfo i = getErrorInfo(e);
	return "ERR " + std::to_string(i.code) + " " + i.name + " : " + i.description + "\n\n";
}

// * Return a string with an 'ok' at the start for successfully operation. *
std::string	getTCP_OK_operation(const std::string& msg) {
	return ("OK " + msg + "\n\n");
}
