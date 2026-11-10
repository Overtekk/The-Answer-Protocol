/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_messages.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 11:51:32 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/10 15:38:57 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

// NAME
# define NAME_SERVER				"[Server] "
# define NAME_GASTER_MANAGER		"[GasterManager]: "

// ACTIONS
# define ACT_SUCCESS_FLEE		"You take your shoes and flee with success!"
# define ACT_FAILED_FLEE		"You slipped on a rock. You didn't succeed!"
# define ACT_COMBAT_WON			"You won the combat."
# define ACT_COMBAT_LOSE		"You lose the combat."

# define ADMIN_KILL_CMD			"You have been killed by a god of an other world."

// SERVER RELATED
# define QUIT_CMD					"QUIT"
# define CONNEXION_CLOSED			"Connection closed\n"
# define CONNEXION_CLOSED_CLIENT	"connection closed by client."
# define SERVER_BYE					"bye"
# define DISCONNEXION_MSG			"left the game."
# define CONNEXION_FAREWELL			"OK " SERVER_BYE
# define SERVER_LISTENING_MSG		NAME_SERVER " : OK hello proto=1\n"
# define SERVER_LISTENING_PORT		"Server listening on port "
# define CONNEXION_DROPPED			"connection dropped (poll error/hangup)."
# define ERR_DISCONNECTED_MSG		"User have been disconnected due to an error."

// MAIN
# define LOAD_FILE_FAILED	"Failed to load file.\n"
# define INVALID_DATA		"\n❌ Server aborting: invalid world data configuration.\n"

// SUCCESS
# define SUCCESS_DATA_LOADED		"World Data loaded!"
# define SUCCESS_DATA_GUI_LOADED	"World Data (gui) loaded!"

inline std::string	SuccessPlayerSpawned(const std::string& player_name, const std::string& zone_name) {
	return NAME_GASTER_MANAGER "player '" + player_name + "' spawned in " + zone_name + ".";
}
inline std::string	SuccessAddDefaultQuest(const std::string& player_name, const std::string& quests_list) {
	return NAME_GASTER_MANAGER "added default quest \"" + quests_list + "\" for " + player_name + ".";
}
inline std::string	SuccessAddDefaultWeapon(const std::string& player_name, const std::string& item_name) {
	return NAME_GASTER_MANAGER "add starting weapon \"" + item_name + "\" for " + player_name + ".";
}
inline std::string	SuccessPlayerMoved(const std::string& player_name, const std::string& old_zone, const std::string& new_zone) {
	return NAME_GASTER_MANAGER "moved player '" + player_name + "' from '" + old_zone + "' to '" + new_zone + "'.";
}

// ERRORS
# define ERR_EMPTY_FILE				"Empty file.\n"
# define ERR_NOT_ENOUGHT_LOCATIONS	"You need to have a least 8 different locations."
# define ERR_MISSING_LOCATIONS_KEY	"Missing locations. Did you forget? 😱"
# define ERR_MISSING_ITEMS_KEY		"Missing items. Did you forget? 😱"
# define ERR_MISSING_ENTITIES_KEY	"Missing entities. Did you forget? 😱"
# define ERR_MISSING_QUESTS_KEY		"Missing quests. Did you forget? 😱"
# define ERR_PARSING_FAILED			"PARSING FAILED!\n"
# define ERR_MISSING_SPAWN_KEY		"\"spawn\" is missing. Make sure a zone ID is named \"spawn\"."
# define ERR_FAILED_CREATE_SOCKET	"Failed to create client socket."
# define ERR_KILL_CMD				"usage: kill [player name]"

inline std::string	errObject(const std::string& error) { return " ERROR: " + error + "\n"; }

inline std::string	errCantFindPlayer(const std::string& player_name) {
	return NAME_GASTER_MANAGER "can't find player \"" + player_name + "\"";
}
inline std::string	errCantFindItem(const std::string& item_name) {
	return NAME_GASTER_MANAGER "can't find item \"" + item_name + "\"";
}
inline std::string	errCantFindRoom(const std::string& room_name) {
	return NAME_GASTER_MANAGER "can't find room \"" + room_name + "\"";
}
inline std::string	errCantFindEntity(const std::string& entity_id) {
	return NAME_GASTER_MANAGER "can't can't find entity \"" + entity_id + "\"";
}
inline std::string	errItemNotWeapon(const std::string& item_name) {
	return NAME_GASTER_MANAGER "can't item \"" + item_name + "\"is not a weapon. Can't equipp.";
}
inline std::string	errCombatNotStarted(const std::string& player_name) {
	return NAME_GASTER_MANAGER "can't can't init combat for " + player_name + ". He have not started a combat yet.";
}
inline std::string	errCantFindPlayerZone(const std::string& player_name) {
	return NAME_GASTER_MANAGER "can't find the zone of player '" + player_name + "'.";
}
inline std::string	errBadMovement(const std::string& player_zone, const std::string& direction) {
	return NAME_GASTER_MANAGER "bad direction '" + direction + "' for zone '" + player_zone + "'.";
}
