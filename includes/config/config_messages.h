/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_messages.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 11:51:32 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/24 09:32:16 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>

# include "config/config.hpp"

// ==============
// ==== NAME ====
// ==============
# define NAME_SERVER				"[Server] "
# define NAME_GASTER_MANAGER		"[GasterManager]: "
# define NAME_SHOP_MANAGER			"[ShopManager]: "

// ==============
// == ACTIONS ===
// ==============
# define ACT_SUCCESS_FLEE		"You take your shoes and flee with success!"
# define ACT_FAILED_FLEE		"You slipped on a rock. You didn't succeed!"
# define ACT_COMBAT_WON			"You won the combat."
# define ACT_COMBAT_LOSE		"You lose the combat."
# define ACT_SUCCESS_SPARE		"You spared the entity successfully!"
# define ACT_FAILED_SPARE		"The spared act have failed. Entity can't be spared."

# define ADMIN_KILL_CMD			"You have been killed by a god of an other world."

// ==============
// === SERVER ===
// ==============
# define QUIT_CMD					"QUIT"
# define CONNEXION_CLOSED			"Connection closed\n"
# define CONNEXION_CLOSED_CLIENT	"connection closed by client (ctrl+c)."
# define SERVER_BYE					"bye"
# define DISCONNEXION_MSG			"left the game."
# define CONNEXION_FAREWELL			"OK " SERVER_BYE
# define SERVER_LISTENING_MSG		"[Server]: OK hello proto=1\n"
# define SERVER_OK_CONNECTED		"CONNECTED"
# define LOG_QUIT_REQUEST			"requested graceful disconnect (QUIT)."
# define SERVER_LISTENING_PORT		"Server listening on port "
# define CONNEXION_DROPPED			"connection dropped (poll error/hangup)."
# define ERR_DISCONNECTED_MSG		"User have been disconnected due to an error."
# define SERVER_ASK_USERNAME		"Use \"connect [USERNAME]\" to launch the game"

inline std::string	userAlreadyExist(const std::string& player_name) {
	return (
		"\"" + player_name + "\" already exist. You can delete it with the \"delete\" command or keep the current progression with the \"keep\". "
		"You can change the username with the command \"change [NEW_USERNAME]\".");
}

// ==============
// ==== MAIN ====
// ==============
# define LOAD_FILE_FAILED	"Failed to load file.\n"
# define INVALID_DATA		"\n❌ Server aborting: invalid world data configuration.\n"

// ===============
// === SUCCESS ===
// ===============
# define SUCCESS_DATA_LOADED		"World Data loaded!"
# define SUCCESS_DATA_GUI_LOADED	"World Data (gui) loaded!"

inline std::string	SuccessPlayerSpawned(const std::string& player_name, const std::string& zone_name) { return NAME_GASTER_MANAGER "player '" + player_name + "' spawned in " + zone_name + "."; }
inline std::string	SuccessAddDefaultQuest(const std::string& player_name, const std::string& quests_list) { return NAME_GASTER_MANAGER "added default quest \"" + quests_list + "\" for " + player_name + "."; }
inline std::string	SuccessAddDefaultWeapon(const std::string& player_name, const std::string& item_name) { return NAME_GASTER_MANAGER "add starting weapon \"" + item_name + "\" for " + player_name + "."; }
inline std::string	SuccessPlayerMoved(const std::string& player_name, const std::string& old_zone, const std::string& new_zone) { return NAME_GASTER_MANAGER "moved player '" + player_name + "' from '" + old_zone + "' to '" + new_zone + "'."; }
inline std::string	SuccessCombatStarted(const std::string& player_name, const std::string& entity_id) { return NAME_GASTER_MANAGER "combat have started between " + player_name + " and " + entity_id; }
inline std::string	SuccessPlayerRespawned(const std::string& player_name) { return NAME_GASTER_MANAGER "player \"" + player_name + "\" have respawned to spawn."; }
inline std::string	SuccessEntityDeleted(const std::string& entity_id) { return NAME_GASTER_MANAGER "entity \"" + entity_id + "\" have been deleted."; }
inline std::string	SuccessPlayerFled(const std::string& player_name) { return NAME_GASTER_MANAGER "player \"" + player_name + "\" have flee the combat."; }
inline std::string	SuccessPlayerKilledByAdmin(const std::string& player_name) { return NAME_GASTER_MANAGER "player \"" + player_name + "\" has been killed by the admin."; }
inline std::string	SuccessAdminKill(const std::string& player_name) { return "player \"" + player_name + "\" has been killed with success."; }
inline std::string	SuccessNewPlayerCreated(const std::string& player_name) { return "new player created: \"" + player_name + "\""; }
inline std::string	SuccessPlayerEnteredShop(const std::string& player_name, const std::string& entity_name) { return "player \"" + player_name + "\" have entered in the shop of " + entity_name; }
inline std::string	SuccessPlayerBuy(const std::string& item_id) { return "have buy \"" + item_id + "\"";}
inline std::string	SuccessPlayerLeavedShop(const std::string& player_name) { return "player \"" + player_name + "\" have leaved the shop"; }

