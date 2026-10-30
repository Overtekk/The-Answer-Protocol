/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enums.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:30:28 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/30 13:19:22 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

enum class	Direction {NORTH, SOUTH, EAST, WEST, UNKNOWN}; 	// for exits
enum class	ItemType {WEAPON, KEY, CONSUMABLE, UNKNOWN};	// for item type
enum class	EnemyType {ENEMY, BOSS, NPC, SHOP, UNKNOWN};	// for enemy type

enum class	QuestStage {HAVE, COMPLETED, UNKNOWN};			// for quest stage
enum class	QuestState {IN_PROGRESS, COMPLETED, NOT_FOUND};	// for quest state

enum class	ValidDialogueKey {
	TALK_, NO_MONEY, BUY, REMOTE, QUIT, SHOP_,
	ENCOUNTER, CHECK_DEFAULT, NEUTRAL_, ACT_, ACT_RESULT_FAILED, ACT_RESULT_WON, CHECK_, LOW_HP, SPARE, KILLED, CAN_SPARE,
	ACT_COLDIFY_, ACT_WARMIFY_, ACT_CHECK_OUFIT_HALF_WARM, ACT_CHECK_OUFIT_HALF_COLD, ACT_CHECK_OUFIT_NOTHING, ACT_CHECK_OUFIT_GREEN,
	ACT_CHECK_OUFIT_ORANGE, ACT_CHECK_OUFIT_YELLOW, ACT_CHECK_OUFIT_RED,
	ACT_PET_, ACT_PLAY_, ACT_IGNORE, ACT_BOW, ACT_BOW_RESULT, CHECK_BOW_, UNKNOWN};	// for dialogues key
