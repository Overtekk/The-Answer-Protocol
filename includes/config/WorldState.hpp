/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WorldState.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 09:27:15 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/06 09:38:40 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <unordered_map>
# include "base_class/rooms/Room.hpp"
# include "base_class/entities/Entity.hpp"
# include "base_class/items/Item.hpp"

// *Structure that contains all objects.*

struct WorldState {
	std::unordered_map<std::string, std::unique_ptr<Room>> rooms;
	std::unordered_map<std::string, std::unique_ptr<Entity>> entities;
	std::unordered_map<std::string, std::unique_ptr<Item>> items;
};