inline std::string	addItemInInventory(const std::string item_id) { return item_id + "added in inventory."; }


// ==============
// ==== LOGS ====
// ==============
// === (commands / connections) ===
inline std::string	logCommandEntered(const std::string& command) { return "entered command: " + command; }
inline std::string	logCommandRejected(const std::string& command) { return "rejected command: '" + command + "'"; }
inline std::string	logClientConnected(int socket_fd) { return "connected to server (socket " + std::to_string(socket_fd) + ")."; }
inline std::string	logServerCommand(const std::string& command) { return "Server used " + command; }

// === MANAGER ===
inline std::string	logDisconnectPlayer(const std::string& player_name) { return player_name + " have been disconnecting and saved."; }
inline std::string	logErasePlayer(const std::string& player_name) { return player_name + " has been erased from the server."; }
inline std::string	logReconnectPlayer(const std::string& player_name) { return player_name + " have reconneted."; }

// === OK REPLIES (sent to the clients) ===
# define okHelpHandshakeCommand	"Available commands: \"CONNECT {username}\" | \"HELP {command}\" | \"QUIT\""
# define okHelpGameCommand		"Available commands: \"LOOK\" | \"MOVE {direction}\" | \"WHO\" | \"TAKE {id}\" | \"DROP {id}\" | \"INVENTORY\" | "\
								"\"TALK {id}\" | \"ATTACK {id}\" | \"STATUS\" | \"QUEST {id}\" | \"QUESTS\" | \"EQUIP {id}\" | \"ITEM_INFO {id}\" | "\
								"\"CHAT {message}\" | \"GROUP_CREATE {name}\" | \"GROUP_INVITE {username}\" | \"GROUP_JOIN\" | \"GROUP_LEAVE\" | \"HELP {command}\" | \"QUIT\""
# define okHelpCombatCommand	"Available commands: \"ATTACK\" | \"ACT {action}\" | \"ITEM {id}\" | \"SPARE\" | \"FLEE\" | \"CHECK\" | \"STATUS\" | \"HELP {command}\""
# define okHelpShopCommmand		"Available commands: \"ITEMS\" | \"BUY {item}\" | \"ITEM_INFO {id}\" | \"INVENTORY\" | \"QUIT\" | \"HELP {command}\""
# define okHelpLoggingCommand	"Available commands: \"KEEP\" | \"DELETE\" | \"change {username}\" | \"HELP {command}\" | \"QUIT\""

# define helpConnectCommand		"CONNECT: Connect you to the game with the provided username."
# define helpHelpCommand		"HELP: give information about a command."
# define helpQuitCommand		"QUIT: leave the game."

