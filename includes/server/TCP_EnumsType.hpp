/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_EnumsType.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 10:33:07 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 14:03:44 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// === SERVER ONLY ===
// CONNECTED: connected to the server.
// AUTHENTICATED: connected to the game (have username).
// CLOSING: asking to quit.
enum class SessionState {CONNECTED, AUTHENTICATED, CLOSING};
enum class OperationState {SUCCESS, WAITING, DECONNEXION, ERROR, NETWORK_ERROR};

// === COMMANDHANDLER ===
enum class HandshakeCommand { CONNECT, QUIT };

enum class GameCommand {
	LOOK,
	MOVE,
	QUIT,
	CHAT,
	WHO,
	GROUP_CREATE,
	GROUP_INVITE,
	GROUP_JOIN,
	GROUP_LEAVE,
	TAKE,
	DROP,
	INVENTORY,
	TALK,
	ATTACK,
	STATUS,
	QUEST,
	QUESTS,
};
