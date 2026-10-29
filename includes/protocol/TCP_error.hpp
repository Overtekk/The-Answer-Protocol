/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_error.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 14:52:14 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/29 10:34:20 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>


enum class TCPErrorCode {
	NAME_IN_USE,				// USERNAME ALREADY USED
	NO_EXIT,					// NO EXIT IN THIS DIRECTION
	NOT_IN_GROUP,				// CLIENT NOT IN A GROUP
	ALREADY_IN_GROUP,			// CLIENT ALREADY IN A GROUP
	ITEM_NOT_FOUND,				// ITEM NOT FOUND
	ITEM_NOT_IN_INVENTORY,		// ITEM NOT IN INVENTORY
	NPC_NOT_FOUND,				// NPC NOT FOUND
	NPC_NOT_HOSTILE,			// THIS NPC IS NOT HOSTILE (= not attackable)
	NO_QUEST_AVAILABLE,			// NO QUEST AVAILABLE
	CONNECTION_FAILED,			// ERROR WHEN CONNECTING
	SEND_FAILED,				// ERROR WHEN SENDING MESSAGE
	INVALID_USERNAME,			// INVALID USERNAME (e.g: too short/too long)
	SYSTEM_ERROR,				// ERROR OF THE SERVER
	CONNEXION_ERROR,			// CONNEXION ERROR WITH THE SERVER
	COMMAND_NOT_FOUND,			// COMMAND DO NOT EXIST
	MISSING_USERNAME,			// PLAYER FORGOT TO ENTER USERNAME
	NPC_NO_DIALOGUE,			// NO DIALOGUES AVAILABLE FOR THIS NPC
};


std::string	getTCP_error(TCPErrorCode e);
std::string	getTCP_OK_operation(const std::string& msg);