# define helpLookCommand		"LOOK: give informations about the current room (name, rooms connexion, players, items, entities...)"
# define helpMoveCommand		"MOVE: move to the next room using \"NORTH\", \"EAST\", \"WEST\", \"SOUTH\" if possible."
# define helpWhoCommand			"WHO: show the list of players connected."
# define helpTakeCommand		"TAKE: take the requested item from the room to your inventory."
# define helpDropCommand		"DROP: drop an item from your inventory into the current room."
# define helpInventoryCommand	"INVENTORY: show your current inventory and equipped weapon."
# define helpTalkCommand		"TALK: talk to the requested NPC in the current room."
# define helpAttackCommand		"ATTACK: attack the request NPC if it's an enemy and launch a combat."
# define helpStatusCommand		"STATUS: show your stats (HP, armor, luck...)"
# define helpQuestCommand		"QUEST: show information about the requested quest."
# define helpQuestsCommand		"QUESTS: show your current quests."
# define helpEquipCommand		"EQUIP: equip the requested item if it's a weapon."
# define helpInfoItemCommand	"INFO_ITEM: give information about the requested item."
# define helpChatCommand		"CHAT: send a message to the other players."
# define helpGroupCreateCommand	"GROUP_CREATE: create a group with the provided name."
# define helpGroupInviteCommand	"GROUP_INVITE: invite the requested player to your group."
# define helpGroupJoinCommand	"GROUP_JOIN: join the group based of your last invitation."
# define helpGroupLeaveCommand	"GROUP_LEAVE: leave your current group."

# define helpCombatAttackCommand	"ATTACK: attack the current enemy with your weapon."
# define helpCombatActCommand		"ACT: show the list of action OR act with the requested action."
# define helpCombatItemCommand		"ITEM: show the list of your items OR use the requested item."
# define helpCombatSpareCommand		"SPARE: spare an enemy if possible."
# define helpCombatFleeCommand		"FLEE: try to flee based on your luck, your hp and the enemy HP."
# define helpCombatCheckCommand		"CHECK: check the enemy information"

# define helpShopItemsCommand	"ITEMS: show the list of available items to buy and their price."
# define helpShopBuyCommand		"BUY: buy the requested item if you have the funds."
# define helpShopQuitCommand	"QUIT: leave the shop."

# define helpKeepCommand		"KEEP: keep the current username and progression saved."
# define helpDeleteCommand		"DELETE: delete the progression of the current username and start fresh."
# define helpChangeCommand		"CHANGE: change the requested username and connect with it."

inline std::string	okTaken(const std::string& item) { return "taken=" + item; }
inline std::string	okDropped(const std::string& item) { return "dropped=" + item; }
inline std::string	okRoom(const std::string& room) { return "room=" + room; }
inline std::string	okEquipped(const std::string& item) { return item + " is now equipped!"; }
inline std::string	okTalk(const std::string& entity_name, const std::string& text) { return entity_name + ": \"" + text + "\""; }

// === COMBAT MESSAGES (sent to the clients) ===
inline std::string	actPlayerAttack(const std::string& entity_name, int damage, int bonus) {
	std::string msg = "You attacked " + entity_name + " with a strength of " + std::to_string(damage);
	if (bonus > 0)
		msg += " (bonus +" + std::to_string(bonus) + ")";
	return msg + ".";
}
inline std::string	actEnemyNoDamage(const std::string& entity_name) { return entity_name + " dealt no damage to you."; }
inline std::string	actEnemyAttack(const std::string& entity_name, int damage) { return entity_name + " attacked you with a strength of " + std::to_string(damage); }
inline std::string	actPlayerBlocked(const std::string& entity_name) { return "You blocked " + entity_name + " damage."; }

// === SHOP MESSAGES (sent to the clients) ===
# define logLeaveShop	"You've leaved the shop."

inline std::string	logEnterShop(const std::string& entity_name) { return "You've entered - " + entity_name + "'s shop -"; }


// ==============
// === ERRORS ===
// ==============
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

