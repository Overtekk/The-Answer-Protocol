/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_event.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 10:22:19 by npillet           #+#    #+#             */
/*   Updated: 2026/11/26 14:49:32 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <vector>

# include "server/manager/GasterManager.hpp"
# include "server/TCPSession.hpp"


struct EventDetails {
	std::string	player_name;
	std::string	evt_type;
	std::string	evt_message;
};


class TCPEvent {
	private:
		GasterManager&				_manager;

		// Utils
		std::vector<std::string>	select_players();

	public:
		// --- CONSTRUCTOR ---
		explicit TCPEvent(GasterManager& manager);
		// --- DESTRUCTOR ---
		~TCPEvent() = default;

		std::vector<EventDetails>	updateEvents(std::unordered_map<int, std::unique_ptr<TCPSession>>& sessions);
		void						TCP_room_event(TCPSession& session, const std::string& zone_name, bool leave);
		void						TCP_global_event(TCPSession& session);
		void						TCP_group_event(TCPSession& session, std::string& group_name);
		void						TCP_stats_event(TCPSession& session);
};
