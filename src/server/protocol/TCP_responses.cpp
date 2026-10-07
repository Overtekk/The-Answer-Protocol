/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_responses.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 15:01:39 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/07 14:07:15 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "protocol/error_code.hpp"

std::string getTCP_errorDescription(TCPErrorCode error_code);

// (PUBLIC)
// * Return a string that matches the specified error code. *
std::string getTCP_error(TCPErrorCode error_code, bool add_description) {
	std::string err_message;

	switch (error_code) {
		case TCPErrorCode::NAME_IN_USE:
			err_message = "201 NAME_IN_USE";
			break;
		case TCPErrorCode::INVALID_USERNAME:
			err_message = "202 INVALID_USERNAME";
			break;
		case TCPErrorCode::NO_EXIT:
			err_message = "301 NO_EXIT";
			break;
		case TCPErrorCode::NOT_IN_GROUP:
			err_message = "401 NOT_IN_GROUP";
			break;
		case TCPErrorCode::ALREADY_IN_GROUP:
			err_message = "402 ALREADY_IN_GROUP";
			break;
		case TCPErrorCode::ITEM_NOT_FOUND:
			err_message = "404 ITEM_NOT_FOUND";
			break;
		case TCPErrorCode::ITEM_NOT_IN_INVENTORY:
			err_message = "404 ITEM_NOT_IN_INVENTORY";
			break;
		case TCPErrorCode::NPC_NOT_FOUND:
			err_message = "404 NPC_NOT_FOUND";
			break;
		case TCPErrorCode::NPC_NOT_HOSTILE:
			err_message = "405 NPC_NOT_HOSTILE";
			break;
		case TCPErrorCode::NO_QUEST_AVAILABLE:
			err_message = "406 NO_QUEST_AVAILABLE";
			break;
		case TCPErrorCode::CONNECTION_FAILED:
			err_message = "900 CONNECTION_FAILED";
			break;
		case TCPErrorCode::SEND_FAILED:
			err_message = "901 SEND_FAILED";
			break;
		default:
			err_message = "Invalid error code";
	}

	if (add_description) {
		return ("ERR " + err_message + "\n" + getTCP_errorDescription(error_code));
	}

	return ("ERR " + err_message + "\n");
}


// (PUBLIC)
// * Return a string with an 'ok' at the start for successfully operation. *
std::string	getTCP_OK_operation(const std::string& msg) {
	return ("OK " + msg + "\n");
}


// * Get the description of an error *
std::string getTCP_errorDescription(TCPErrorCode error_code) {
	std::string err_desc;

	switch (error_code) {
		case TCPErrorCode::NAME_IN_USE:
			err_desc = "Requested username already taken";
			break;
		case TCPErrorCode::INVALID_USERNAME:
			err_desc = "Username lenght is 3-20 characters.";
			break;
		case TCPErrorCode::NO_EXIT:
			err_desc = "Invalid movement direction";
			break;
		case TCPErrorCode::NOT_IN_GROUP:
			err_desc = "Group operation requires group membership";
			break;
		case TCPErrorCode::ALREADY_IN_GROUP:
			err_desc = "Player already belongs to a group";
			break;
		case TCPErrorCode::ITEM_NOT_FOUND:
			err_desc = "Requested item not available in room";
			break;
		case TCPErrorCode::ITEM_NOT_IN_INVENTORY:
			err_desc = "Requested item not in player inventory";
			break;
		case TCPErrorCode::NPC_NOT_FOUND:
			err_desc = "Requested NPC not present in room";
			break;
		case TCPErrorCode::NPC_NOT_HOSTILE:
			err_desc = "NPC cannot be attacked (not an enemy)";
			break;
		case TCPErrorCode::NO_QUEST_AVAILABLE:
			err_desc = "NPC has no quests or quest already completed";
			break;
		case TCPErrorCode::CONNECTION_FAILED:
			err_desc = "Connection establishment failed";
			break;
		case TCPErrorCode::SEND_FAILED:
			err_desc = "Message transmission failed";
			break;
		default:
			err_desc = "Invalid error code. No description.";
	}

	return err_desc;
}