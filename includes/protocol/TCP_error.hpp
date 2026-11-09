/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_error.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 14:52:14 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/09 10:36:48 by roandrie         ###   ########.fr       */
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
	PLAYER_NOT_FOUND,			// ERROR WHEN FINDING THE PLAYER
	NPC_NOT_IN_ROOM,			// NPC IS NOT IN THE SAME ROOM AS THE CLIENT
	ROOM_NOT_FOUND,				// ROOM NOT FOUND
	QUEST_NOT_FOUND,			// QUEST NOT FOUND
	ITEM_NOT_IN_ROOM,			// ITEM NOT IN CLIENT ROOM
	MISSING_NPC,				// CLIENT FORGOT TO ADD ENTITY TO A COMMAND
	ITEM_NOT_WEAPON,			// ITEM IS NOT A WEAPON
	MISSING_ITEM,				// ITEM IS MISSING
	NOT_IN_BATTLE,				// CLIENT IS NOT IN A BATTLE
	NOT_YOUR_TURN				// NOT THE CLIENT TURN
};


std::string	getTCP_error(TCPErrorCode e);
std::string	getTCP_OK_operation(const std::string& msg);
