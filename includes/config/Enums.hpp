/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enums.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:30:28 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/21 14:07:25 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

enum class	Direction {NORTH, SOUTH, EAST, WEST, UNKNOWN}; 	// for exits
enum class	ItemType {WEAPON, KEY, CONSUMABLE, UNKNOWN};	// for item type
enum class	EnemyType {ENEMY, BOSS, NPC, SHOP, UNKNOWN};	// for enemy type

enum class	QuestState {IN_PROGRESS, COMPLETED, NOT_FOUND};	// for quest state
