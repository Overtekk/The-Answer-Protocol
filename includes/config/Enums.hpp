/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enums.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:30:28 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/07 15:18:56 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

enum class Direction {NORTH, SOUTH, EAST, WEST, UNKNOWN}; 	// for exits
enum class ItemType {WEAPON, KEY, CONSUMABLE, UNKNOWN};		// for item type
enum class EnemyType {ENEMY, BOSS, NPC, SHOP, UNKNOWN};		// for enemy type

// === SERVER ONLY ===
enum class SessionState {CONNECTED, AUTHENTICATED};
enum class OperationState {SUCCESS, WAITING, DECONNEXION, ERROR, NETWORK_ERROR};
