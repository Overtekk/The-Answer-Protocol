/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualRoom.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 12:00:27 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/22 10:57:39 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unordered_map>
# include <string>
# include <iostream>

# include "raylib.h"
# include "gui/rooms/VisualRoom.hpp"
# include "gui/Items/VisualItem.hpp"


VisualRoom::VisualRoom(
    const Texture2D	&tile_map
):
    tile_map(tile_map)
{}

void    VisualRoom::addItem(VisualItem *item, const std::string &id) {
    auto result = this->items.emplace(id, item);
    if (result.second == false) {
        std::cout << "not added\n";
    }
    else {
        std::cout << "added\n";
    }
}

std::unordered_map<std::string, VisualItem*>	&VisualRoom::getItems() {
    return (this->items);
}

void	VisualRoom::drawItems() {
    for (auto item : this->items) {
        item.second->DrawInRoom();
    }
}