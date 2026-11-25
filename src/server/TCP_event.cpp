/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_event.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 09:26:13 by npillet           #+#    #+#             */
/*   Updated: 2026/11/25 15:58:13 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/TCP_event.hpp"
#include "server/TCPSession.hpp"
#include "server/manager/GasterManager.hpp"
#include "config/config_messages.h"
#include <cstddef>


// ============================================================================
// =========================       METHODS      ===============================
// ============================================================================
// --- CONSTRUCTOR ---
TCPEvent::TCPEvent(GasterManager& manager): _manager(manager) {}

// ============================================================================
// =========================       PUBLIC      ================================
// ============================================================================
// * Handles Room Events. *
void TCPEvent::TCP_room_event(TCPSession& session, const std::string& zone_name, bool leave) {
	std::vector<std::string>	player_list = select_players();
	std::string					event;

	if (leave == true)
		event = LeaveRoomEvent(session.getUsername(), zone_name);
	else
		event = EnterRoomEvent(session.getUsername(), zone_name);

	// Sends event to every players in the room
	for (auto& it : sessions) {
			TCPSession& session = *it.second;
			if (session.getUsername() != &session)
				other.add_msg_to_buffer(event)
	}
}

// * Handles Global Event. *
// void TCPEvent::TCP_global_event(TCPSession& session) { // todo
// 	;
// }

// * Handle Group Events. *
void TCPEvent::TCP_group_event(TCPSession& session, std::string& group_name) { // todo
	// Player receives an invite
	session.add_msg_to_buffer(GroupInviteEvent(session.getUsername(), group_name));

	// Player joins a group
	session.add_msg_to_buffer(GroupJoinEvent(session.getUsername(), group_name));

	// Player leaves a group
	session.add_msg_to_buffer(GroupLeaveEvent(session.getUsername(), group_name));
}

// * Handles Stats Event. *
// void TCPEvent::TCP_stats_event(TCPSession& session) { // todo
// 	;
// }

// ============================================================================
// =========================       PRIVATE      ===============================
// ============================================================================
// * Makes a list of players included for the event message. *
std::vector<std::string> TCPEvent::select_players() {
	std::string					raw_list = _manager.getListOfPlayers();
	std::vector<std::string>	player_list;
	std::string					delim = ", ";
	size_t						start = 0;
	size_t						pos;

	std::string	token = raw_list.substr(raw_list.find("[") + 1, raw_list.find("]") - raw_list.find("[") - 1);

	while ((pos = token.find(delim, start)) != std::string::npos) {
		player_list.push_back(token.substr(start, pos - start));
		start = pos + delim.length();
	}
	player_list.push_back(token.substr(start));

	return player_list;
}
