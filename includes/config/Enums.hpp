/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enums.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:30:28 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/02 10:53:30 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// MOVEMENT
enum class	Direction {NORTH, SOUTH, EAST, WEST, UNKNOWN}; 	// for exits
// TYPE
enum class	ItemType {WEAPON, KEY, CONSUMABLE, UNKNOWN};	// for item type
enum class	EnemyType {ENEMY, BOSS, NPC, SHOP, UNKNOWN};	// for enemy type

// QUESTS
enum class	QuestStage {HAVE, COMPLETED, UNKNOWN};			// for quest stage
enum class	QuestState {IN_PROGRESS, COMPLETED, NOT_FOUND};	// for quest state

// DIALOGUES
enum class	ValidDialogueKey {
	TALK_, NO_MONEY, BUY, REMOTE, QUIT, SHOP_,
	ENCOUNTER, CHECK_DEFAULT, NEUTRAL_, ACT_, ACT_RESULT_FAILED, ACT_RESULT_WON, CHECK_, LOW_HP, SPARE, KILLED, CAN_SPARE,
	ACT_COLDIFY_, ACT_WARMIFY_, ACT_CHECK_OUFIT_HALF_WARM, ACT_CHECK_OUFIT_HALF_COLD, ACT_CHECK_OUFIT_NOTHING, ACT_CHECK_OUFIT_GREEN,
	ACT_CHECK_OUFIT_ORANGE, ACT_CHECK_OUFIT_YELLOW, ACT_CHECK_OUFIT_RED,
	ACT_PET_, ACT_PLAY_, ACT_IGNORE, ACT_BOW, ACT_BOW_RESULT, CHECK_BOW_, UNKNOWN};	// for dialogues key


// ERRORS (GasterManager)
enum class ReturnState {
	VALID,
	PLAYER_NOT_FOUND, ENTITY_NOT_FOUND, ROOM_NOT_FOUND, ITEM_NOT_FOUND, QUEST_NOT_FOUND,
	ENTITY_NOT_IN_PLAYER_ROOM, ENTITY_NOT_ENEMY,
	ITEM_NOT_IN_PLAYER_ROOM, ITEM_NOT_IN_PLAYER_INVENTORY,
};
