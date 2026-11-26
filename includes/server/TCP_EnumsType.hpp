/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_EnumsType.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 10:33:07 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/26 10:23:14 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// === SERVER ONLY ===
// CONNECTED: connected to the server.
// AUTHENTICATED: connected to the game (have username).
// CLOSING: asking to quit.
enum class SessionState {CONNECTED, LOGGING, AUTHENTICATED, CLOSING};
enum class SubSessionState {MOVING, IN_COMBAT, IN_SHOP};
enum class OperationState {SUCCESS, WAITING, DECONNEXION, ERROR, NETWORK_ERROR};

// === COMMANDHANDLER ===
enum class HandshakeCommand {
	CONNECT,
	QUIT,
	HELP
};

enum class GameCommand {
	LOOK,
	MOVE,
	QUIT,
	CHAT, //todo
	WHO,
	GROUP_CREATE, //todo
	GROUP_INVITE, //todo
	GROUP_JOIN, //todo
	GROUP_LEAVE, //todo
	TAKE,
	DROP,
	INVENTORY,
	TALK,
	ATTACK,
	STATUS,
	QUEST,
	QUESTS,
	EQUIP,
	ITEM_INFO,
	HELP,
};

enum class CombatCommand {
	ATTACK,
	ACT,
	ITEM,
	SPARE,
	FLEE,
	STATUS,
	HELP,
};

enum class ShopCommand {
	ITEMS,
	ITEM_INFO,
	INVENTORY,
	BUY,
	QUIT,
	HELP
};

enum class UsernameLoggingCommand {
	DELETE,
	KEEP,
	CHANGE,
	QUIT,
	HELP
};
