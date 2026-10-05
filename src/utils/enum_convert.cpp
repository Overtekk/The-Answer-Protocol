/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum_convert.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 16:48:05 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/05 11:26:42 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include "config/WorldConfig.hpp"

std::string direction_to_string(Direction dir) {
    switch (dir) {
        case Direction::NORTH: return "north";
        case Direction::SOUTH: return "south";
        case Direction::EAST:  return "east";
        case Direction::WEST:  return "west";
        default:               return "unknown";
    }
}

std::string enemy_type_to_string(EnemyType type) {
    switch (type) {
        case EnemyType::NPC:   return "npc";
        case EnemyType::ENEMY: return "enemy";
        case EnemyType::SHOP:  return "shop";
        case EnemyType::BOSS:  return "boss";
        default:               return "unknown";
    }
}

std::string item_type_to_string(ItemType type) {
    switch (type) {
        case ItemType::CONSUMABLE:   return "consumable";
        case ItemType::KEY: 	     return "key";
        case ItemType::WEAPON:       return "weapon";
        default:               	     return "unknown";
    }
}
