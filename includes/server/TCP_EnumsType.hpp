/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_EnumsType.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 10:33:07 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/03 10:37:43 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// === SERVER ONLY ===
// CONNECTED: connected to the server.
// AUTHENTICATED: connected to the game (have username).
// CLOSING: asking to quit.
enum class SessionState {CONNECTED, AUTHENTICATED, CLOSING};
enum class SubSessionState {MOVING, IN_BATTLE};
enum class OperationState {SUCCESS, WAITING, DECONNEXION, ERROR, NETWORK_ERROR};

// === COMMANDHANDLER ===
enum class HandshakeCommand {
	CONNECT,
	QUIT,
	HELP //todo
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
	TALK, //todo
	ATTACK,
	STATUS,
	QUEST,
	QUESTS,
	QUEST_INFO,
	EQUIP,
	INFO_ITEM,
	HELP, //todo
};

enum class BattleCommand {
	ATTACK,
	ACT, //todo
	ITEM, //todo
	SPARE, //todo
	RUNAWAY, //todo
	CHECK, //todo
	STATUS,
	HELP, //todo
};
