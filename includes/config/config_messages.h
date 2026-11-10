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
#include "config/config.hpp"

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
# define SERVER_LISTENING_MSG		"[Server]: OK hello proto=1\n"
# define SERVER_OK_CONNECTED		"CONNECTED"
# define LOG_QUIT_REQUEST			"requested graceful disconnect (QUIT)."
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
inline std::string	SuccessCombatStarted(const std::string& player_name, const std::string& entity_id) {
	return NAME_GASTER_MANAGER "combat have started between " + player_name + " and " + entity_id;
}
inline std::string	SuccessPlayerRespawned(const std::string& player_name) {
	return NAME_GASTER_MANAGER "player \"" + player_name + "\" have respawned to spawn.";
}
inline std::string	SuccessEntityDeleted(const std::string& entity_id) {
	return NAME_GASTER_MANAGER "entity \"" + entity_id + "\" have been deleted.";
}
inline std::string	SuccessPlayerFled(const std::string& player_name) {
	return NAME_GASTER_MANAGER "player \"" + player_name + "\" have flee the combat.";
}
inline std::string	SuccessPlayerKilledByAdmin(const std::string& player_name) {
	return NAME_GASTER_MANAGER "player \"" + player_name + "\" has been killed by the admin.";
}
inline std::string	SuccessAdminKill(const std::string& player_name) {
	return "player '" + player_name + "' has been killed with success.";
}
inline std::string	SuccessNewPlayerCreated(const std::string& player_name) {
	return "new player created: '" + player_name + "'";
}

// LOGS (commands / connections)
inline std::string	logCommandEntered(const std::string& command) { return "entered command: " + command; }
inline std::string	logCommandRejected(const std::string& command) { return "rejected command: '" + command + "'"; }
inline std::string	logClientConnected(int socket_fd) { return "connected to server (socket " + std::to_string(socket_fd) + ")."; }
inline std::string	logServerCommand(const std::string& command) { return "Server used " + command; }

// OK REPLIES (sent to the clients)
inline std::string	okTaken(const std::string& item) { return "taken=" + item; }
inline std::string	okDropped(const std::string& item) { return "dropped=" + item; }
inline std::string	okRoom(const std::string& room) { return "room=" + room; }
inline std::string	okEquipped(const std::string& item) { return item + " is now equipped!"; }
inline std::string	okTalk(const std::string& entity_name, const std::string& text) { return entity_name + ": \"" + text + "\""; }

// COMBAT MESSAGES (sent to the clients)
inline std::string	actPlayerAttack(const std::string& entity_name, int damage, int bonus) {
	std::string msg = "You attacked " + entity_name + " with a strength of " + std::to_string(damage);
	if (bonus > 0)
		msg += " (bonus +" + std::to_string(bonus) + ")";
	return msg + ".";
}
inline std::string	actEnemyNoDamage(const std::string& entity_name) { return entity_name + " dealt no damage to you."; }
inline std::string	actEnemyAttack(const std::string& entity_name, int damage) {
	return entity_name + " attacked you with a strength of " + std::to_string(damage);
}
inline std::string	actPlayerBlocked(const std::string& entity_name) { return "You blocked " + entity_name + " damage."; }

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
	return NAME_GASTER_MANAGER "can't find entity \"" + entity_id + "\"";
}
inline std::string	errItemNotWeapon(const std::string& item_name) {
	return NAME_GASTER_MANAGER "item \"" + item_name + "\" is not a weapon. Can't equip.";
}
inline std::string	errCombatNotStarted(const std::string& player_name) {
	return NAME_GASTER_MANAGER "can't init combat for " + player_name + ". He have not started a combat yet.";
}
inline std::string	errCantAttackNoCombat(const std::string& player_name) {
	return NAME_GASTER_MANAGER + player_name + " can't attack. He have not started a combat yet.";
}
inline std::string	errCantCheckNoCombat(const std::string& player_name) {
	return NAME_GASTER_MANAGER + player_name + " have not started a combat yet. Can't check status of his combat.";
}
inline std::string	errCantGetPlayerRoom(const std::string& player_name) {
	return NAME_GASTER_MANAGER "can't get the room of \"" + player_name + "\".";
}
inline std::string	errEntityNotInRoom(const std::string& entity_name) {
	return NAME_GASTER_MANAGER "\"" + entity_name + "\" not in player room.";
}
inline std::string	errEntityNotEnemy(const std::string& entity_name) {
	return NAME_GASTER_MANAGER "\"" + entity_name + "\" not an enemy.";
}
inline std::string	errItemNotInRoom(const std::string& item_name) {
	return NAME_GASTER_MANAGER "item \"" + item_name + "\" not in room.";
}
inline std::string	errItemNotInInventory(const std::string& item_name) {
	return NAME_GASTER_MANAGER "item \"" + item_name + "\" not in player inventory.";
}
inline std::string	errCantKillPlayer(const std::string& player_name) {
	return "can't kill '" + player_name + "': player not found.";
}

