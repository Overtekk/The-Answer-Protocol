/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_event.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 10:22:19 by npillet           #+#    #+#             */
/*   Updated: 2026/11/25 14:25:05 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "server/manager/GasterManager.hpp"
#include "server/TCPSession.hpp"


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

		void	TCP_room_event(TCPSession& session, const std::string& zone_name, bool leave);
		void	TCP_global_event(TCPSession& session);
		void	TCP_group_event(TCPSession& session, std::string& group_name);
		void	TCP_stats_event(TCPSession& session);
};