inline std::string	errCantFindPlayer(const std::string& player_name) { return NAME_GASTER_MANAGER "can't find player \"" + player_name + "\""; }
inline std::string	errCantFindItem(const std::string& item_name) { return NAME_GASTER_MANAGER "can't find item \"" + item_name + "\""; }
inline std::string	errCantFindRoom(const std::string& room_name) { return NAME_GASTER_MANAGER "can't find room \"" + room_name + "\""; }
inline std::string	errCantFindEntity(const std::string& entity_id) { return NAME_GASTER_MANAGER "can't find entity \"" + entity_id + "\""; }
inline std::string	errItemNotWeapon(const std::string& item_name) { return NAME_GASTER_MANAGER "item \"" + item_name + "\" is not a weapon. Can't equip."; }
inline std::string	errCombatNotStarted(const std::string& player_name) { return NAME_GASTER_MANAGER "can't init combat for " + player_name + ". He have not started a combat yet."; }
inline std::string	errCantAttackNoCombat(const std::string& player_name) { return NAME_GASTER_MANAGER + player_name + " can't attack. He have not started a combat yet."; }
inline std::string	errCantCheckNoCombat(const std::string& player_name) { return NAME_GASTER_MANAGER + player_name + " have not started a combat yet. Can't check status of his combat."; }
inline std::string	errCantGetPlayerRoom(const std::string& player_name) { return NAME_GASTER_MANAGER "can't get the room of \"" + player_name + "\"."; }
inline std::string	errEntityNotInRoom(const std::string& entity_name) { return NAME_GASTER_MANAGER "\"" + entity_name + "\" not in player room."; }
inline std::string	errEntityNotEnemy(const std::string& entity_name) { return NAME_GASTER_MANAGER "\"" + entity_name + "\" not an enemy."; }
inline std::string	errEntityAlreadyInCombat(const std::string& entity_name) { return NAME_GASTER_MANAGER "\"" + entity_name + "\" is already in a combat. Combat launch aborted."; }
inline std::string	errEntityNotShop(const std::string& entity_name) { return NAME_GASTER_MANAGER "\"" + entity_name + "\" not a shop."; }
inline std::string	errItemNotInRoom(const std::string& item_name) { return NAME_GASTER_MANAGER "item \"" + item_name + "\" not in room."; }
inline std::string	errItemNotInInventory(const std::string& item_name) { return NAME_GASTER_MANAGER "item \"" + item_name + "\" not in player inventory."; }
inline std::string	errCantKillPlayer(const std::string& player_name) { return "can't kill '" + player_name + "': player not found."; }

// === ERRORS - TCP LOGS (same info as the TCP_responses.cpp errors) ===
# define ERR_LOG_MISSING_USERNAME	"error: 203 MISSING_USERNAME"
# define ERR_LOG_INVALID_USERNAME	"error: 202 INVALID_USERNAME"
# define ERR_LOG_NAME_IN_USE		"error: 201 NAME_IN_USE"
# define ERR_LOG_BAD_DIRECTION		"error: 301 Invalid movement direction (bad input)."
# define ERR_LOG_NPC_NOT_FOUND		"error 404: Requested NPC not present in room."
# define ERR_LOG_NPC_NO_DIALOGUE	"error 407: Requested NPC have no available dialogue."
# define ERR_LOG_MISSING_NPC		"error 204: Missing argument (NPC) after command."

// === ERRORS - CLIENT CONNECTION ===
# define ERR_CONNECTION_FAILED		"Connection have failed. Try to reconnect using the \"connect\" command."

inline std::string	errIncorrectPort() { return "Incorrect port. Use: " + std::to_string(SERVER_PORT); }
inline std::string	errInvalidIp(const std::string& ip) { return "Invalid IP address: " + ip; }
inline std::string	errConnectionFailed(const std::string& ip, int port) { return "Connection to server failed (" + ip + ":" + std::to_string(port) + ")."; }