// ERRORS - TCP LOGS (same info as the TCP_responses.cpp errors)
# define ERR_LOG_MISSING_USERNAME	"error: 203 MISSING_USERNAME"
# define ERR_LOG_INVALID_USERNAME	"error: 202 INVALID_USERNAME"
# define ERR_LOG_NAME_IN_USE		"error: 201 NAME_IN_USE"
# define ERR_LOG_BAD_DIRECTION		"error: 301 Invalid movement direction (bad input)."
# define ERR_LOG_NPC_NOT_FOUND		"error 404: Requested NPC not present in room."
# define ERR_LOG_NPC_NO_DIALOGUE	"error 407: Requested NPC have no available dialogue."
# define ERR_LOG_MISSING_NPC		"error 204: Missing argument (NPC) after command."

// ERRORS - CLIENT CONNECTION
inline std::string	errIncorrectPort() { return "Incorrect port. Use: " + std::to_string(SERVER_PORT); }
inline std::string	errInvalidIp(const std::string& ip) { return "Invalid IP address: " + ip; }
inline std::string	errConnectionFailed(const std::string& ip, int port) {
	return "Connection to server failed (" + ip + ":" + std::to_string(port) + ").";
}

// ERRORS - MANAGERS
inline std::string	errDialogueNotFound(const std::string& entity_id, const std::string& key) {
	return "DialogueManager: can't find dialogue \"" + key + "\" for entity \"" + entity_id + "\".";
}
inline std::string	errQuestNotExist(const std::string& quest_id) { return "\"" + quest_id + "\" doesn't exist."; }

// ERRORS - PARSER (server)
inline std::string	errNotEnoughQuests(size_t found) {
	return "You need to have a least 3 quests. Only " + std::to_string(found) + " found.";
}
inline std::string	errInvalidStageQuest(const std::string& entity_id, const std::string& quest_id) {
	return "Invalid quest id for dialogue stage of entity \"" + entity_id + "\" (" + quest_id + ").";
}
inline std::string	errItemMissingType(const std::string& id) { return id + " missing type for this item. Use: WEAPON, KEY or CONSUMABLE."; }
inline std::string	errEntityMissingType(const std::string& id) { return id + " missing type for this entity. Use: ENEMY, BOSS, NPC or SHOP."; }
inline std::string	errNameEmpty(const std::string& id) { return id + " name can't be empty."; }
inline std::string	errDescEmpty(const std::string& id) { return id + " description can't be empty."; }
inline std::string	errNotPositive(const std::string& id) { return id + " invalid integer. Need to be positive."; }
inline std::string	warnDialogueIgnored(const std::string& entity_id) {
	return "Dialogues will be ignored for \"" + entity_id + "\" because it as custom behavior.";
}
inline std::string	warnDialogueNotScalar(const std::string& entity_id, const std::string& key) {
	return "Dialogue not scalar for \"" + entity_id + " \" and key:\"" + key + "\"";
}
inline std::string	errInvalidDialogueKey(const std::string& entity_id, const std::string& key) {
	return "invalid dialogue key \"" + key + "\" for entity \"" + entity_id + "\".";
}
inline std::string	errInvalidStage(const std::string& entity_id, const std::string& reason) {
	return "invalid dialogue stage for entity \"" + entity_id + "\" : invalid = " + reason;
}
# define STAGE_REASON_NOT_MAP			"not a map"
# define STAGE_REASON_BAD_CONDITION		"invalid condition (valid are \"completed\" or \"have\")."
inline std::string	stageReasonNotPositive(int last_stage) { return std::to_string(last_stage) + "."; }
inline std::string	stageReasonNotIncreasing(int last_stage, int previous) {
	return std::to_string(last_stage) + " must be greater than previous stage " + std::to_string(previous) + ".";
}
inline std::string	stageReasonMissingKey(int last_stage) { return "missing dialogue key: " + std::to_string(last_stage); }

// ERRORS - PARSER (gui)
inline std::string	errMissingResource(const std::string& id, const std::string& kind) {
	return "'" + id + "' missing " + kind + ".";
}
inline std::string	errBadResourceExt(const std::string& id, const std::string& kind, const std::string& allowed) {
	return "'" + id + "' " + kind + " must be in " + allowed + ".";
}
inline std::string	errCantFindPlayerZone(const std::string& player_name) {
	return NAME_GASTER_MANAGER "can't find the zone of player '" + player_name + "'.";
}
inline std::string	errBadMovement(const std::string& player_zone, const std::string& direction) {
	return NAME_GASTER_MANAGER "bad direction '" + direction + "' for zone '" + player_zone + "'.";
}
