/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GasterManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:39:30 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/05 15:02:32 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server/manager/GasterManager.hpp"
# include "debug.h"

GasterManager::GasterManager(
	WorldConfig& world_data
):
	_world_data(world_data) {}


// DEBUG
void GasterManager::debug_print_structure_data(bool show_gui_data) {
	debug_print_structure(_world_data, show_gui_data);
}