// === ERRORS - MANAGERS ===
// -- GasterManager --
inline std::string	errDialogueNotFound(const std::string& entity_id, const std::string& key) { return "DialogueManager: can't find dialogue \"" + key + "\" for entity \"" + entity_id + "\"."; }
inline std::string	errQuestNotExist(const std::string& quest_id) { return "\"" + quest_id + "\" doesn't exist."; }

// --- ShopManager --
inline std::string	errShopItemRemove(const std::string& entity_id, const std::string& item_id) { return "Can't delete \"" + item_id + "\" from \"" + entity_id + "\"."; }

// === ERRORS - PARSER (server) ===
# define STAGE_REASON_NOT_MAP			"not a map"
# define STAGE_REASON_BAD_CONDITION		"invalid condition (valid are \"completed\" or \"have\")."

inline std::string	errNotEnoughQuests(size_t found) { return "You need to have a least 3 quests. Only " + std::to_string(found) + " found."; }
inline std::string	errInvalidStageQuest(const std::string& entity_id, const std::string& quest_id) { return "Invalid quest id for dialogue stage of entity \"" + entity_id + "\" (" + quest_id + ")."; }
inline std::string	errItemMissingType(const std::string& id) { return id + " missing type for this item. Use: WEAPON, KEY or CONSUMABLE."; }
inline std::string	errEntityMissingType(const std::string& id) { return id + " missing type for this entity. Use: ENEMY, BOSS, NPC or SHOP."; }
inline std::string	errNameEmpty(const std::string& id) { return id + " name can't be empty."; }
inline std::string	errDescEmpty(const std::string& id) { return id + " description can't be empty."; }
inline std::string	errNotPositive(const std::string& id) { return id + " invalid integer. Need to be positive."; }
inline std::string	warnDialogueIgnored(const std::string& entity_id) { return "Dialogues will be ignored for \"" + entity_id + "\" because it as custom behavior."; }
inline std::string	warnDialogueNotScalar(const std::string& entity_id, const std::string& key) { return "Dialogue not scalar for \"" + entity_id + " \" and key:\"" + key + "\""; }
inline std::string	warningStockMapButNotShopType(const std::string& entity_id) { return "\"" + entity_id + "\" have a stock_shop but is not of type shop. It will not be registered."; }
inline std::string	errInvalidDialogueKey(const std::string& entity_id, const std::string& key) { return "invalid dialogue key \"" + key + "\" for entity \"" + entity_id + "\"."; }
inline std::string	errInvalidStage(const std::string& entity_id, const std::string& reason) { return "invalid dialogue stage for entity \"" + entity_id + "\" : invalid = " + reason; }
inline std::string	errInvalidItemStock(const std::string& entity_id, const std::string& item_id) { return "\"" + entity_id + "\" have an unkown item is in stock shop (\"" + item_id + "\")";}
inline std::string	stageReasonNotPositive(int last_stage) { return std::to_string(last_stage) + "."; }
inline std::string	stageReasonNotIncreasing(int last_stage, int previous) { return std::to_string(last_stage) + " must be greater than previous stage " + std::to_string(previous) + "."; }
inline std::string	stageReasonMissingKey(int last_stage) { return "missing dialogue key: " + std::to_string(last_stage); }

// === ERRORS - PARSER (gui) ===
inline std::string	errMissingResource(const std::string& id, const std::string& kind) { return "'" + id + "' missing " + kind + "."; }
inline std::string	errBadResourceExt(const std::string& id, const std::string& kind, const std::string& allowed) { return "'" + id + "' " + kind + " must be in " + allowed + "."; }
inline std::string	errCantFindPlayerZone(const std::string& player_name) { return NAME_GASTER_MANAGER "can't find the zone of player '" + player_name + "'."; }
inline std::string	errBadMovement(const std::string& player_zone, const std::string& direction) { return NAME_GASTER_MANAGER "bad direction '" + direction + "' for zone '" + player_zone + "'.";}

// === ERRORS - OTHER ===
inline std::string	errRandomGenerationBounds(int min, int max) { return "RandomGeneration: error " + std::to_string(min) + " superior to " + std::to_string(max); }
